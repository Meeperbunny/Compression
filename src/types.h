#ifndef TYPES
#define TYPES

#include <vector>
#include <string>
#include <stdexcept>

typedef std::vector<bool> bitstring;

inline bitstring BytestringFromString(std::string s) {
    bitstring b;
    for(const auto &c : s) {
        if (c != '0' && c != '1') {
            throw std::runtime_error("Bitstring must be parsed from a string containing only '0' and '1', but it is: " + std::string(1, c));
        }
        b.push_back(c == '1');
    }
    return b;
}

#endif /* TYPES */