INCLUDE_DIRECTORIES(..)
ADD_LIBRARY(
  Parser
  ExprAST.cc
  NumberExpr.cc
  VariableExpr.cc
  BinExpr.cc
  BlockExpr.cc
  BuiltinExpr.cc
  IfExpr.cc
  WhileExpr.cc
  Parser.cc
)

TARGET_LINK_LIBRARIES(Parser Lexer)
