//Ligang_Zou_CS179K

#include "read.cpp"
#include <gtest/gtest.h>

//This is the test cases of read.cpp
//We want to test by examing the counter in the function
//Assume that there are 10 documents. Alpha, beta, gamma, delta, epsilon are their keys 
//Each key will appear in two files
//Counter counts the amount of the read document

TEST(doc_read, doc_read_alpha) {
    ASSERT_EQ(0, doc_read(alpha));
    ASSERT_EQ(1, doc_read(alpha));
    ASSERT_EQ(2, doc_read(alpha));
    EXPECT_TRUE(counter = 2);
}

TEST(doc_read, doc_read_beta) {
    ASSERT_EQ(0, doc_read(beta));
    ASSERT_EQ(1, doc_read(beta));
    ASSERT_EQ(2, doc_read(beta));
    EXPECT_TRUE(counter = 2);
}

TEST(doc_read, doc_read_gamma&&delta) {
    ASSERT_EQ(0, doc_read(gamma && delta));
    ASSERT_EQ(1, doc_read(gamma && delta));
    ASSERT_EQ(2, doc_read(gamma && delta));
    ASSERT_EQ(3, doc_read(gamma && delta));
    ASSERT_EQ(4, doc_read(gamma && delta));
    EXPECT_TRUE(counter = 4);
}

TEST(doc_read, doc_read_zeta) {
    ASSERT_EQ(0, doc_read(zeta));
    ASSERT_EQ(1, doc_read(zeta));
    ASSERT_EQ(2, doc_read(zeta));
    EXPECT_TRUE(counter = 0);
}

TEST(doc_read, doc_read_ALL) {
    ASSERT_EQ(0, doc_read(ALL));
    ASSERT_EQ(1, doc_read(ALL));
    ASSERT_EQ(2, doc_read(ALL));
    ASSERT_EQ(3, doc_read(ALL));
    ASSERT_EQ(4, doc_read(ALL));
    ASSERT_EQ(5, doc_read(ALL));
    ASSERT_EQ(6, doc_read(ALL));
    ASSERT_EQ(7, doc_read(ALL));
    ASSERT_EQ(8, doc_read(ALL));
    ASSERT_EQ(9, doc_read(ALL));
    ASSERT_EQ(10, doc_read(ALL));
    EXPECT_TRUE(counter = 10);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
