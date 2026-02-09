#!/usr/bin/env python3
"""
merge_root_files.py

Merge multiple ROOT files into a single output file.

Usage:
  merge_root_files.py -o out.root in1.root in2.root in3.root in4.root

By default uses the `hadd` executable if available, otherwise you can
force `--method pyroot` to use PyROOT's `TFileMerger`.
"""
import argparse
import shutil
import subprocess
import sys


def merge_with_hadd(output, inputs):
    hadd = shutil.which("hadd")
    if not hadd:
        raise RuntimeError("`hadd` not found in PATH")
    cmd = [hadd, "-f", output] + inputs
    subprocess.check_call(cmd)


def merge_with_pyroot(output, inputs):
    try:
        import ROOT
    except Exception as e:
        raise RuntimeError(f"PyROOT import failed: {e}")
    merger = ROOT.TFileMerger(False)
    for f in inputs:
        merger.AddFile(f)
    merger.OutputFile(output)
    ok = merger.Merge()
    if not ok:
        raise RuntimeError("TFileMerger.Merge() reported failure")


def parse_args():
    p = argparse.ArgumentParser(description="Merge ROOT files (uses hadd or PyROOT)")
    p.add_argument("-o", "--output", required=True, help="output ROOT file")
    p.add_argument("--method", choices=["hadd", "pyroot"], default="hadd",
                   help="merge method: prefer `hadd` (default) or `pyroot`")
    p.add_argument("inputs", nargs="+", help="input ROOT files (2 or more)")
    return p.parse_args()


def main():
    args = parse_args()
    if len(args.inputs) < 2:
        print("Need at least two input ROOT files to merge", file=sys.stderr)
        sys.exit(2)

    try:
        if args.method == "hadd":
            try:
                merge_with_hadd(args.output, args.inputs)
            except Exception:
                # fallback to pyroot if hadd fails or not found
                merge_with_pyroot(args.output, args.inputs)
        else:
            merge_with_pyroot(args.output, args.inputs)
    except subprocess.CalledProcessError as e:
        print(f"hadd failed with exit {e.returncode}", file=sys.stderr)
        sys.exit(e.returncode)
    except Exception as e:
        print(f"Merge failed: {e}", file=sys.stderr)
        sys.exit(1)

    print(f"Merged {len(args.inputs)} files -> {args.output}")


if __name__ == "__main__":
    main()
