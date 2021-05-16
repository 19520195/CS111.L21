INCLUDE_DIRECTORIES(..)
ADD_LIBRARY(
    Interp
    DataTable.cc
    Interp.cc
)

TARGET_LINK_LIBRARIES(Interp Parser)
