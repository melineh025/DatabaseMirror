#include "main.cpp"
#include <gtest/gtest.h>
#include <Collection.h>
#include <Document.h>
#include <Create.h>

// Testing basic CRUD functionality
// This tests to see if a new collection can be created
// to the database
TEST(CreateTest, createCollection) {
    Database db1 = new Database();
    Collection c = new Collection();
    bool isCollectionMade = db1.hasMember(c);
    ASSERT_EQ(isCollectionMade, 1);
}

// This tests to see if a new document can be created and subsequently added to
// the proper collection
TEST(CreateTest, createDocument) {
    Database db1 = new Database();
    Collection c = new Collection();
    db1.addCollection(c);
    Document d1 = c.insertDoc();
    bool isDocMade = c.hasMember(d1);
    ASSERT_EQ(isDocMade, 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}