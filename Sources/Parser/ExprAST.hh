#pragma once

#include "Lexer/Token.hh"
#include "Interpreter/DataTable.hh"
#include <memory>

class ExprAST
{
  public:
    virtual ~ExprAST();
    virtual std::unique_ptr<ExprAST> Execute(DataTable& Table) = 0;
};

#include "NumberExpr.hh"
#include "VariableExpr.hh"

#include "BinExpr.hh"
#include "BlockExpr.hh"

#include "BuiltinExpr.hh"

#include "IfExpr.hh"
#include "WhileExpr.hh"
