# SRDI C++

This Code will generate a Windows Native DLL into position independent shellcode

The goal of this lib was to replicate the great work done by the sRDI team

[sRDI](https://github.com/monoxgas/sRDI)

Unfortunately, the latest versions of sRDI no longer works

There is however, a GO implementation that does:

[Doge-sRDI](https://github.com/timwhitez/Doge-sRDI)

This project is a C++ implementation of Doge-sRDI, it completes the same goal as that application, it also provides a header only solution if you wish to bundle this in your own project [Header Usage Here](./LIBRARY_USAGE.md)

The project can target Win32, Win64 and Linux64

To compile all 3 from a Linux machine, please ensure you have the mingw tool chain installed, along with g++

Simply run the build.sh script and it will generate a bin directory

This directory will create 3 files:

```
 - srdi32.exe (Win32 PE tool for creating x64/x86 DLL shellcode)
 - srdi64.exe (Win64 PE tool for creating x64/x86 DLL shellcode)
 - srdi64     (Linux ELF tool for creating x64/x86 DLL shellcode)
```

## Usage:

The binaries are all used the exact same way, but require specific flags:

Example usage converting a DLL (payload.dll) to shellcode

```bash
$ srdi64 ./payload.dll -o payload.bin
```

If you wish to specify a entrypoint other than DllMain you may use the `-f` flag

```bash
$ srdi64 ./payload.dll -o payload.bin -f DllExportedFunction
```

If you wish to pass args to the function you are calling (wether it be DllMain or any other function) you may use the `-a` flag

```bash
$ srdi64 ./payload.dll -o payload.bin -f DllMain -a "Args I am passing to DllMain"
```

The tool is generally simply to use, and you may use it the same with any of the compiled outputs (whether you are on a Windows or Linux machine)

The tool will also detect the architecture of the Dll to ensure it produces proper shellcode for the Dll, therefore, a x64 DLL will be converted to x64 shellcode and a x86 DLL will be converted to x86 shellcode
