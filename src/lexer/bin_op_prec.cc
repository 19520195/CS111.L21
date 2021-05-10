#include "bin_op_prec.hh"

bin_op_prec get_bin_op_prec(const lexer_token& tok) {
    switch (tok) {
        case lexer_token::NOT: return PREC_NOT_EQUAL;
        default              : return PREC_NONE;
    }
}
