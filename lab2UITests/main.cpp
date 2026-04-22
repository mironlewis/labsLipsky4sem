#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(output) = "xml:test_report.xml";
    return RUN_ALL_TESTS();
}