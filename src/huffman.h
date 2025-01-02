#ifndef HUFFMAN
#define HUFFMAN

#include <string>
#include <vector>

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
public:
    bytestring Encode(std::string text);
    std::string Decode(std::string text);
};

#endif /* HUFFMAN */