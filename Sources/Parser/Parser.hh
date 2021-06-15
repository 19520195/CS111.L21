#pragma once

#include "Lexer/Lexer.hh"
#include "Lexer/Precedence.hh"
#include "ExprAST.hh"

#include <fstream>
#include <memory>

class Parser
{
  public:
    ~Parser() = default;

    Parser();
    Parser(std::unique_ptr<Lexer> L);
    Parser(const std::string& Filename);

    std::unique_ptr<ExprAST> ParseNumberExpr();
    std::unique_ptr<ExprAST> ParseIdentifierExpr();

    std::unique_ptr<ExprAST> ParsePrimary();
    std::unique_ptr<ExprAST> ParseParenthesesExpr();

    std::unique_ptr<ExprAST> ParseBinExpr(Precedence Value, std::unique_ptr<ExprAST> ShiftLeft);

    std::unique_ptr<ExprAST> ParseBlockExpr();
    std::unique_ptr<ExprAST> ParseExpression();
    std::unique_ptr<ExprAST> ParseBuiltinExpr();

    std::unique_ptr<ExprAST> ParseIfExpr();
    std::unique_ptr<ExprAST> ParseWhileExpr();

    std::unique_ptr<ExprAST> HandleToken(Token T);
    std::unique_ptr<ExprAST> ParseNextToken();

    void Ignore();
    void ResetInput(const std::string& Filename);

  private:
    std::unique_ptr<Lexer> m_Lexer;
    std::unique_ptr<std::ifstream> m_Input;
};
