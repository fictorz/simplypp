#!/usr/bin/env python3
import os, json

# 1) Compute your real workspace folder in forward-slash form
ws = os.path.abspath(os.getcwd()).replace("\\", "/")  # → C:/Users/felix/dev/simplypp

# 2) Load compile_commands.json
fname = "build/compile_commands.json"
data = json.load(open(fname, "r", encoding="utf-8"))

# 3) Rewrite every path entry
for e in data:
    for key in ("directory", "file"):
        e[key] = e[key].replace("/simplypp", ws)
    e["command"] = e["command"].replace("/simplypp", ws)

# 4) Save it back
json.dump(data, open(fname, "w", encoding="utf-8"), indent=2)
print(f"✅ Rewrote compile_commands.json to use {ws}")
