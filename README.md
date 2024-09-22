# Yodelr

[![Build](https://github.com/xorz57/yodelr/actions/workflows/Build.yml/badge.svg)](https://github.com/xorz57/yodelr/actions/workflows/Build.yml)

## Diagrams

![diagram1](assets/diagram1.png)

![diagram2](assets/diagram2.png)

## How to Build

```bash
git clone https://github.com/xorz57/yodelr.git
cd yodelr
cmake -B build -DCMAKE_BUILD_TYPE=Release -S .
cmake --build build --config Release
ctest --build-config Release
```
