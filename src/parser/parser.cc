#include "parser.hh"

parser::parser(std::unique_ptr<lexer> lexer) : m_lexer(std::move(lexer)) {
    // Parser::Parser
}

lexer* parser::getlexer() {
    return m_lexer.get();
}

std::unique_ptr<expr_ast> parser::parse_number_expr() {
    return std::make_unique<number_expr>(m_lexer->get_number_value());
}

std::unique_ptr<expr_ast> parser::parse_paren_expr() {
    std::unique_ptr<expr_ast> expr = parse_expr();
    if (expr == nullptr) {
        return nullptr;
    }

    if (m_lexer->get_next_token() != lexer_token::CLOSE_PAREN) {
        throw std::logic_error("Expected ')'");
    }

    return expr;
}

std::unique_ptr<expr_ast> parser::parse_identifier_expr() {
    const std::string value = m_lexer->get_identifier_value();
    return std::make_unique<identifier_expr>(value);
}

std::unique_ptr<expr_ast> parser::parse_primary() {
    switch (m_lexer->get_last_token()) {
        case lexer_token::NUMBER    : return parse_number_expr();
        case lexer_token::IDENTIFIER: return parse_identifier_expr();
        case lexer_token::OPEN_PAREN: return parse_paren_expr();
    }

    return nullptr;
}

std::unique_ptr<expr_ast> parser::parse_expr() {
    std::unique_ptr<expr_ast> shift_left = parse_primary();
    if (shift_left == nullptr)
        return nullptr;
    return parse_bin_op(0, std::move(shift_left));
}

std::unique_ptr<expr_ast> parser::parse_bin_op(int expr_prec, std::unique_ptr<expr_ast> shift_left) {
    // If this is a binop, find its bin_op_prec.
    while (true) {
        bin_op_prec token_prec = get_bin_op_prec(m_lexer->get_next_token());
        if (token_prec < expr_prec)
            return shift_left;

        // Okay, we know this is a binop.
        int bin_op = (int)m_lexer->get_last_token();

        // Parse the primary expression after the binary operator.
        m_lexer->get_next_token();
        std::unique_ptr<expr_ast> shift_right = this->parse_primary();
        if (!shift_right) {
            return nullptr;
        }

        // If BinOp binds less tightly with RHS than the operator after RHS, let
        // the pending operator take RHS as its LHS.
        int next_prec = get_bin_op_prec(m_lexer->get_last_token());
        if (token_prec < next_prec)
            if (!(shift_right = this->parse_bin_op(token_prec + 1, std::move(shift_right))))
                return nullptr;

        // Merge LHS/RHS.
        shift_left = std::unique_ptr<bin_expr>(new bin_expr((bin_op_prec)(bin_op), std::move(shift_left), std::move(shift_right)));
    }

    return nullptr;
}

std::unique_ptr<expr_ast> parser::parse_if_expr() {
    m_lexer->get_next_token();

    std::unique_ptr<expr_ast> if_cond = parse_expr();
    return if_cond;
}

void parser::live_parse() {
    lexer_token current_token = m_lexer->get_next_token();
    if (current_token == lexer_token::END_OF_FILE) {
        std::cout << "Successful parsed!\n";
        return;
    }

    try {
        switch (current_token) {
            case lexer_token::IF: parse_if_expr(); break;

            default:
                std::cout << m_lexer->get_line()  << ":"
                          << m_lexer->get_index() << ": "
                          << "Unexpected character" << std::endl;
                m_lexer->get_next_char();
        }
    } catch (const std::exception& ex) {
        std::cerr << m_lexer->get_line()  << ":"
                  << m_lexer->get_index() << ": "
                  << ex.what() << std::endl;
    }
}
