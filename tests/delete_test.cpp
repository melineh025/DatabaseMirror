#include "delete.cpp"
#include <gtest/gtest.h>

//This is the test file of delete.cpp
//We want to test by examing the counter in the function
//Suppose there are 10 documents, and each of them
//Counter equals to the amount of documents
//And current_doc is the pointer of current editing document
//If the previous one document is deleted, current_doc will increase by 1
TEST(doc_delete, delete_first_doc){
    EXPECT_EQ(1, doc_delete(1));
    EXPECT_TRUE(counter = 9);
    EXPECT_TRUE(current_doc = 1)
}

TEST(doc_delete, delete_second_doc){
    EXPECT_EQ(2, doc_delete(2));
    EXPECT_TRUE(counter = 9);
    EXPECT_TRUE(current_doc = 2)
}

TEST(doc_delete, delete_last_doc){
    EXPECT_EQ(9, doc_delete(10));
    EXPECT_TRUE(counter = 9);
    EXPECT_TRUE(current_doc = 9);
}

TEST(doc_delete, delete_2_docs){
    EXPECT_EQ(1, doc_delete(1));
    EXPECT_EQ(2, doc_delete(2));
    EXPECT_TRUE(counter = 8);
    EXPECT_TRUE(current_doc = 2);
}

TEST(doc_delete, delete_all_docs){
    EXPECT_EQ(1, doc_delete(1));
    EXPECT_EQ(1, doc_delete(1));
    EXPECT_EQ(1, doc_delete(1));
    EXPECT_EQ(1, doc_delete(1));
    EXPECT_EQ(1, doc_delete(1));
    EXPECT_EQ(1, doc_delete(1));
    EXPECT_EQ(1, doc_delete(1));
    EXPECT_EQ(1, doc_delete(1));
    EXPECT_EQ(1, doc_delete(1));
    EXPECT_EQ(1, doc_delete(1));
    EXPECT_TRUE(counter = 0);
    EXPECT_TRUE(current_doc = 0);
}