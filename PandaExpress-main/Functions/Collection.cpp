#include "../Headers/Collection.h"
#include <fstream>
#include <filesystem>
#include <iostream>

Collection::Collection() {
    
}
void Collection::setParentDB(std::string name) {
    parentDB = name;
}

int nameExist3(std::string s, std::string path) {
    std::ifstream myf;
    std::string l;
    int off;

    myf.open(path);
    if(myf.is_open()) {
        while(!myf.eof()) {
            getline(myf, l);
            if((off = l.find(s,0)) != std::string::npos) {
                //found
                myf.close();
                return 1;
            }
            else {
                //not found
            }
        }

    }
   else {
        //cant open file
    }
    myf.close();

    return 0;
}

bool DoesFileExist (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

void Collection::addDocument(std::string DocName, Collection &c)
{
    
    // initialize a new Document
    Doc *newDoc = new Doc();
    newDoc->setFileName(DocName);
    newDoc->setcol(c.getName());
    newDoc->setparent(c.getparentDB());
    // add document to vector of documents
    c.Docs.push_back(*newDoc);
    
    std::string w = c.getparentDB() + "/" + c.getName()+ "/" + DocName;

    //check if file exists on pc
    bool doesExist = false;
    doesExist = DoesFileExist(w);
    if(doesExist == false) {
        //create new file and write to it
        std::ofstream of;
        of.open(w);
        of << "{}";
        of.close();
    }

    std::string p = "col_folder/" + c.getName() + ".txt";
    int inFile = nameExist3(DocName,p);
    if(!inFile) {
        std::ofstream out;
        out.open(p, std::ios::app);
        //at end of file add json name
        out << DocName << std::endl;
        out.close();
    }
 
   
}


std::string Collection::getparentDB() {
    return parentDB;
}
void Collection::updateDoc(std::string oldName, std::string newName) {
    // rename document
    //int rename( const char *oldname, const char *newname );
    std::string w = getparentDB() + "/" + getName()+ "/" + oldName;
    std::string k = getparentDB() + "/" + getName()+ "/" + newName;
    int x = rename(w.c_str(), k.c_str());

}

void Collection::deleteDocument(std::string DocName)
{
    DocName.append(".json");
    int count = 0;
    for(int i =0; i < Docs.size(); i++){
        if(Docs[i].getFileName() == DocName){
            Docs.erase(Docs.begin()+ i);
            count = 1;
            remove(DocName.c_str());
        }
    }
    if(count){
        std::cout << "Successfully delete the document.\n";
    }
    else{
        std::cout << "Cannot find the document.\n";
    }
}

void Collection::readDoc(std::string key)
{
    int count = 0;
    for(int i =0; i < Docs.size(); i++){
        if(Docs[i].getFileName() == key ){
            std::cout << Docs[i].getFileName() << std::endl;
            count ++;
        }
    }
    if(!count){
        std::cout << "Couldn't find such document.\n";
    }
    else{
        std::cout << "Successfully found the document.\n";
    }
}

std::string Collection::getName() {return CollectionName;}

Doc& Collection::returnDoc(std::string name)  {
        auto itr = Docs.begin();
        for(; itr != Docs.end(); itr++) {
            if(name == itr->getFileName()) {
                return *itr;
            }
        }
}

void Collection::setColName(std::string name) {CollectionName = name;}

std::ostream & operator<<(std::ostream & o, Collection n)
{
    auto itr = n.Docs.begin();
    int i = 1;
    for( ; itr != n.Docs.end(); itr++) {
        o << i << ")" << " " << itr->getFileName() << "\n";
        i++;
    }
    
  return o;
}