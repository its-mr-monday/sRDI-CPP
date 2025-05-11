#!/bin/bash

SRC_FILES=(
    "srdi.cpp"
    "main.cpp"
)

OUT_DIR="bin"

clear_and_make_bin() {
    rm -f "$OUT_DIR/*.exe"
    mkdir -p "$OUT_DIR"
}

build_win64() {
    x86_64-w64-mingw32-g++ -m64 -std=c++17 -O3 -o "$OUT_DIR/srdi64.exe" "${SRC_FILES[@]}" -I. -g -static
}

build_win32() {
    i686-w64-mingw32-g++ -m32 -std=c++17 -O3 -o "$OUT_DIR/srdi32.exe" "${SRC_FILES[@]}" -I. -g -static
}

build_linux() {
    g++ -m64 -std=c++17 -O3 -o "$OUT_DIR/srdi64" "${SRC_FILES[@]}" -I. -g -static
}


main() {
    clear_and_make_bin
    build_win64
    build_win32
    build_linux
}

main