cmake_minimum_required(VERSION 3.10)
project(HLAPI)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(hlapi)

add_library(vmread SHARED
        hlapi/hlapi.h
        hlapi/pointers.h
        hlapi/windll.cpp
        hlapi/winprocess.cpp
        hlapi/winprocesslist.cpp
        definitions.h
        mem.c
        mem.h
        pmparser.h
        vmmem.c
        winstructs.h
        wintools.c
        wintools.h)