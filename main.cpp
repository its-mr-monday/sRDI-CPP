/*
MIT License

Copyright (c) 2025 its-mr-monday

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "argparse.hpp"
#include "srdi.hpp"
#include <stdint.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

std::vector<BYTE> readFile(std::string path) {
    std::vector<BYTE> buffer;
    FILE* file = fopen(path.c_str(), "rb");
    if (file) {
        fseek(file, 0, SEEK_END);
        size_t size = ftell(file);
        fseek(file, 0, SEEK_SET);
        buffer.resize(size);
        fread(buffer.data(), 1, size, file);
        fclose(file);
    }
    return buffer;
}

bool writeFile(std::string path, std::vector<BYTE> data) {
    FILE* file = fopen(path.c_str(), "wb");
    if (file) {
        fwrite(data.data(), 1, data.size(), file);
        fclose(file);
        return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("srdicpp");
    program.add_argument("dll")
        .help("DLL to be converted to shellcode");
    
    program.add_argument("-f", "--function")
        .default_value(std::string("DllMain"))
        .help("Function to be called");
    program.add_argument("-a", "--args")
        .default_value(std::string(""))
        .help("Arguments to be passed to the function");
    program.add_argument("-o", "--output")
        .default_value(std::string("shellcode.bin"))
        .help("Output file for the shellcode");
    try {
        program.parse_args(argc, argv);
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }
    std::string dllPath = program.get<std::string>("dll");
    std::string functionName = program.get<std::string>("--function");
    std::string args = program.get<std::string>("--args");
    std::string outputPath = program.get<std::string>("--output");
    std::vector<BYTE> dllBytes = readFile(dllPath);
    if (dllBytes.empty()) {
        std::cerr << "Failed to read DLL file: " << dllPath << std::endl;
        return 1;
    }
    std::vector<BYTE> shellcode = shellcodifyDll(dllBytes, functionName, args);
    if (shellcode.empty()) {
        std::cerr << "Failed to generate shellcode" << std::endl;
        return 1;
    }
    if (!writeFile(outputPath, shellcode)) {
        std::cerr << "Failed to write shellcode to file: " << outputPath << std::endl;
        return 1;
    }
    std::cout << "Shellcode written to: " << outputPath << std::endl;
    std::cout << "Shellcode size: " << shellcode.size() << " bytes" << std::endl;
    return 0;
}