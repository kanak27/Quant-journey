#!/usr/bin/env python
"""Git clean filter: strip outputs & execution counts from Jupyter notebooks.

Reads a notebook JSON on stdin and writes the stripped notebook on stdout, so
committed notebooks carry no outputs/plot images (keeping diffs and repo size
small). Pure standard library -- runs anywhere `python` is available. Cell
source, markdown and cell ids are left untouched; only volatile output/run
state is removed.
"""
import sys, json

def strip(nb):
    for cell in nb.get("cells", []):
        if cell.get("cell_type") == "code":
            cell["outputs"] = []
            cell["execution_count"] = None
        meta = cell.get("metadata", {})
        for k in ("execution", "collapsed", "scrolled"):
            meta.pop(k, None)
    nb.get("metadata", {}).pop("widgets", None)
    return nb

def main():
    data = sys.stdin.read()
    try:
        nb = json.loads(data)
    except Exception:
        sys.stdout.write(data)          # not valid JSON -> pass through untouched
        return
    json.dump(strip(nb), sys.stdout, indent=1, ensure_ascii=False)
    sys.stdout.write("\n")

if __name__ == "__main__":
    main()
