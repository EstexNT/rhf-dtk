import os
import sys
import subprocess
import argparse

scriptDir = os.path.dirname(os.path.realpath(__file__))
rootDir = os.path.abspath(os.path.join(scriptDir, ".."))

dtkPath = os.path.join(rootDir, "build/tools/dtk")

def listLabelHeaders(szsPath):
    try:
        output = subprocess.check_output([dtkPath, "vfs", "ls", f"{szsPath}:./"], text=True)
        labelHeaders = []
        for line in output.splitlines():
            parts = line.strip().split('|')
            if len(parts) >= 3:
                filename = parts[1].strip()
                if filename.startswith("rcad_") and filename.endswith("_labels.h"):
                    labelHeaders.append(filename)
        return labelHeaders
    except subprocess.CalledProcessError as e:
        print(f"[RCAD LABEL] Error listing contents of {szsPath}: {e}", file=sys.stderr)
        return []

def getOutputPath(szsPath, labelFile, includeRoot="include"):
    # find the directory path after "cellanim/"
    components = os.path.normpath(szsPath).split(os.sep)
    if "cellanim" not in components:
        print(f"[RCAD LABEL] 'cellanim' not found in path: {szsPath}", file=sys.stderr)
        sys.exit(1)

    idx = components.index("cellanim") + 1
    relSubdir = os.path.join(*components[idx:]) # e.g., cellanim/ABCDE/verX/cellanim.szs
    relDir = os.path.dirname(relSubdir) # strip 'cellanim.szs'
    return os.path.join(includeRoot, relDir, labelFile)

def extractLabel(szsPath, labelFile, outputPath):
    os.makedirs(os.path.dirname(outputPath), exist_ok=True)
    try:
        subprocess.check_call([dtkPath, "vfs", "cp", f"{szsPath}:./{labelFile}", outputPath], stdout=subprocess.DEVNULL)

        # rewrite as UTF-8
        with open(outputPath, 'r', encoding='shift_jis') as f:
            content = f.read()
        with open(outputPath, 'w', encoding='utf-8') as f:
            f.write(content)

        # print(f"Extracted {labelFile} -> {outputPath}")
    except subprocess.CalledProcessError as e:
        print(f"[RCAD LABEL] Failed to extract {labelFile} from {szsPath}; is it valid?", file=sys.stderr)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("szsFiles", nargs="+", help="paths to cellanim archives")
    parser.add_argument("--outputDir", "-o", help="path to output directory")
    args = parser.parse_args()

    for idx, szsPath in enumerate(args.szsFiles, start=1):
        print(f"[RCAD LABEL] Processing ({idx}/{len(args.szsFiles)}): {szsPath}", flush=True)

        if not os.path.isfile(szsPath):
            print(f"\n[RCAD LABEL] SZS does not exist: {szsPath}, reconfigure?", file=sys.stderr)
            continue

        labelFiles = listLabelHeaders(szsPath)
        if not labelFiles:
            print(f"\n[RCAD LABEL] No *_labels.h found in {szsPath}, or error listing?", file=sys.stderr)
            continue

        for labelFile in labelFiles:
            outputPath = getOutputPath(szsPath, labelFile, args.outputDir)
            extractLabel(szsPath, labelFile, outputPath)

    print()
    print("[RCAD LABEL] All done!")

if __name__ == "__main__":
    main()
