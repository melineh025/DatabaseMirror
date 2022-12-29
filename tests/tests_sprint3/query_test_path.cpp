#include "main.cpp"
#include <gtest/gtest.h>
#include <Collection.h>
#include <Document.h>
#include <Create.h>

// Find if the key is in the document
TEST(FindKey, FindMemberInDoc)
{
    Database db1 = new Database();
    Collection c = new Collection();
    Doc d = new Doc();
    bool f = d.hasMember(key);
    ASSERT_EQ(f, 1);
}

// Find the path
TEST(FindPath, FindPathOfKV)
{
    Database db1 = new Database();
    Collection c = new Collection();
    db1.addCollection(c);
    Document d1 = c.insertDoc();
    ASSERT_EQ("path\of\KV", path);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
