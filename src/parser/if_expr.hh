#pragma once

#include "expr_ast.hh"

class if_expr : public expr_ast {
public:
    if_expr(std::unique_ptr<expr_ast> condition, std::unique_ptr<expr_ast> block);

private:
    std::unique_ptr<expr_ast> m_condition;
    std::unique_ptr<expr_ast> m_block;
};
