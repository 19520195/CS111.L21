#include "if_expr.hh"

if_expr::if_expr(std::unique_ptr<expr_ast> condition, std::unique_ptr<expr_ast> block)
: m_condition(std::move(condition)), m_block(std::move(block)) {
    // if_expr::if_expr
}
