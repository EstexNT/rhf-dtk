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

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
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

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-1"
config.compilers_tag = "20240706"
config.dtk_tag = "v1.3.0"
config.objdiff_tag = "v2.4.0"
config.sjiswrap_tag = "v1.2.0"
config.wibo_tag = "0.6.11"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
    f"--defsym VERSION_{config.version}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-gdwarf-2")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None


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
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
]

# Debug flags
if args.debug:
    # Or -sym dwarf-2 for Wii compilers
    cflags_base.extend(["-sym dwarf-2", "-DDEBUG=1"])
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

# Helper function for Revolution libraries
def RevolutionLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "Wii/1.0",
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": objects,
    }


# Helper function for NW4R libraries
def Nw4rLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "Wii/1.0",
        "cflags": cflags_base,
        "progress_category": "nw4r",
        "objects": objects,
    }

Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "Game", 
        "mw_version": config.linker_version,
        "cflags": cflags_game,
        "shiftjis": False,
        "progress_category": "game",
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
        "progress_category": "runtime",  # str | List[str]
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
        "progress_category": "gameutil",
        "objects": [
            Object(Matching, "GameUtil/Mem.cpp"),
            Object(NonMatching, "GameUtil/FileManager.cpp"),
            Object(NonMatching, "GameUtil/Controller.cpp"),
            Object(Matching, "GameUtil/GraphicManager.cpp"),
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

# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects

# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("sdk", "SDK Code"),
    ProgressCategory("runtime", "Runtime Code"),
    ProgressCategory("nw4r", "NW4R Code"),
    ProgressCategory("gameutil", "Game Utility Code"),
]
config.progress_each_module = args.verbose

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress and write progress.json
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
