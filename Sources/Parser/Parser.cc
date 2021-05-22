#include "Parser.hh"

Parser::Parser() : m_Lexer(std::make_unique<Lexer>())
{
  // Parser::Parser
}

Parser::Parser(std::unique_ptr<Lexer> L) : m_Lexer(std::move(L))
{
  // Parser::Parser
}

std::unique_ptr<ExprAST> Parser::ParseNumberExpr()
{
  return std::make_unique<NumberExpr>(m_Lexer->GetNumberValue());
}

std::unique_ptr<ExprAST> Parser::ParseIdentifierExpr()
{
  return std::make_unique<VariableExpr>(m_Lexer->GetIdentifierValue());
}

std::unique_ptr<ExprAST> Parser::ParsePrimary()
{
  switch (m_Lexer->GetLastToken())
  {
    case Token::NUMBER             : return ParseNumberExpr();
    case Token::IDENTIFIER         : return ParseIdentifierExpr();
    case Token::OPENING_PARENTHESES: return ParseParenthesesExpr();
    default                        : return nullptr;
  }
}

std::unique_ptr<ExprAST> Parser::ParseParenthesesExpr()
{
  std::unique_ptr<ExprAST> Expression = ParseExpression();

  if (Expression != nullptr)
    if (m_Lexer->GetLastToken() != Token::CLOSING_PARENTHESIS)
      throw std::logic_error("expected ')'");

  return Expression;
}

std::unique_ptr<ExprAST> Parser::ParseBinExpr()
{
  m_Lexer->GetNextToken();
  std::unique_ptr<ExprAST> Left = ParsePrimary();
  if (Left == nullptr)
    throw std::logic_error("Left side is undefined");

  Token Oper = m_Lexer->GetNextToken();
  if (Oper == Token::IDENTIFIER)
    throw std::logic_error("Undefined operator " + m_Lexer->GetIdentifierValue());

  m_Lexer->GetNextToken();
  std::unique_ptr<ExprAST> Right = ParsePrimary();;
  if (Left == nullptr)
    throw std::logic_error("Right side is undefined");

  return std::make_unique<BinExpr>(Oper, std::move(Left), std::move(Right));
}

std::unique_ptr<ExprAST> Parser::ParseBinExpr(Precedence PreviousPrecedence, std::unique_ptr<ExprAST> ShiftLeft)
{
  for (std::unique_ptr<ExprAST> ShiftRight; ;)
  {
    if (false) //-> expected an exception
      throw std::logic_error("expected a binary operator");

    Precedence CurrentPrecedence = Precedence::FromToken(m_Lexer->GetLastToken());
    if (CurrentPrecedence < PreviousPrecedence)
      return ShiftLeft;

    Token Operator = m_Lexer->GetLastToken();
    if (!Operator.IsOperator())
      return ShiftLeft;

    m_Lexer->GetNextToken();
    if (!(ShiftRight = ParsePrimary()))
      return nullptr;

    m_Lexer->GetNextToken();
    Precedence NextPrecedence = Precedence::FromToken(m_Lexer->GetLastToken());
    if (CurrentPrecedence < NextPrecedence)
      if (!(ShiftRight = ParseBinExpr(CurrentPrecedence + 1, std::move(ShiftRight))))
        return nullptr;

    ShiftLeft = std::make_unique<BinExpr>(Operator, std::move(ShiftLeft), std::move(ShiftRight));
  }

  // For loop always return a value
  // So return here is meaningless
}

std::unique_ptr<ExprAST> Parser::ParseBlockExpr()
{
  std::unique_ptr<BlockExpr> BlockCode = std::make_unique<BlockExpr>();
  for
  (
    Token Current = m_Lexer->GetNextToken();
    Current != Token::END && Current != Token::ELSE;
    Current = m_Lexer->GetNextToken()
  ) BlockCode->InsertExpr(std::move(HandleToken(Current)));
  return BlockCode;
}

std::unique_ptr<ExprAST> Parser::ParseExpression()
{
  m_Lexer->GetNextToken();
  auto ShiftLeft = ParsePrimary();
  if (ShiftLeft == nullptr)
    return nullptr;

  m_Lexer->GetNextToken();
  return ParseBinExpr(Precedence::NONE_HIGH, std::move(ShiftLeft));
}

std::unique_ptr<ExprAST> Parser::ParseBuiltinExpr()
{
  const Token BuiltinToken = m_Lexer->GetLastToken();
  const std::string Identifier = m_Lexer->GetNextIdentifier();

  if (m_Lexer->GetLastToken() != Token::IDENTIFIER)
    throw std::logic_error("expected an identifier");

  std::unique_ptr<ExprAST> Expression = ParseExpression();
  if (m_Lexer->GetLastToken() != Token::SEPERATOR)
    throw std::logic_error("expected " + Lexer::Seperator);
  return std::make_unique<BuiltinExpr>(BuiltinToken, Identifier, std::move(Expression));
}

std::unique_ptr<ExprAST> Parser::ParseIfExpr()
{
  std::unique_ptr<ExprAST> Bin = ParseBinExpr();
  if (m_Lexer->GetNextToken() != Token::THEN)
    throw std::logic_error("expected then");
  if (m_Lexer->GetNextToken() != Token::SEPERATOR)
    throw std::logic_error("expected " + Lexer::Seperator);

  std::unique_ptr<ExprAST> ThenBlock = ParseBlockExpr();
  std::unique_ptr<ExprAST> ElseBlock;
  if (m_Lexer->GetLastToken() == Token::ELSE)
  {
    if (m_Lexer->GetNextToken() != Token::SEPERATOR)
      throw std::logic_error("expected " + Lexer::Seperator);
    ElseBlock = ParseBlockExpr();
  }

  if (m_Lexer->GetLastToken() != Token::END)
    throw std::logic_error("expected end");
  if (m_Lexer->GetNextToken() != Token::SEPERATOR)
    throw std::logic_error("expected " + Lexer::Seperator);
  return std::make_unique<IfExpr>(std::move(Bin), std::move(ThenBlock), std::move(ElseBlock));
}

std::unique_ptr<ExprAST> Parser::ParseWhileExpr()
{
  std::unique_ptr<ExprAST> Bin = ParseBinExpr();
  if (m_Lexer->GetNextToken() != Token::DO)
    throw std::logic_error("expected do");
  if (m_Lexer->GetNextToken() != Token::SEPERATOR)
    throw std::logic_error("expected " + Lexer::Seperator);

  std::unique_ptr<ExprAST> CodeBlock = ParseBlockExpr();
  if (m_Lexer->GetLastToken() != Token::END)
    throw std::logic_error("expected end");
  if (m_Lexer->GetNextToken() != Token::SEPERATOR)
    throw std::logic_error("expected " + Lexer::Seperator);

  return std::make_unique<WhileExpr>(std::move(Bin), std::move(CodeBlock));
}

std::unique_ptr<ExprAST> Parser::HandleToken(Token T)
{
  if (T.IsBuiltin())
    return ParseBuiltinExpr();

  switch (T)
  {
    case Token::IF   : return ParseIfExpr();
    case Token::WHILE: return ParseWhileExpr();
    default          : throw std::logic_error("Invalid expression");
  }
}

std::unique_ptr<ExprAST> Parser::ParseNextToken()
{
  Token CurrentToken = m_Lexer->GetNextToken();
  if (CurrentToken == Token::END_OF_FILE)
    exit(EXIT_SUCCESS);
  return HandleToken(CurrentToken);
}

void Parser::Ignore()
{
  if (m_Lexer->GetLastChar() != '\n')
    while (m_Lexer->GetNextChar() != '\n');
}
