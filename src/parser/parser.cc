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


std::unique_ptr<expr_ast> parser::parse_builtin_expr() {
    lexer_token builtin_token = m_lexer->get_last_token();
    if (m_lexer->get_next_token() != lexer_token::IDENTIFIER)
        throw std::logic_error("Expected a variable identifier");

    switch (builtin_token) {
        case lexer_token::INCR:
            return std::make_unique<bin_expr>(
                bin_op_prec::PLUS,
                std::make_unique<variable_expr>(m_lexer->get_identifier_value()),
                std::make_unique<number_expr>(1)
            );

        case lexer_token::DECR:
            return std::make_unique<bin_expr>(
                bin_op_prec::MINUS,
                std::make_unique<variable_expr>(m_lexer->get_identifier_value()),
                std::make_unique<number_expr>(1)
            );

        default:
            return nullptr;
    }
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
        bin_op_prec token_prec = m_lexer->get_next_token().get_prec();
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
        int next_prec = m_lexer->get_last_token().get_prec();
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

bool parser::live_parse() {
    lexer_token current_token = m_lexer->get_next_token();
    if (current_token == lexer_token::END_OF_FILE)
        return true;

    try {
        switch (current_token) {
            // case lexer_token::IF: return (bool)parse_if_expr();

            default:
                if (current_token.is_builtin()) return (bool)parse_builtin_expr();
                else {
                    std::cout << m_lexer->get_cursor_info() << ": ";
                    std::cout << "Unexpected character" << std::endl;
                }
        }
    } catch (const std::exception& ex) {
        std::cerr << m_lexer->get_cursor_info() << ": ";
        std::cerr << ex.what() << std::endl;
        return false;
    }

    // Parsed
    return true;
}
