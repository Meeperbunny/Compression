cc_binary(
    name = "main",
    srcs = ["main.cc"],
)

cc_library(
    name = "types",
    hdrs = ["types.h"],
)

cc_library(
    name = "huffman",
    srcs = ["huffman.cc"],
    hdrs = ["huffman.h"],
    deps = [":types"],
)

cc_test(
    name = "huffman_test",
    size = "small",
    srcs = ["huffman_test.cc"],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        ":huffman",
    ],
    data = ["//files:test_files"],
)