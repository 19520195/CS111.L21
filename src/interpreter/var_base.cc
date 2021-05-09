#include "var_base.hh"

unsigned int var_base::get_value(const std::string& name) const {
    return m_variable.count(name) ? m_variable.at(name) : 0;
}

void var_base::set_value(const std::string& name, const unsigned int& value) {
    m_variable[name] = value;
}
