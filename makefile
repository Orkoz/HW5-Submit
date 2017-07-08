# This is a Makefile for project
CCC = g++
CXXFLAGS = -g -Wall -std=c++0x
CXXLINK = $(CCC)
OBJS = Commands.o LineParser.o main.o MamatScriptEngine.o Matrix.o Scalar.o Variable.o VariablesMap.o

all: MamatScript

MamatScript: $(OBJS) 
	$(CXXLINK) -o MamatScript $(OBJS)

Commands.o: Commands.cpp Commands.h VariablesMap.h Variable.h MySharedPtr.h ScriptExceptions.h Scalar.h Matrix.h LineParser.h
LineParser.o: LineParser.cpp LineParser.h VariablesMap.h Variable.h MySharedPtr.h ScriptExceptions.h Commands.h Scalar.h Matrix.h
main.o: main.cpp MamatScriptEngine.h VariablesMap.h Variable.h MySharedPtr.h ScriptExceptions.h LineParser.h Commands.h Scalar.h Matrix.h
MamatScriptEngine.o: MamatScriptEngine.cpp MamatScriptEngine.h VariablesMap.h Variable.h MySharedPtr.h ScriptExceptions.h LineParser.h Commands.h
Matrix.o: Matrix.cpp Matrix.h Variable.h MySharedPtr.h ScriptExceptions.h Scalar.h
Scalar.o: Scalar.cpp Scalar.h Variable.h MySharedPtr.h ScriptExceptions.h Matrix.h
Variable.o: Variable.cpp Variable.h MySharedPtr.h ScriptExceptions.h
VariablesMap.o: VariablesMap.cpp VariablesMap.h Variable.h MySharedPtr.h ScriptExceptions.h