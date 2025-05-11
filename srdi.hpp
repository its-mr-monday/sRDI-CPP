#ifndef SRDI_HPP
#define SRDI_HPP
#pragma once

#include <vector>
#include <string>

//For Linux machines
#ifndef BYTE
typedef unsigned char BYTE;
#endif

std::vector<BYTE> shellcodifyDll(std::vector<BYTE> dll, std::string funcName, std::string funcArgs);

#endif