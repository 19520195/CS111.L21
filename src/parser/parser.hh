#pragma once

#include "expr_ast.hh"
#include "../lexer/lexer.hh"
#include <memory>

class parser {
public:
    parser(std::unique_ptr<lexer> lexer);

    lexer* getlexer();

    std::unique_ptr<expr_ast> parse_number_expr();
    std::unique_ptr<expr_ast> parse_identifier_expr();
    std::unique_ptr<expr_ast> parse_primary();
    std::unique_ptr<expr_ast> parse_expression();
    std::unique_ptr<expr_ast> parse_bin_oper_right(int expr_prec, std::unique_ptr<expr_ast> shift_left);

    void parse_if_expr();
    void parse();

private:
    std::unique_ptr<lexer> m_lexer;
};
