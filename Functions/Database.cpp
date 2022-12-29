#include "../Headers/Database.h"
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

Database::Database() {
    
}
int nameExist2(std::string s, std::string path) {
    ifstream myf;
    std::string l;
    int off;

    myf.open(path);
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

bool IsPathExist2(const std::string &s)
{
  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}

std::string Database::getRelative() {
    return relativePath;
}
void Database::addCollection(std::string ColName, Database &d)
{
    // initialize a new Collection
    Collection *newCol = new Collection();
    // add collection to vector of collections
    newCol->setColName(ColName);
    newCol->setParentDB(d.getDBName());
    d.Cols.push_back(*newCol);
    

    //when creating a collection, create a new folder inside specific DB folder
    int isCreated;

    //check if collection exists on computer
    //DB1/Col1/data1.json
    std::string path = d.getDBName() + "/" + ColName;
    if(IsPathExist2(path)== 0) {
        //if col not there...
        isCreated = mkdir(path.c_str(), 0777);
        relativePath = path;

    }
    
    
//fixed bug: already exists: file corrupted
//when adding collections to databases
        //also add to data_folders/DATABASENAME.txt
        std::string temp1;
        temp1 = "data_folders/" + d.getDBName() + ".txt";
        
        //if col doesnt exist only then add
        int x = nameExist2( ColName ,temp1);
        if(!x) {
            std::ofstream out2;
            out2.open(temp1, std::ios::app);
            out2 << ColName << std::endl;
            out2.close();
        }
        
        std::ofstream out4;
        std::string p2;
        p2 = "col_folder/" + ColName + ".txt";
        //add nothing to it but create it
        out4.open(p2, std::ios::app);
        out4.close();

        //only add collection if doesnt exist

    if(isCreated == -1) {
        std::cout << "Error creating collection in database\n" << endl;
    }
    else {
        // dir created
    }
}   



void Database::updateCollection(std::string key, std::string newVal) {
    //find all collections that have the key and update
    auto itr = Cols.begin();
    
    for(; itr != Cols.end(); itr++) {
        auto itr2 = itr->Docs.begin();
        for(; itr2 != itr->Docs.end(); itr2++) {
            //Update(itr2->getFileName(), key, newVal);
        }

    }
}
void replaceLine(std::string dbName, std::string file, std::string line) {
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



void addToEnd(std::string file, std::string newLine) {
      std::ofstream out;
      out.open(file, std::ios::app);
      out << newLine << std::endl;
      out.close();
}
void Database::updateData(std::string oldName, std::string newName) {

    //change db name in vectorDB.txt
    replaceLine(getDBName(), "vectorDB.txt", newName);

    /*
    //rename db folder/directory on pc
    std::string s = getDBName();
    std::string k = newName;
    std::string oldDir = s + "/";
    std::string newDir = k + "/";
    std::rename(oldDir.c_str(), newDir.c_str());
    */
   
    //rename "database_name.txt"
    std::string oldD = "data_folders/" + getDBName() + ".txt";
    std::string newD = "data_folders/" + newName + ".txt";
    std::rename(oldD.c_str(), newD.c_str());
    
    //rename Database object name done in main
    setDBName(newName);
    

}
void Database::deleteCollection(string ColName)
{
    int count = 0;
    for(int i =0; i < Cols.size(); i++){
        if(Cols[i].getName() == ColName){
            Cols.erase(Cols.begin() + i);
            count = 1;
            remove(ColName.c_str());
        }
    if(count){
        cout << "Successfully delete the collection." << endl;
        }
    else{
        cout << "Cannot find the collection." << endl;
    }
    }
}

void Database::readCollection(string key)
{
    int count = 0;
    for(int i =0; i < Cols.size(); i++){
        if(Cols[i].getName() == key){
            cout << Cols[i].getName() << endl;
            count ++;
        }
    } //new change
    if(count){
        cout << "Successfully found the collection." << endl;
        }
    else{
        cout << "Cannot find the collection." << endl;
    }
    
}

void Database::print_Collections() { //of specific database
        for(int i = 1; i < Cols.size() + 1; i++) {
            std::cout << i << ")" << " " << Cols[i].getName() << "\n";
        }
}

Collection& Database::returnCol(std::string name)  {
        auto itr = Cols.begin();
        for(; itr != Cols.end(); itr++) {
            if(name == itr->getName()) {
                return *itr;
            }
        }
       
}

void Database::setDBName(std::string name) {
        DatabaseName = name;
}

std::string Database::getDBName() {
    return DatabaseName;
}


std::ostream & operator<<(std::ostream & o, Database n)
{
    auto itr = n.Cols.begin();
   
    int i = 1;
    for( ; itr !=  n.Cols.end(); itr++) {
        o << i << ")" << " " << itr->getName() << "\n";
        i++;
    }
    
  return o;
}