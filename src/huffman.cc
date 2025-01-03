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

bitstring Huffman::Encode(std::string text) {
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
        auto [freqFirst, firstNode] = Q.top();
        Q.pop();
        auto [freqSecond, secondNode] = Q.top();
        Q.pop();

        HuffmanNode* newNode = new HuffmanNode(freqFirst + freqSecond);
        newNode->left = firstNode;
        newNode->right = secondNode;

        Q.push({newNode->frequency, newNode});
    }
    root = Q.top().second;

    // Now that we have a tree generate binary encodings.
    symbolMap = std::unordered_map<char, std::string>{};
    fillSymbolMap(root, symbolMap);

    // Now that we have the symbol map, encode the text as a vector of bytes.
    std::string binaryString{};
    for(const auto& c : text) {
        binaryString += symbolMap[c];
    }
    bitstring b = BytestringFromString(binaryString);

    // If we are decoding and encoding, ensure that we only do one at a time.
    return b;
}

std::string Huffman::Decode(bitstring bstring) {
    std::string text{};

    // Invert symbol map.
    std::unordered_map<std::string, char> symbolMapInverse;
    for(auto &[k, v] : symbolMap) {
        symbolMapInverse[v] = k;
    }

    std::string current{};
    for(const auto& b : bstring) {
        current += b ? "1" : "0";
        auto it = symbolMapInverse.find(current);
        if (it != symbolMapInverse.end()) {
            // Is found in the mapping, so decode it.
            text += it->second;
            current = "";
        }
    }
    if (current.size())
        throw std::runtime_error("Error decoding the given bitstring");

    return text;
}