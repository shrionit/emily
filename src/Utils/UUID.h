#ifndef UUID_H
#define UUID_H


#pragma comment(lib, "rpcrt4.lib")  // UuidCreate - Minimum supported OS Win 2000
#include <windows.h>
#include <iostream>
#pragma once
namespace uuid {
#ifndef v4
    const std::string v4();
#endif
}


#endif
