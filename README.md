# Yodelr

[![Build](https://github.com/xorz57/yodelr/actions/workflows/Build.yml/badge.svg)](https://github.com/xorz57/yodelr/actions/workflows/Build.yml)

## Diagram

![diagram](assets/diagram.png)

## How to Build

```bash
git clone https://github.com/xorz57/yodelr.git
cd yodelr
cmake -B build -DCMAKE_BUILD_TYPE=Release -S .
cmake --build build --config Release
ctest --test-dir build --build-config Release
```
