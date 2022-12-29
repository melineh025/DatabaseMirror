
#include "../Headers/System.h"
#include <unistd.h> 
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "../rapidjson/include/rapidjson/document.h"
#include "../rapidjson/include/rapidjson/writer.h"
#include "../rapidjson/include/rapidjson/stringbuffer.h"
#include "../rapidjson/include/rapidjson/prettywriter.h" // for stringify JSON
#include "../rapidjson/include/rapidjson/filewritestream.h"
#include "../rapidjson/include/rapidjson/pointer.h"
#include <filesystem>

using namespace rapidjson;

using namespace std;

System::System() {

}
int nameExist(std::string s) {
    ifstream myf;
    std::string l;
    int off;

    myf.open("vectorDB.txt");
    if(myf.is_open()) {
        while(!myf.eof()) {
            getline(myf, l);
            if((off = l.find(s,0)) != string::npos) {
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


bool IsPathExist(const std::string &s)
{
  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}
void System::addDB(std::string DBName)
{
    // initialize a new Database
    Database *newDB = new Database();
    // add database to vector of databases
    newDB->setDBName(DBName);
    DBs.push_back(*newDB);

    //create a new database/directory  folder
    int isCreated;

    if(IsPathExist(DBName)== 0) { 
        isCreated = mkdir(DBName.c_str(), 0777);
        
        //only add if database doesnt exist in vectorDB.txt
        int doesE = nameExist(DBName);
        
        if(!doesE){
            std::ofstream out;
            out.open("vectorDB.txt", std::ios::app);
            out << DBName << std::endl;
            out.close();    
        }

        
    }
    
}

 void System::print_Databases() {
        for(int i = 1; i < DBs.size() + 1; i++) {
            std::cout << i << ")" << " " << DBs[i].getDBName() << "\n";
        }
    }
Database& System::returnDatabase(std::string name)  {
        auto itr = DBs.begin();
        for(; itr != DBs.end(); itr++) {
           
            if (name == itr->getDBName()) {
                return *itr;
            }
        }

    }


void System::updateDB(std::string newName) {
    //nada

}

void System::readDB(string key)
{
    int count = 0;
    for(int i =0; i < DBs.size(); i++){
        if(DBs[i].getDBName() == key){
            cout << DBs[i].getDBName() << endl;
            count ++;
        }
    }
    if(!count){
        cout << "Couldn't find such database.";
    }
    else{
        cout << "Successfully found the database.";
    }
}
void replaceL(std::string dbName, std::string file, std::string line) {
    std::ofstream temp;
    temp.open("temp.txt", std::ios::app);

    std::string str; 
    std::string input;
    std::fstream f(file);
   while(std::getline(f, str)){

        if(str == dbName) {
            temp << line << std::endl;
        }
        else if(str == "") {
            temp << "EMPty" << std::endl;
        }
        else {
            temp << str << std::endl;
        }
        
    }
    f.close();
    temp.close();

   std::remove(file.c_str()); //delete old file
   std::ifstream ini_file;
   std::ofstream out_file;

    ini_file.open("temp.txt", std::ios::app);

   out_file.open(file);

    std::string l;

    if (ini_file && out_file) {
  
        while (getline(ini_file, l)) {
              out_file << l << "\n";
        }
        //std::cout << "Copy Finished \n";
    }
    std::remove("temp.txt"); //delete temp file

}


void System::deleteDB(std::string DBName)  {
    
   /* std::string temp = DBName + "/";
    std::filesystem::remove_all(temp);
*/
    //remove from object structure
    int count = 0;
    for(int i =0; i < DBs.size(); i++){
        if(DBs[i].getDBName() == DBName){
            DBs.erase(DBs.begin()+ i);
            count = 1;
            remove(DBName.c_str());
        }
    }
    
    //remove from vectorDB.txt
    
    //remove from data_folders/ - its db.txt
   //remove directory from pc
    if(count){
        cout << "Successfully delete the database." << endl;
    }
    else{
        cout << "Cannot find the database." << endl;
    }
}

std::ostream & operator<<(std::ostream & o, System n)
{
    auto itr = n.DBs.begin();
    int i = 1;
    for( ; itr != n.DBs.end(); itr++) {
        o << i << ")" << " " << itr->getDBName() << "\n";
        i++;
    }
    
  return o;
}



//normal query function

void print_query(std::string f, std::string key)
{
    //std::string f =  giveparent() + "/" + givecol() + "/" + getFileName();
    
    std::ifstream jsonFile(f);
    std::stringstream file_contents;
    file_contents <<  jsonFile.rdbuf();
    rapidjson::Document myDoc;
    myDoc.Parse(file_contents.str().c_str());
    // define a string for position searching
    string str4=file_contents.str().c_str() ;
	int doc_read3;

    string a = "/";
    string b = key;
    string c = a+b;
    string d;
    string e = c + a + d;
    
    Value* v = Pointer(c.c_str()).Get(myDoc);


    Value::ConstMemberIterator itr = myDoc.FindMember(b.c_str()); //search for key from the whole document
    if (itr != myDoc.MemberEnd()){
        //There are different situations even if we could find the key.
        //1: The key has only 1 value
        if(v->IsArray() == false){
            //1.1: The key has only 1 value, and it's a key.
            doc_read3 = str4.find(key);
            int ss = key.size(); 
            char ttt = '{';              
            //The thinking is to locate the position of the searching key and see if there's "{" after it
            if(str4.at(doc_read3 + ss + 2) == ttt){    // Need a way to determine if it's a key. Right now just assume it's a key. Change 1/0 to test.  HELP~~~~~~~~~~~~~~
                string key3;
                cout << "What's the key you want to find in " << b << " ?" << endl;
                cin >> key3;
                Value::ConstMemberIterator itr1 = v->FindMember(key3.c_str());
                if(itr1 != v->MemberEnd()){
                    cout << "Key founded. Display the value: " << endl;
                    cout << "\"" << key3 << "\": "; 
                    string j = c + a + key3;
                    Value* x = Pointer(j.c_str()).Get(myDoc);
                    cout << x->GetString() << endl;
                }
                else{
                    cout << "Cannot find the key." << endl;
                }
            }
            //1.2: The key has only 1 value, and the value is not a key.
            else{
                cout << "\"" << b << "\": " << v->GetString();
            }            
        }
        //2: The key has multiple values
        else{
            //2.1: The key has multiple values, and they are not keys.
            doc_read3 = str4.find(key);
            int ss = key.size(); 
            char ttt = '{';    
            //The thinking is to locate the position of the searching key and see if there's "{" after it
            if(str4.at(doc_read3 + ss + 3) != ttt){    // Need a way to determine if elements in array are keys. Change 1/0 to test.   HELP~~~~~~~~~~~~~~~~~~
                int count = v->GetArray().Size();
                cout << "\"" << b << "\": ";
                for(int i=0; i<(count-1); i++){
                    string f = to_string(i);
                    string g = c + a + f;
                    Value* x = Pointer(g.c_str()).Get(myDoc);
                    cout << x->GetString() << ", ";
                } 
                string h = to_string(count-1);
                string k = c + a + h;
                Value* x = Pointer(k.c_str()).Get(myDoc);
                cout << x->GetString();          
            }
            //2.2: The key has multiple values, and they are keys. 
            else{
                cout << "What's the key you want to find in " << b << " ?" << endl;
                string key4;
                cin >> key4;
                int count = v->GetArray().Size();
                bool K = true;
                int count2 = 0;                
                for(int i=0; i<count; i++){ // First loop to find the key in the second level
                    string l = to_string(i);
                    string m = c + a + l;
                    Value* x = Pointer(m.c_str()).Get(myDoc);
                    Value::ConstMemberIterator itr3 = x->FindMember(key4.c_str());
                    if(itr3 != x->MemberEnd()){  // If we found the key, we need to check if it's an array.
                        m = m + a + key4;
                        Value* z = Pointer(m.c_str()).Get(myDoc);
                        if(z->IsArray()){   // If the key is an array, go into elements in the array to output k-v
                            int count1 = z->GetArray().Size();
                            for(int j=0; j< count1; j++){
                                count2 ++;
                                string o = to_string(j);
                                string p = m + a + o;
                                Value* zz = Pointer(p.c_str()).Get(myDoc);
                                if(K){
                                    cout << "\"cities\": ";
                                    K = false;
                                }
                                cout << zz->GetString();
                                if(count2 <((count * count1))){
                                    cout << ", ";
                                }
                                
                            }
                        }
                        else{    // If not an array, just use getstring() to output the value
                            if(K){
                                cout << "\"" << key4 << "\": ";
                            }
                            K = false;
                            cout << z->GetString();
                            if(i < (count - 1)){
                                cout << ", ";
                            }
                        }
                    }
                    else{  // If can't find the key
                        cout << "Cannot find the key." << endl;
                    }
                }
            }
        }                
    }
    else{  // If can't find the key
        cout << "Key not found." << endl;
    }
    
    FILE* fp = fopen(f.c_str(), "w"); 
        char writeBuffer[65536];
        rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
        Writer<FileWriteStream> writer(os);
        myDoc.Accept(writer);
        fclose(fp);

}
