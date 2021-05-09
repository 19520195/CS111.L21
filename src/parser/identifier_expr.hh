#pragma once

#include "expr_ast.hh"

class identifier_expr : public expr_ast {
public:
    identifier_expr(const std::string& value);

private:
    std::string m_value;
};
