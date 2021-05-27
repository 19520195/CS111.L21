#pragma once

#include "ExprAST.hh"
#include <memory>

class BinExpr : public ExprAST
{
  public:
    BinExpr(const Token& Oper, std::unique_ptr<ExprAST> Left, std::unique_ptr<ExprAST> Right);

    unsigned int GetLeftValue(DataTable& Table);
    unsigned int GetRightValue(DataTable& Table);

    std::string GenerateCode() const;
    std::unique_ptr<ExprAST> Execute(DataTable& Table);
    void LookupVaribale(std::set<std::string>& Set) const;

  private:
    Token                    m_Oper;
    std::unique_ptr<ExprAST> m_Left;
    std::unique_ptr<ExprAST> m_Right;
};
