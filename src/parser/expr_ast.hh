#pragma once

#include <lexer/lexer.hh>
#include <string>
#include <memory>
#include <vector>

class expr_ast {
public:
    virtual ~expr_ast();
};

#include "number_expr.hh"
#include "identifier_expr.hh"
#include "variable_expr.hh"
#include "bin_expr.hh"
