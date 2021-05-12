#pragma once

#include "Lexer/Lexer.hh"
#include "ExprAST.hh"
#include <memory>

class Parser
{
  public:
    ~Parser() = default;

    Parser();
    Parser(std::unique_ptr<Lexer> L);

    std::unique_ptr<ExprAST> ParsePrimary();
    std::unique_ptr<ExprAST> ParseBuiltinExpr();
    std::unique_ptr<ExprAST> ParseBinExpr();
    std::unique_ptr<ExprAST> ParseBlockExpr();
    std::unique_ptr<ExprAST> ParseIfExpr();
    std::unique_ptr<ExprAST> ParseWhileExpr();

    std::unique_ptr<ExprAST> HandleToken(Token T);
    std::unique_ptr<ExprAST> ParseNextToken();

    void IgnoreCharacter();

  private:
    std::unique_ptr<Lexer> m_Lexer;
};
