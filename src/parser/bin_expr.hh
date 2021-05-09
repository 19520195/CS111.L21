#pragma once

#include "expr_ast.hh"

class bin_expr : public expr_ast {
public:
    bin_expr(const precedence& oper, std::unique_ptr<expr_ast> left, std::unique_ptr<expr_ast> right);

private:
    precedence                m_oper;
    std::unique_ptr<expr_ast> m_left;
    std::unique_ptr<expr_ast> m_right;
};
