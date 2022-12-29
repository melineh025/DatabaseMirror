#pragma once
#include <vector>
#include <iostream>
#include <iterator>
#include "../Headers/Database.h"
#include <fstream>
#include <sstream> 
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include "../rapidjson/include/rapidjson/document.h"
#include "../rapidjson/include/rapidjson/writer.h"
#include "../rapidjson/include/rapidjson/stringbuffer.h"
#include "../rapidjson/include/rapidjson/prettywriter.h" 
#include "../rapidjson/include/rapidjson/filewritestream.h"
using namespace rapidjson;

class Database;

class System{
    
    public:
    System();
    std::vector<Database> DBs;
    void addDB(std::string DBName);
    int getSize() {return DBs.size();};
    friend std::ostream & operator<<(std::ostream & o, System n);

    void deleteDB(std::string DBName);
    void updateDB(std::string newVal);
    void readDB(std::string key);
    void print_Databases();
    Database& returnDatabase(std::string name);

};


void Update(std::string fileName, std::string key, std::string newValue) {
    std::ifstream jsonFile(fileName);
    std::stringstream file_contents;
    file_contents <<  jsonFile.rdbuf();
    rapidjson::Document myDoc;
    myDoc.Parse(file_contents.str().c_str());

    //check if key exists and write to file
    if(myDoc.HasMember(key.c_str())){
        
        const char *c  = key.c_str();

        myDoc[c] = StringRef(newValue.c_str());
        FILE* fp = fopen(fileName.c_str(), "w"); 
        char writeBuffer[65536];
        rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
        Writer<FileWriteStream> writer(os);
        myDoc.Accept(writer);
        fclose(fp);
     }
    

}




