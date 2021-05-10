#pragma once

#include "lexer_token.hh"

enum bin_op_prec : int {
    PREC_NONE         =  0,
    PREC_NOT_EQUAL    = 10,
    PREC_LESS_THAN    = 10,
    PREC_GREATER_THAN = 10,

    PREC_PLUS     = 20,
    PREC_MINUS    = 20,
    PREC_DIVIDE   = 40,
    PREC_MULTIPLY = 40,
};

bin_op_prec get_bin_op_prec(const lexer_token& tok);
