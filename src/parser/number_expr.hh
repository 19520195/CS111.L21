#pragma once

#include "expr_ast.hh"

class number_expr : public expr_ast {
public:
    number_expr(unsigned int value);

private:
    unsigned int m_value;
};
