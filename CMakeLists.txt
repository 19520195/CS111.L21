CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

SET(ProgramName Barebones)
SET(SourceFolder Sources)

# Set the project name and version
PROJECT(${ProgramName} VERSION 0.1)

# Specify the C++ standard
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Libraries
INCLUDE_DIRECTORIES(${SourceFolder})

FILE(GLOB LexerFiles  "${SourceFolder}/Lexer/*.cc" )
FILE(GLOB ParserFiles "${SourceFolder}/Parser/*.cc")
FILE(GLOB InterpFiles "${SourceFolder}/Interp/*.cc")

ADD_LIBRARY(Lexer  ${LexerFiles} )
ADD_LIBRARY(Interp ${InterpFiles})
ADD_LIBRARY(Parser ${ParserFiles} )

ADD_EXECUTABLE(${ProgramName} ${SourceFolder}/Master.cc)
TARGET_LINK_LIBRARIES(Parser Lexer)
TARGET_LINK_LIBRARIES(Interp Parser)
TARGET_LINK_LIBRARIES(${ProgramName} Lexer Parser Interp)
