#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <stdexcept>

#include "src/huffman.h"
#include "src/types.h"

// Testing on Moby Dick text.
TEST(HuffmanTest, MobyDickTest) {
    // Get the base of the runfiles directory
    // const char* test_srcdir = std::getenv("TEST_SRCDIR");
    // if (!test_srcdir) {
    //     throw std::runtime_error("TEST_SRCDIR environment variable not set");
    // }

    // Construct the path to moby.txt using the manifest mapping
    std::string filepath = "C:/users/ian mckibben/compression/files/moby.txt";

    // Open the file
    std::ifstream file(filepath);

    if (!file.is_open()) {
        throw std::runtime_error("File cannot be opened");
    }
    std::stringstream buf;
    buf << file.rdbuf();
    std::string s = buf.str();

    Huffman h;

    // Check that they are equal.
    bitstring s_encoded = h.Encode(s);
    EXPECT_EQ(s, h.Decode(s_encoded));
}