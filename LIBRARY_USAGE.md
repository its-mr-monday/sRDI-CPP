# SRDI C++ Library

A Header only Library is available and functional across Windows and POSIX systems

If you wish to bundle sRDI-CPP into your C++ project simply add the [HEADER_FILE](header_only/srdi.hpp) to your project

## Usage

In a C++ source file reference the header file:

```cpp
#include "srdi.hpp"
```

There is 1 primary function that you may use for turning dll's into shellcode, the function itself validates the architecture of a Dll (32/64 bit) and creates PIE shellcode to jump to a specified function

See bellow how to use this function

## Library Function

### shellcodifyDll

Signature:
```cpp
std::vector<BYTE> shellcodifyDll(std::vector<BYTE> dll, std::string funcName, std::string funcArgs);
```

Params:
 - std::vector<BYTE> dll **The bytes of the DLL you wish to shellcodify**
 - std::string funcName **The function to execute within your DLL** (You may also use `DllMain`)
 - std::string funcArgs **The arguments to pass to your exported functions** (You may leave this blank)
