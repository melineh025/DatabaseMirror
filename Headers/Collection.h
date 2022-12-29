#ifndef SYSTEM_H
#define SYSTEM_H


#include "../Headers/Doc.h"
#include <vector>
class Doc;


class Collection {
    
    public:
    Collection();
    std::string parentDB;
    std::string  relativePath;
    void setParentDB(std::string);
    std::string getparentDB();
    std::vector<Doc> Docs;
    std::string CollectionName;
    friend std::ostream & operator<<(std::ostream & o, Collection n);
    std::string getName();
    void addDocument(std::string DocName, Collection &c);
    void deleteDocument(std::string DocName);
    void updateDoc(std::string oldName, std::string newName);
    void readDoc(std::string key);
    void setColName(std::string name);
    void print_Documents();
    Doc& returnDoc(std::string name);
};
#endif