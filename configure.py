#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import sys
import argparse

from pathlib import Path
from tools.project import (
    Object,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "SOME01",	# 0
]

if len(VERSIONS) > 1:
    versions_str = ", ".join(VERSIONS[:-1]) + f" or {VERSIONS[-1]}"
else:
    versions_str = VERSIONS[0]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    default="configure",
    help="configure or progress (default: configure)",
    nargs="?",
)
parser.add_argument(
    "--version",
    dest="version",
    default=VERSIONS[DEFAULT_VERSION],
    help=f"version to build ({versions_str})",
)
parser.add_argument(
    "--build-dir",
    dest="build_dir",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--compilers",
    dest="compilers",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    dest="map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    dest="debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        dest="wrapper",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--build-dtk",
    dest="build_dtk",
    type=Path,
    help="path to decomp-toolkit source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    dest="sjiswrap",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--verbose",
    dest="verbose",
    action="store_true",
    help="print verbose output",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = args.version.upper()
if config.version not in VERSIONS:
    sys.exit(f"Invalid version '{config.version}', expected {versions_str}")
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.build_dtk_path = args.build_dtk
config.compilers_path = args.compilers
config.debug = args.debug
config.generate_map = args.map
config.sjiswrap_path = args.sjiswrap
if not is_windows():
    config.wrapper = args.wrapper

# Tool versions
config.compilers_tag = "20231018"
config.dtk_tag = "v0.6.2"
config.sjiswrap_tag = "v1.1.1"
config.wibo_tag = "0.6.9"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
    "-listclosure",
]

cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    # "-W all",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
	"-enc SJIS",
    "-i include",
    "-i include/stl",
    "-i include/revolution",
    "-i src/GameUtil",
    "-i src/Game",
    f"-i build/{config.version}/include",
    f"-DVERSION={version_num}",
]

# Debug flags
if config.debug:
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Actual game code 
cflags_game = [
    *cflags_base,
    "-RTTI on",
    "-str readonly",
    "-func_align 4",
    "-enc multibyte",
]

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
	"-inline auto",
]

# Game utilities
cflags_gameutil = [
    *cflags_base,
    "-RTTI on",
    "-str readonly",
    "-use_lmw_stmw on",
    "-func_align 4",
    "-ipa file",
]


config.linker_version = "Wii/1.0"

def RevolutionLib(lib_name, objects):
    return {
        "lib": lib_name,
        "mw_version": config.linker_version,
        "cflags": cflags_base,
        "host": False,
        "objects": objects,
    }

def Nw4rLib(lib_name, objects):
    return {
        "lib": lib_name,
        "mw_version": config.linker_version,
        "cflags": cflags_base,
        "host": False,
        "objects": objects,
    }

Matching = True
NonMatching = False

config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "Game", 
        "mw_version": config.linker_version,
        "cflags": cflags_game,
        "host": False,
        "shiftjis": False,
        "objects": [
            Object(NonMatching, "Game/Menu/SceneMenu.cpp"),
            Object(NonMatching, "Game/ExScene.cpp"),
            Object(NonMatching, "Game/Prologue/ScenePrologue.cpp"),
            Object(Matching, "Game/SceneManager.cpp"),
        ],
    },
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "host": False,
        "objects": [
            Object(NonMatching, "Runtime.PPCEABI.H/global_destructor_chain.c"),
            Object(NonMatching, "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
        ],
    },
    RevolutionLib(
        "hbm", 
        [
            Object(NonMatching, "revolution/hbm/nw4hbm/lyt/lyt_bounding.cpp"),
            Object(NonMatching, "revolution/hbm/nw4hbm/lyt/lyt_pane.cpp"),
            Object(NonMatching, "revolution/hbm/nw4hbm/lyt/lyt_picture.cpp"),
            Object(NonMatching, "revolution/hbm/nw4hbm/lyt/lyt_textBox.cpp"),
            Object(NonMatching, "revolution/hbm/nw4hbm/lyt/lyt_window.cpp"),
            Object(NonMatching, "revolution/hbm/nw4hbm/lyt/ut_TextWriterBase.cpp"),
            Object(NonMatching, "revolution/hbm/nw4hbm/ut/ut_TextWriterBase.cpp"),   
        ]
    ),
    Nw4rLib(
        "g3d",
        [
            Object(NonMatching, "nw4r/g3d/g3d_state.cpp"),
        ]
    ),
    Nw4rLib(
        "lyt",
        [
            Object(NonMatching, "nw4r/lyt/lyt_pane.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_picture.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_textBox.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_window.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_bounding.cpp"),
        ]
    ),
    Nw4rLib(
        "snd",
        [
            Object(NonMatching, "nw4r/snd/snd_AxManager.cpp"),
            Object(NonMatching, "nw4r/snd/snd_BasicSound.cpp"),
            Object(NonMatching, "nw4r/snd/snd_SeqSound.cpp"),
            Object(NonMatching, "nw4r/snd/snd_SoundSystem.cpp"),
            Object(NonMatching, "nw4r/snd/snd_StrmSound.cpp"),
            Object(NonMatching, "nw4r/snd/snd_WaveSound.cpp"),
        ]
    ),
    Nw4rLib(
        "ut",
        [
            Object(NonMatching, "nw4r/ut/ut_IOStream.cpp"),
            Object(NonMatching, "nw4r/ut/ut_FileStream.cpp"),
            Object(NonMatching, "nw4r/ut/ut_DvdFileStream.cpp"),
            Object(NonMatching, "nw4r/ut/ut_DvdLockedFileStream.cpp"),
            Object(NonMatching, "nw4r/ut/ut_LockedCache.cpp"),
            Object(NonMatching, "nw4r/ut/ut_TextWriterBase.cpp"),
        ]
    ),
    {
        "lib": "GameUtil",
        "mw_version": config.linker_version,
        "cflags": cflags_gameutil,
        "host": False,
        "objects": [
            Object(Matching, "GameUtil/Mem.cpp"),
            Object(NonMatching, "GameUtil/FileManager.cpp"),
            Object(NonMatching, "GameUtil/Controller.cpp"),
            Object(NonMatching, "GameUtil/GraphicManager.cpp"),
            Object(NonMatching, "GameUtil/LayoutManager.cpp"),
            Object(NonMatching, "GameUtil/GameManager.cpp"),
            Object(Matching, "GameUtil/Scene.cpp"),
            Object(NonMatching, "GameUtil/Layout.cpp"),
            Object(NonMatching, "GameUtil/LayoutAnimation.cpp"),
            Object(Matching, "GameUtil/Random.cpp"),
            Object(Matching, "GameUtil/DiscMessages.cpp"),
            Object(NonMatching, "GameUtil/CellAnimManager.cpp"),
            Object(NonMatching, "GameUtil/CellAnim.cpp"),
            Object(NonMatching, "GameUtil/TickFlow.cpp"),
            Object(NonMatching, "GameUtil/TickFlowManager.cpp"),
            Object(NonMatching, "GameUtil/SoundManager.cpp"),
            Object(NonMatching, "GameUtil/InputChecker.cpp"),
            Object(NonMatching, "GameUtil/InputCheckManager.cpp"),
            Object(NonMatching, "GameUtil/TimeRatio.cpp"),
            Object(NonMatching, "GameUtil/List.cpp"), # matching; not linked because weak RTTI
            Object(NonMatching, "GameUtil/CheckPointManager.cpp"),
            Object(Matching, "GameUtil/SDManager.cpp"),
            Object(NonMatching, "GameUtil/DebugPrint.cpp"),
            Object(NonMatching, "GameUtil/VarParamManager.cpp"),
            Object(NonMatching, "GameUtil/code_801ed6a8.cpp"),
            Object(NonMatching, "GameUtil/DebugConsole.cpp"),
            
        ],
    },
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress and write progress.json
    config.progress_each_module = args.verbose
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
