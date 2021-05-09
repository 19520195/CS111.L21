#pragma

#include <map>

class var_base {
public:
    var_base() = default;
    ~var_base() = default;

    unsigned int get_value(const std::string& name) const;
    void set_value(const std::string& name, const unsigned int& value);

private:
    std::map<std::string, unsigned int> m_variable;
};
