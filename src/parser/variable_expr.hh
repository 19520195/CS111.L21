#pragma once

#include "expr_ast.hh"

class variable_expr : public expr_ast {
public:
    variable_expr(const std::string &name);

private:
    std::string m_name;
};
