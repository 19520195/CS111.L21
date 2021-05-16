CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(Barebones VERSION 0.1)

# Specify the C++ standard
SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Libraries
INCLUDE_DIRECTORIES(Sources)
FILE(GLOB LexerFiles  "Sources/Lexer/*.cc" )
FILE(GLOB ParserFiles "Sources/Parser/*.cc")
FILE(GLOB InterpFiles "Sources/Interp/*.cc")

ADD_LIBRARY(Lexer  ${LexerFiles} )
ADD_LIBRARY(Interp ${InterpFiles})
ADD_LIBRARY(Parser ${ParserFiles})

ADD_EXECUTABLE(${PROJECT_NAME} Sources/Master.cc)
TARGET_LINK_LIBRARIES(Parser Lexer)
TARGET_LINK_LIBRARIES(Interp Parser)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Lexer Parser Interp)
