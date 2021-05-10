#pragma once

#include "expr_ast.hh"
#include <lexer/lexer.hh>
#include <memory>
#include <exception>

class parser {
public:
    parser(std::unique_ptr<lexer> lexer);

    lexer* getlexer();

    std::unique_ptr<expr_ast> parse_number_expr();
    std::unique_ptr<expr_ast> parse_identifier_expr();

    std::unique_ptr<expr_ast> parse_paren_expr();
    std::unique_ptr<expr_ast> parse_primary();
    std::unique_ptr<expr_ast> parse_expr();
    std::unique_ptr<expr_ast> parse_bin_op(int expr_prec, std::unique_ptr<expr_ast> shift_left);

    std::unique_ptr<expr_ast> parse_if_expr();
    void live_parse();

private:
    std::unique_ptr<lexer> m_lexer;
};
