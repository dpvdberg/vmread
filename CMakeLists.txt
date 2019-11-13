cmake_minimum_required(VERSION 3.10)
project(HLAPI)

set(CMAKE_CXX_STANDARD 14)

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
        pmparser.c
        vmmem.c
        winstructs.h
        wintools.c
        wintools.h)


target_include_directories(vmread PUBLIC hlapi ${CMAKE_CURRENT_SOURCE_DIR})