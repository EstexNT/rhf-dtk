# rsidGenerate v1.3 (Jul 29 2025)
# conhlee

import struct
import sys
import argparse
import io
import os

def myUnpack(form, formName, reader):
    data = struct.unpack(form, reader.read(struct.calcsize(form)))
    if formName:
        return dict(zip(formName, data))
    return data

def readCString(reader: io.BufferedReader) -> str:
    result = bytearray()
    while True:
        byte = reader.read(1)
        if not byte or byte == b'\x00':
            break
        result.extend(byte)
    return result.decode("ascii")

BRSAR_HEADER_FORM_NAME = [
    "id", "bom", "version", "fileSize", "headerSize", "sectionCount",
    "symbSectionOffs", "symbSectionSize",
    "infoSectionOffs", "infoSectionSize", 
    "fileSectionOffs", "fileSectionSize"
]
BRSAR_HEADER_FORM = "> 4s H H I H H IIIIII"

BRSAR_SYMB_FORM_NAME = [
    "id", "size",
    "nameTableOffs", "soundTreeOffs",
    "playerTreeOffs", "groupTreeOffs", 
    "bankTreeOffs",
]
BRSAR_SYMB_FORM = "> 4s I IIIII"

BRSAR_INFO_FORM_NAME = [
    "id", "size",
    "soundDataTableOffs", "bankTableOffs",
    "playerInfoTableOffs", "fileTableOffs", 
    "groupTableOffs", "soundCountTableOffs"
]
# The padding is the reference data, which we don't really care about ..
BRSAR_INFO_FORM = "> 4s I xxxxIxxxxIxxxxIxxxxIxxxxIxxxxI"

BRSAR_SOUNDDATA_FORM_NAME = [
    "nameIndex", "fileIndex", "playerID", "sound3DParamOffs",
    "volume", "playerPriority", "soundType", "remoteFilter",
    "soundInfoOffs", "userParam1", "userParam2",
    "panMode", "panCurve", "actorPlayerID"
]
BRSAR_SOUNDDATA_FORM = "> I I I xxxxI B B B B xxxxI I I B B B x"

BRSAR_BANKDATA_FORM_NAME = [
    "nameIndex", "fileIndex", "bankIndex"
]
BRSAR_BANKDATA_FORM = "> I I I"

BRSAR_PLAYERDATA_FORM_NAME = [
    "nameIndex", "playableSoundCount", "heapSize"
]
BRSAR_PLAYERDATA_FORM = "> I B x xx I xxxx"

BRSAR_GROUPDATA_FORM_NAME = [
    "nameIndex", "entryNum", "extFilePathOffs",
    "groupFileDataOffs", "groupFileDataSize",
    "groupAudioDataOffs", "groupAudioDataSize",
    "groupItemRefTableOffs"
]
BRSAR_GROUPDATA_FORM = "> I I xxxxI II II xxxxI"

def formatRSIDDef(name: str, id: int, useMacro: bool, hexID: bool):
    if useMacro:
        prefix = "#define"
        assignment = ""
        IDstr = f"(0x{id:X})" if hexID else f"({id})"
    else:
        prefix = "static const unsigned int"
        assignment = "= "
        IDstr = f"0x{id:X};" if hexID else f"{id};"

    return f"{prefix} {name} {assignment}{IDstr}"


def brsarProcess(f: io.BufferedReader, archiveName: str, useMacro = False, includeGuard = False, labeling = False, crlf = True, hexID = False):
    output = []

    if includeGuard:
        output.append(f"#ifndef RVLSOUNDID_{archiveName.upper()}")
        output.append(f"#define RVLSOUNDID_{archiveName.upper()}")
        output.append("")

    header = myUnpack(BRSAR_HEADER_FORM, BRSAR_HEADER_FORM_NAME, f)
    if header["id"] != b"RSAR":
        print("Header identifier is nonmatch .. is this really a BRSAR??", file=sys.stderr)
        sys.exit(1)
    if header["bom"] != 0xFEFF:
        print("Header BOM failed check .. we expected a big-endian BRSAR!", file=sys.stderr)
        sys.exit(1)
    if header["version"] != 0x0104:
        print("Odd .. version 01 04 was expected, but we got something else!", file=sys.stderr)
        print("We will continue anyways ..", file=sys.stderr)

    f.seek(header["symbSectionOffs"])
    symbSection = myUnpack(BRSAR_SYMB_FORM, BRSAR_SYMB_FORM_NAME, f)

    if symbSection["id"] != b"SYMB":
        print("SYMB section identifier is nonmatch ..", file=sys.stderr)
        sys.exit(1)

    baseOffset = header["symbSectionOffs"] + 8
    
    f.seek(baseOffset + symbSection["nameTableOffs"])
    nameCount = myUnpack("> I", None, f)[0]

    nameTable = [""] * nameCount

    for i in range(nameCount):
        offsetToName = myUnpack("> I", None, f)[0]

        prevReadPos = f.tell()
        f.seek(baseOffset + offsetToName)

        nameTable[i] = readCString(f)

        f.seek(prevReadPos)

    f.seek(header["infoSectionOffs"])
    infoSection = myUnpack(BRSAR_INFO_FORM, BRSAR_INFO_FORM_NAME, f)

    if infoSection["id"] != b"INFO":
        print("INFO section identifier is nonmatch ..", file=sys.stderr)
        sys.exit(1)

    baseOffset = header["infoSectionOffs"] + 8

    f.seek(baseOffset + infoSection["soundDataTableOffs"])
    soundDataCount = myUnpack("> I", None, f)[0]

    if labeling:
        output.append("// SOUND")
        output.append("")

    for i in range(soundDataCount):
        soundDataOffs = myUnpack("> xxxxI", None, f)[0]

        prevReadPos = f.tell()
        f.seek(baseOffset + soundDataOffs)

        soundData = myUnpack(BRSAR_SOUNDDATA_FORM, BRSAR_SOUNDDATA_FORM_NAME, f)

        output.append(formatRSIDDef(nameTable[soundData["nameIndex"]], i, useMacro, hexID))

        f.seek(prevReadPos)

    f.seek(baseOffset + infoSection["bankTableOffs"])
    bankDataCount = myUnpack("> I", None, f)[0]

    if labeling:
        output.append("")
        output.append("// BANK")
        output.append("")

    for i in range(bankDataCount):
        bankDataOffs = myUnpack("> xxxxI", None, f)[0]

        prevReadPos = f.tell()
        f.seek(baseOffset + bankDataOffs)

        bankData = myUnpack(BRSAR_BANKDATA_FORM, BRSAR_BANKDATA_FORM_NAME, f)

        output.append(formatRSIDDef(nameTable[bankData["nameIndex"]], i, useMacro, hexID))

        f.seek(prevReadPos)

    f.seek(baseOffset + infoSection["playerInfoTableOffs"])
    playerDataCount = myUnpack("> I", None, f)[0]

    if labeling:
        output.append("")
        output.append("// PLAYER")
        output.append("")

    for i in range(playerDataCount):
        playerDataOffs = myUnpack("> xxxxI", None, f)[0]

        prevReadPos = f.tell()
        f.seek(baseOffset + playerDataOffs)

        playerData = myUnpack(BRSAR_PLAYERDATA_FORM, BRSAR_PLAYERDATA_FORM_NAME, f)

        output.append(formatRSIDDef(nameTable[playerData["nameIndex"]], i, useMacro, hexID))

        f.seek(prevReadPos)

    f.seek(baseOffset + infoSection["groupTableOffs"])
    groupDataCount = myUnpack("> I", None, f)[0]

    if labeling:
        output.append("")
        output.append("// GROUP")
        output.append("")

    for i in range(groupDataCount):
        groupDataOffs = myUnpack("> xxxxI", None, f)[0]

        prevReadPos = f.tell()
        f.seek(baseOffset + groupDataOffs)

        groupData = myUnpack(BRSAR_GROUPDATA_FORM, BRSAR_GROUPDATA_FORM_NAME, f)

        if (groupData["nameIndex"] != 0xFFFFFFFF):
            output.append(formatRSIDDef(nameTable[groupData["nameIndex"]], i, useMacro, hexID))

        f.seek(prevReadPos)
    
    if includeGuard:
        output.append("")
        output.append("#endif")

    output.append("")

    return ("\r\n" if crlf else "\n").join(output)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("brsarPath", help="path to BRSAR")
    parser.add_argument("--output", "-o", help="path to output RSID")
    parser.add_argument("--useMacro", "-mac", action="store_true", help="use macros to store IDs instead of static const unsigned ints")
    parser.add_argument("--includeGuard", "-ig", action="store_true", help="add an include guard (there is none by default)")
    parser.add_argument("--unixNewline", "-lf", action="store_true", help="use a Unix-style newline (LF) instead of Windows-style (CRLF)")
    parser.add_argument("--hexID", "-hex", action="store_true", help="write IDs in hex instead of decimal")
    parser.add_argument("--sectionLabel", "-sl", action="store_true", help="add a comment above each archive section (SOUND, BANK, PLAYER, GROUP)")
    args = parser.parse_args()

    outputPath = os.path.abspath(
        args.output if args.output else f"{os.path.splitext(args.brsarPath)[0]}.rsid"
    )

    print(f"[RSID] Processing BRSAR at path '{args.brsarPath}' ..", end="")

    try:
        with open(args.brsarPath, "rb") as f:
            rsarName = os.path.splitext(os.path.basename(args.brsarPath))[0]
            headerContent = brsarProcess(
                f, rsarName,
                useMacro=args.useMacro, includeGuard=args.includeGuard, labeling=args.sectionLabel, hexID=args.hexID
            )
    except FileNotFoundError:
        print(f"[RSID] The specified BRSAR file was not found", file=sys.stderr)
        sys.exit(1)
    except PermissionError:
        print(f"[RSID] The BRSAR could not be read; permission was denied", file=sys.stderr)
        sys.exit(1)
    except IsADirectoryError:
        print(f"[RSID] BRSAR path points to a directory, not a file", file=sys.stderr)
        sys.exit(1)
    except OSError as e:
        print(f"[RSID] Failed to open BRSAR file: {e}", file=sys.stderr)
        sys.exit(1)
    except Exception as e:
        print(f"[RSID] Unexpected error while reading BRSAR: {e}", file=sys.stderr)
        sys.exit(1)

    print(" OK")

    print(f"[RSID] Writing RSID to path '{outputPath}' ..", end="")
    try:
        with open(outputPath, "w") as out:
            out.write(headerContent)
    except Exception as e:
        print(f"[RSID] Failed to write output RSID: {e}", file=sys.stderr)
        sys.exit(1)

    print(" OK")

    print("[RSID] All done!")

if __name__ == "__main__":
    main()
