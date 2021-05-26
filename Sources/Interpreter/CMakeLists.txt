INCLUDE_DIRECTORIES(..)
ADD_LIBRARY(
    Interpreter
    DataTable.cc
    Interpreter.cc
)

TARGET_LINK_LIBRARIES(Interpreter Parser)
