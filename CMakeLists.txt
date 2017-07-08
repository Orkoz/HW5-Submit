cmake_minimum_required(VERSION 3.7)
project(HW5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        ScriptExceptions.h
        MySharedPtr.h
        Variable.h
        Variable.cpp
        Scalar.h
        Scalar.cpp
        Matrix.h
        Matrix.cpp
        VariablesMap.h
        VariablesMap.cpp
        main.cpp
        Commands.h
        Commands.cpp
        LineParser.h
        LineParser.cpp
        MamatScriptEngine.h
        MamatScriptEngine.cpp)
add_executable(HW5 ${SOURCE_FILES})