#ifndef DATABASE_H
#define DATABASE_H
#include "../Headers/Collection.h"

class Collection;

class Database {
    public:
    Database();
    std::string relativePath;
    std::string getRelative();
    std::vector<Collection> Cols;
    std::string DatabaseName;
    std::string getDBName();
    friend std::ostream & operator<<(std::ostream & o, Database n);
    void setDBName(std::string name);
    void addCollection(std::string ColName, Database &d);
    void deleteCollection(std::string ColName);
    void updateCollection(std::string key, std::string newVal);
    void readCollection(std::string key);
    void print_Collections();
    Collection& returnCol(std::string name);
    void updateData(std::string oldName, std::string s);
};

#endif