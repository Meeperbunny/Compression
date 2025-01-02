#include "src/huffman.h"
#include "src/types.h"

#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>
#include <iostream>
#include <random>

void fillSymbolMap(HuffmanNode* node, std::unordered_map<char, std::string> &mapping, std::string s="") {
    // Check if leaf, then should map the symbol, otherwise traverse.
    if (!node->left && !node->right) {
        mapping[node->symbol] = s;
        return;
    }
    else {
        if (node->left) {
            fillSymbolMap(node->left, mapping, s + "0");
        }
        if (node->right) {
            fillSymbolMap(node->right, mapping, s + "1");
        }
    }
}

bytestring Huffman::Encode(std::string text) {
    std::unordered_map<char, double> frequencies;
    for(const auto& c : text)
        ++frequencies[c];

    // Normalize for text length.
    for(auto &[k, v] : frequencies) {
        v /= text.size();
    }

    // Construct nodes and priority queue.
    std::priority_queue<std::pair<double, HuffmanNode*>> Q;
    for(const auto &[k, v] : frequencies) {
        // Sort so that largest ones are last instead of first.
        Q.push({-v, new HuffmanNode(v, k)});
    }
    while(Q.size() > 1) {
        HuffmanNode *first;
        HuffmanNode *second;
        first = Q.top().second;
        Q.pop();
        second = Q.top().second;
        Q.pop();

        HuffmanNode* newNode = new HuffmanNode(first->frequency + second->frequency);
        newNode->left = first, newNode->right = second;

        Q.push({newNode->frequency, newNode});
    }
    root = Q.top().second;

    // Now that we have a tree generate binary encodings.
    std::unordered_map<char, std::string> symbolMap;
    fillSymbolMap(root, symbolMap);

    // Now that we have the symbol map, encode the text as a vector of bytes.
    std::string binaryString{};
    for(const auto& c : text) {
        binaryString += symbolMap[c];
    }
    bytestring b = BytestringFromString(binaryString);
    std::cerr << "Encoded original string of " << text.size() << " bytes to have " << b.size() << " bytes." << std::endl;
    return b;
}

std::string Huffman::Decode(std::string text) {
    return text;
}