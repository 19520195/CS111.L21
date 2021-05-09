#include "parser.hh"

parser::parser(std::unique_ptr<lexer> lexer) : m_lexer(std::move(lexer)) {
    // Parser::Parser
}

lexer* parser::getlexer() {
    return m_lexer.get();
}

std::unique_ptr<expr_ast> parser::parse_number_expr() {
    return std::move(std::unique_ptr<number_expr>(new number_expr(m_lexer->get_number_value())));
}

std::unique_ptr<expr_ast> parser::parse_identifier_expr() {
    const std::string value = m_lexer->get_identifier_value();
    return std::move(std::unique_ptr<identifier_expr>(new identifier_expr(value)));
}

std::unique_ptr<expr_ast> parser::parse_primary() {
    switch (m_lexer->get_last_token()) {
        case TOKEN_NUMBER    : return parse_number_expr();
        case TOKEN_IDENTIFIER: return parse_identifier_expr();
    }

    return nullptr;
}

std::unique_ptr<expr_ast> parser::parse_expression() {
    std::unique_ptr<expr_ast> shift_left = parse_primary();
    return shift_left ? parse_bin_oper_right(0, std::move(shift_left)) : nullptr;
}

std::unique_ptr<expr_ast> parser::parse_bin_oper_right(int expr_prec, std::unique_ptr<expr_ast> shift_left) {
    // // If this is a binop, find its precedence.
    while (true) {
        int token_prec = (int)_get_precedence(m_lexer->get_last_token());
        // If this is a binop that binds at least as tightly as the current binop,
        // consume it, otherwise we are done.
        if (token_prec < expr_prec)
        return shift_left;

        // Okay, we know this is a binop.
        int bin_op = (int)m_lexer->get_last_token();

        // Parse the primary expression after the binary operator.
        std::unique_ptr<expr_ast> shift_right = this->parse_primary();
        if (!shift_right) {
            return nullptr;
        }

        // If BinOp binds less tightly with RHS than the operator after RHS, let
        // the pending operator take RHS as its LHS.
        int next_prec = _get_precedence(m_lexer->get_last_token());
        if (token_prec < next_prec)
            if (!(shift_right = this->parse_bin_oper_right(token_prec + 1, std::move(shift_right))))
                return nullptr;

        // Merge LHS/RHS.
        shift_left = std::unique_ptr<bin_expr>(new bin_expr((precedence)(bin_op), std::move(shift_left), std::move(shift_right)));
    }

    return nullptr;
}

void parser::parse_if_expr() {
    std::vector<expr_ast*> exprs;
    for (token token; (token = m_lexer->get_next_token()) != TOKEN_THEN; ) {
        switch (token) {
            case TOKEN_IDENTIFIER:
                exprs.emplace_back(new variable_expr(m_lexer->get_identifier_value()));
                break;

            default:
                break;
        }
    }

    std::cout << "Expr: " << exprs.size() << "\n";
    std::cout << (int)m_lexer->get_last_token() << ": ";
    // std::cout << (int)TOKEN_THEN << "\n";

    std::vector<expr_ast*> block_lines;
    while ((m_lexer->get_next_token()) != TOKEN_END) {
        std::cout << "Parsing: " << m_lexer->get_identifier_value() << "\n";
    }
}

void parser::parse() {
    while (true) {
        token current_token = m_lexer->get_next_token();
        if (current_token == END_OF_FILE) {
            std::cout << "Successful parsed!\n";
            break;
        }

        switch (current_token) {
            case TOKEN_IF: parse_if_expr(); return;
            default:
                break;
        }

        if (current_token == CHARACTER) {
            std::cout <<  m_lexer->get_line()  << ":"
                      <<  m_lexer->get_index() << ": ";
            std::cout << "Unexpected character" << std::endl;
            m_lexer->get_next_char();
            return;
        }
    }
}
