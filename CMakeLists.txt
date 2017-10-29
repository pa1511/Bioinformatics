cmake_minimum_required(VERSION 3.8)
project(Welcome_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        nbproject/private/c_standard_headers_indexer.c
        nbproject/private/cpp_standard_headers_indexer.cpp
        BioSequence.cpp
        BioSequence.h
        example-input.txt
        fasta-example
        FastADocument.cpp
        FastADocument.h
        SimpleClass.cpp
        SimpleClass.h
        Stopwatch.cpp
        Stopwatch.h
        welcome.cc
        welcome.h)

add_executable(Welcome_1 ${SOURCE_FILES})