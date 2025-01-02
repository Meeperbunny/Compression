#ifndef TYPES
#define TYPES

#include <vector>
#include <string>
#include <stdexcept>

typedef std::vector<char> bytestring;

inline bytestring BytestringFromString(std::string s) {
    int ind = 0;
    bytestring b;
    for(const auto &c : s) {
        if (c != '0' && c != '1') {
            throw std::runtime_error("Bytestring must be parsed from a string containing only '0' and '1', but it is: " + std::string(1, c));
        }
        bool bit = c == '1';

        if (ind == 0) {
            b.push_back(0);
        }
        b[b.size() - 1] |= bit << ind;

        // Increment and wrap
        ind = (ind == 7) ? 0 : ind + 1;
    }
    return b;
}

#endif /* TYPES */