INCLUDE_DIRECTORIES(..)
ADD_LIBRARY(
    Compiler
    Compiler.cc
)

TARGET_LINK_LIBRARIES(Compiler Parser)
