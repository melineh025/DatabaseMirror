#include "Headers/menu.h"
#include <iostream>
#include <vector>
#include "Headers/System.h"
#include "Functions/System.cpp"
#include "Functions/Database.cpp"
#include "Functions/Collection.cpp"
#include  "Functions/Threading.cpp"
#include "Functions/Doc.cpp"

using namespace std;

enum SM_States {Main_Menu, Database_Menu, Col_Menu, Doc_Menu} SM_State;
int flag = 1;
System * Sys= new System();
Database *tempDB = new Database();
Collection *tempCol = new Collection();
Doc *tempDoc = new Doc();
std::string curDB;
std::string curCol;
std::string curDoc;
std::vector<std::string> databases;


void load() {
    //create col folder and data_folder if doesnt exist
    std::ifstream of1;
    of1.open("vectorDB.txt"); //create if not there
    of1.close();

    bool isCreated = mkdir("data_folders", 0777);
    bool isCreated2 = mkdir("col_folder", 0777);

    //read in vector of databases from vector file "vectorDB.txt"
    ifstream myfile1;
    myfile1.open("vectorDB.txt");
  
    std::string readVectorLine;
    while(getline(myfile1, readVectorLine)) {
        databases.push_back(readVectorLine);
        Sys->addDB(readVectorLine); //its going to add a new db here...
    }
    myfile1.close();

    //Collection persistence- Load in collections for every db
    //go though every file in data_folders, open by database name + .txt , each text file contains a list of its ccollections line by line
    //read through every txt file and populate its collections based on its string name

    ifstream myfile2;
    ifstream myfile3;

    for(int i = 0; i < databases.size(); i++ ) {

        tempDB = &Sys->returnDatabase(databases[i]);
        std::string tempName = "data_folders/" + databases[i] + ".txt";
        myfile2.open(tempName);

        std::string line = "";
        while(getline(myfile2, line)) {
            tempDB->addCollection(line, *tempDB);
            tempCol = &tempDB->returnCol(line);

            //check if collection belongs database[i]
            std::string isParent = tempCol->getparentDB();
            
            if(isParent == databases[i]) {
                //go through collection .txt and add .json files to col : document load in persistence 
                
                std::string line3 = "";
                std::string col_line = "col_folder/" + tempCol->getName() + ".txt";
              
                myfile3.open(col_line);

                while(getline(myfile3, line3)) {
                tempCol->addDocument(line3, *tempCol);
                }
                myfile3.close();

            }
            
        }
       // myfile2.close();

        
    }
 myfile2.close();

}



char getInput() {
    char temp;
    std::cout << "Enter input: \n" << endl;
    cin >> temp;
    return temp;
}
std::string getStringInput() {
    std::string temp;
    std::cout << "Enter input: \n" << endl;
    getline(cin, temp);
    cin.ignore(21);
    return temp;
}
char t1;
std::string t2;
std::string t3;
string d1;
string d2;
string d3;
string d4;



void runMenu() {
    switch(SM_State) {
        case Main_Menu:
            MainMenu(); 
            t1 = getInput();
            if(t1 == '0') {
                std::cout << "Enter name of database you want to find: \n";
                getline(cin >> ws, t2);
                Sys->readDB(t2);
                SM_State = Main_Menu;
            }
            else if(t1 == '1') {
                //display databases and select which DB
                std::cout << *Sys;
                std::cout << "Please select Database: \n";
                getline(cin >> ws, curDB);
                tempDB = &Sys->returnDatabase(curDB); //point to the database you want
                SM_State = Database_Menu;  //goto the database menu
            }
            else if(t1 == '2') {
                // Add database
                std::cout << "Enter new database name\n";
                getline(cin >> ws, t2);
                Sys->addDB(t2);
                std::cout << "Success! Added new database: " << t2 << "\n";
                SM_State = Main_Menu; //return to main menu
                
            }
            /* Refactoring, not required for now
            else if(t1 == '3') {
                cout << "Enter the database you want to delete:" << endl;
                getline(cin >> ws, d1);
                Sys->deleteDB(d1);
                SM_State = Main_Menu; //return to main menu
            }
            */
           /*
            else if(t1 == '4') {
                std::string newName;
                std::cout << "Enter name of database you wish to change: \n";
                getline(cin >> ws, t2);
                tempDB = &Sys->returnDatabase(t2);
                std::cout << "Enter new database name: \n";
                getline(cin >> ws, newName);
                tempDB->updateData(t2, newName);
                
                //rename file on computer, idk why it wont work in class function
                std::string oldDir = t2 + "/";
                std::string newDir = newName + "/";
                std::rename(oldDir.c_str(), newDir.c_str());

                SM_State = Main_Menu; //return to main menu
            }
            */
            else if(t1 == '3') {
                std::string key;
                std::string query;
                std::cout << "Enter path query:" << std::endl;
                std::getline(cin >> ws, query);
                std::cout << "What key would you like to find: " << std::endl;
                std::getline(cin >> ws, key);
                print_query(query, key);
                SM_State = Main_Menu;
            }
            else if(t1 == '4') {
                //threading calling queries here:
                std::cout << "Starting Multi-threaded queries: \n"; //  << std::endl;
                multipleQuery();
                std::cout << "Finished Multi-threaded queries: \n" << std::endl;
                
                std::cout << "Started Linear (non-threaded) queries:\n"; //<< std::endl;
                linearQuery();
                std::cout << "Finished Linear  queries:\n" << std::endl;
                
            }
            else if(t1 == '5'){
               flag = 0; //quit
            }
            break;
        case Database_Menu:
            std::cout << "\nDATABASE__" << tempDB->getDBName() << "__MENU\n";
            DatabaseMenu();
            t1 = getInput();
            if(t1 == '0') {
                std::cout << "Select and search if collection exists: \n";
                getline(cin >> ws, t2);
                tempDB->readCollection(t2);
                SM_State = Database_Menu;
            }
            else if(t1 == '1') {
                std::cout << *tempDB;
                std::cout << "Select current Collection" << endl;
                getline(cin >> ws, curCol);
                tempCol = &tempDB->returnCol(curCol); //set current collection
                SM_State = Col_Menu; //go to collection menu
            }
            else if(t1 == '2') {
                
                std::cout << "Enter name of new collection\n";
                getline(cin >> ws, t2);
                tempDB->addCollection(t2, *tempDB);
                std::cout << "Successfully added" << t2 << " to database " << tempDB->getDBName() << "\n";
                SM_State = Database_Menu; //return to db menu
            }
            /* Refactoring for later
             else if(t1 == '3') {
                cout << "Enter the collection you want to delete: " << endl;
                getline(cin>>ws, d2);
                tempDB->deleteCollection(d2);
                SM_State = Database_Menu; //return to db menu
            }
            else if(t1 == '4') {
                std::cout << "Enter collection name you wish to update: \n";
                getline(cin >> ws, t2);
                tempCol = &tempDB->returnCol(t2);
                std::cout << "Enter new collection name: \n";
                getline(cin >> ws, t2);
                tempCol->setColName(t2);
                SM_State = Database_Menu; //return to db menu
            }
            */
            else if(t1 == '3'){
                SM_State = Main_Menu; //go back to Main Menu
            }
            break;
        case Col_Menu:
            std::cout << "COLLECTION__" << tempCol->getName() << "__MENU\n";

            CollectionMenu();
            t1 = getInput();
            if(t1 == '0') {
                std::cout << "Select and search for document: \n";
                getline(cin >> ws, t2);
                tempCol->readDoc(t2);
                SM_State = Col_Menu;
            }
            else if(t1 == '1') {
                
                std::cout << *tempCol;
                std::cout << "Please select your document\n";
                getline(cin >> ws, curDoc);
                tempDoc = &tempCol->returnDoc(curDoc);
                SM_State = Doc_Menu;
            }
            else if(t1 == '2') {
                std::cout << "Enter name of new document\n";
                getline(cin >> ws, t2);
                tempCol->addDocument(t2, *tempCol);
                std::cout << "Successfully added " << t2 << " to collection " << tempCol->getName() << "\n";
                SM_State = Col_Menu; //return to col menu
            }
            /* Refactoring for later
             else if(t1 == '3') {
                cout << "Enter the document you want to delete:" << endl;
                getline(cin>>ws, d3);
                tempCol->deleteDocument(d3);
                SM_State = Col_Menu; //return to col menu
            }
            else if(t1 == '4') {
                std::cout << "Which document would you like to rename: \n";
                getline(cin >> ws, t2);
                tempDoc = &tempCol->returnDoc(t2);
                std::cout << "Name of new document: \n";
                getline(cin >> ws, t3);
                tempDoc->rename(tempDoc->getFileName(),t3);
                tempDoc->setFileName(t3);
                tempCol->updateDoc(t2, t3);
                SM_State = Col_Menu; //return to col menu
            }
            */
            else if(t1 == '3'){
                SM_State = Main_Menu; //go back
            }
            
            break;
        case Doc_Menu:
            std::cout << "\nDOCUMENT__ " << tempDoc->getFileName() << " __MENU\n";
            DocumentMenu();
            t1 = getInput();
            if(t1 == '1') {
               std::cout << "Select and search if Key Exists in document: \n";
               getline(cin >> ws, t2);
               tempDoc->print_KV(t2);
               SM_State = Doc_Menu; 
            }
            else if(t1 == '2') {
                std::cout << "Enter new key: \n";
                std::string K;
                getline(cin >> ws, K);
                std::cout << "Enter new value for such key:\n";
                std::string V;
                getline(cin >> ws, V);
                tempDoc->addKV(K, V);
                std::cout << "Successfully added new key-value pair\n";
                SM_State = Doc_Menu; //return to doc menu
            }
             else if(t1 == '3') {
                cout << "Enter the key you want to delete: " << endl;
                getline(cin>>ws, d4);
                tempDoc->deleteKV(d4);
                SM_State = Doc_Menu; //return to doc menu
            }
            else if(t1 == '4') {
                std::cout << "Enter key you wish to change\n";
                std::string k1;
                getline(cin >> ws, k1);
                std::cout << "Enter new value for such key:\n";
                std::string v1;
                getline(cin >> ws, v1);
                tempDoc->updateKV(k1, v1);
                std::cout << "Successfully updated K_V Pair\n";
                SM_State = Doc_Menu; //return to doc menu
            }
            else if(t1 == '5'){
                SM_State = Main_Menu; 
            }
            else if(t1 == 'q') {
                flag = 0;
            }
            //flag = 0;
            break;
        default:
           flag = 0;
    }
}


int main() {
    load();
    
   while(flag) {
        runMenu(); 
    }
    
    
}