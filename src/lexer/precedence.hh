#pragma once

#include "token.hh"

enum precedence : int {
    prec_greater = 0,
};

precedence _get_precedence(const token& t);
