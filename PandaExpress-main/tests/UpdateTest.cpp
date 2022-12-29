//Melineh Mansour- cs 179k
#include <gtest/gtest.h>
#include <Collection.h>
#include <Document.h>
#include <Update.h>

TEST(UpdateTest, CheckExistence) {
    Collection c = new Collection();
    Document d1 = c.insertDoc();
    bool isPresent = c.hasMember(d1);
    ASSERT_EQ(isPresent, 1);
}

TEST(UpdateTest, UpdateCollection){
    Collection c = new Collection();
    Document d1 = c.insertDoc();
    Document d2 = c.insertDoc();
    string prevName = c.getName();
    c.updateCollection();
    string newName = c.getName();
    ASSERT_NEQ(prevName, newName);
}
TEST(UpdateTest, UpdateDocument) {
    Collection c = new Collection();
    Document d1 = c.insertDoc();
    string newField = "{ id: 200}";
    d1.updateDocument(newField);
    ASSERT_EQ(d1.getName(), "{ id: 200}");
}
TEST(UpdateTest, UpdateDatabase) {
    Database db1 = new Database();
    Collection c1 = new Collection();
    Collection c2 = new Collection();
    db1.addCollection(c1);
    db1.addCollection(c2);
    string db1Name = db1.getName();
    db1.updateDatabase("db2");
    ASSERT_NEQ(db1Name, "db2");
}
TEST(UpdateTest, UpdateField) {
    Collection c = new Collection();
    Document d1 = c.insertDoc();
    string member = "\"hello": "world\"";
    string key = d1.getKey(member);
    d1.updateField(key);
    ASSERT_EQ(hasMember(member), "\"hello": "world\"");
}
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}