#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

// Testing on Moby Dick text.
TEST(HuffmanTest, MobyDickTest) {
    // Check that on running the huffman encoding the files are the same.
    std::ifstream file("uncompressed_files/moby.txt");
    std::stringstream buf;
    buf << file.rdbuf();
    std::string uncompressed_str = buf.str();
    // COMPRESS HERE
    std::string compressed_str(uncompressed_str);
    // Check that they are equal.
    EXPECT_EQ(uncompressed_str, compressed_str);
}