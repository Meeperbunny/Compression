#ifndef HUFFMAN
#define HUFFMAN

#include <string>
#include <vector>
#include <unordered_map>

#include "src/types.h"

struct HuffmanNode {
    double frequency;
    char symbol;
    HuffmanNode *left{}, *right{};
    HuffmanNode(double _frequency, char _symbol='\0')
        : frequency(_frequency), symbol(_symbol) {}
};

class Huffman {
private:
    HuffmanNode* root;
    std::vector<HuffmanNode*> nodes;
    std::unordered_map<char, std::string> symbolMap;
public:
    bitstring Encode(std::string);
    std::string Decode(bitstring);
};

#endif /* HUFFMAN */