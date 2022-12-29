#ifndef DOC_H
#define DOC_H
#include "../Headers/System.h"
#include "../rapidjson/include/rapidjson/document.h"
#include "../rapidjson/include/rapidjson/writer.h"
#include "../rapidjson/include/rapidjson/stringbuffer.h"
#include "../rapidjson/include/rapidjson/prettywriter.h" 
#include "../rapidjson/include/rapidjson/filewritestream.h"
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
using namespace rapidjson;

class Doc {
    
    
    public:
    std::string colP;
    std::string dbP;
    std::string givecol();
    std::string giveparent();
    void setcol(std::string);
    void setparent(std::string);
    Doc();
    std::string fileName;
    std::string getFileName();
    void addKV(std::string key, std::string value);
    void updateKV(std::string key, std::string newVal);
    void deleteKV(std::string key);
    void print_KV(std::string key);
    void setFileName(std::string name);
    void rename(std::string, std::string);
    void findpath(std::string filePath, std::string key3);
};
#endif