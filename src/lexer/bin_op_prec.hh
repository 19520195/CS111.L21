#pragma once

enum bin_op_prec : int {
    NONE = 0,

    NOT_EQUAL    = 10,
    LESS_THAN    = 10,
    GREATER_THAN = 10,

    PLUS     = 20,
    MINUS    = 20,
    DIVIDE   = 40,
    MULTIPLY = 40,
};
