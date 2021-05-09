#include "bin_expr.hh"

bin_expr::bin_expr(const precedence& oper,
                   std::unique_ptr<expr_ast> left,
                   std::unique_ptr<expr_ast> right)
: m_oper(oper), m_left(std::move(left)), m_right(std::move(right)) {
    // bin_expr::bin_expr
}
