#include "../Headers/Doc.h"
#include "../Headers/System.h" 

#include "../rapidjson/include/rapidjson/document.h"
#include "../rapidjson/include/rapidjson/writer.h"
#include "../rapidjson/include/rapidjson/stringbuffer.h"
#include "../rapidjson/include/rapidjson/prettywriter.h" // for stringify JSON
#include "../rapidjson/include/rapidjson/filewritestream.h"
#include "../rapidjson/include/rapidjson/pointer.h"
#include <iostream>
#include <sys/io.h>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <algorithm>

#include <cstdio>
using namespace rapidjson;
using namespace std;

Doc::Doc() {
    
}
std::string Doc::givecol() {
    return colP;
}
std::string Doc::giveparent() {
    return dbP;
}
void Doc::setcol(std::string s) {
    colP = s;
}
void Doc::setparent(std::string s) {

    dbP = s;
}
void Doc::print_KV(std::string key)
{
    std::string f =  giveparent() + "/" + givecol() + "/" + getFileName();
    
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

void Doc::addKV(std::string key, std::string value)
{
    // assigns value to the passed-through key in the .JSON
    // document
    //open and parse .json file db1/col1/s.json
    std::string f =  giveparent() + "/" + givecol() + "/" + getFileName();
    std::ifstream jsonFile(f);

    std::stringstream file_contents;
    file_contents <<  jsonFile.rdbuf();
    rapidjson::Document myDoc;
    myDoc.Parse(file_contents.str().c_str());


    
    rapidjson::Document::AllocatorType& allocator = myDoc.GetAllocator();
    Value s;
    s.SetString(StringRef(key.c_str()));
    Value k;
    k.SetString(StringRef(value.c_str()));
    myDoc.AddMember(s,k, allocator);
    
   
  
    FILE* fp = fopen(f.c_str(), "w");  
        char writeBuffer[65536];
        rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
        Writer<FileWriteStream> writer(os);
        myDoc.Accept(writer);
        fclose(fp);

}

void Doc::updateKV(std::string key, std::string newVal) {
    //find the key that match and update their value
    std::string f =  giveparent() + "/" + givecol() + "/" + getFileName();

    Update(f, key, newVal);

}

void Doc::deleteKV(string key)
{
    std::string f =  giveparent() + "/" + givecol() + "/" + getFileName();
    std::ifstream jsonFile(f);
    std::stringstream file_contents;
    file_contents <<  jsonFile.rdbuf();
    rapidjson::Document myDoc;
    myDoc.Parse(file_contents.str().c_str());

    Value s;
    s.SetString(StringRef(key.c_str()));
    int a = 0;
    while(myDoc.HasMember(s)){
        myDoc.RemoveMember(s);
        a ++;
    }
    if(!a){
        cout << "Cannot find the key." << endl;
    }
    else{
        cout << "Successfully delete key-value." << endl;
    }

    

    FILE* fp = fopen(f.c_str(), "w"); 
        char writeBuffer[65536];
        rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
        Writer<FileWriteStream> writer(os);
        myDoc.Accept(writer);
        fclose(fp);

}
/*
void Doc::print_KV(string key)
{
    std::ifstream jsonFile(fileName);
    std::stringstream file_contents;
    file_contents <<  jsonFile.rdbuf();
    rapidjson::Document myDoc;
    myDoc.Parse(file_contents.str().c_str());

    Value s;
    s.SetString(StringRef(key.c_str()));
    int b = 0;
    if(myDoc.HasMember(s)){
        cout << myDoc[s].GetString() << endl;
        b ++;
    }
    if(!b){
        cout << "Cannot find the key." << endl;
    }
    else{
        cout << "Successfully print key-value." << endl;
    }
    


    FILE* fp = fopen(fileName.c_str(), "w"); 
        char writeBuffer[65536];
        rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
        Writer<FileWriteStream> writer(os);
        myDoc.Accept(writer);
        fclose(fp);
}
*/
 std::string Doc::getFileName() {return fileName;}
 void Doc::setFileName(std::string name) { 
    fileName = name;	
    
}
void Doc::rename(std::string old, std::string newName) {

    if (std::rename(old.c_str(), newName.c_str()) != 0)
		cout << "Error renaming file\n";
	else
		cout << "File renamed successfully";

}

//filecontents, string key
bool KeyCheck(string fileName, string key1)
{
	//Opening the JSON dataset and reading it's contents intro a string
	//Tokenizing into a string to convert into DOM
    //PandaExpress/db1/col1/a.json
    std::string s;

	std::ifstream jsonFile(fileName);
	std::stringstream file_contents;
	file_contents << jsonFile.rdbuf();

	//Create a document(DOM) and store it
	rapidjson::Document myDoc;
	myDoc.Parse(file_contents.str().c_str());

	//Taking the contents of the file as a string variable "str3".
	//The return value of the find function can be compared with "string::npos" (constant - 1)
	std::string str4{ file_contents.str().c_str() };
	int doc_read3;
	if ((doc_read3 = str4.find(key1)) != string::npos) {
		return true;
	}
	else
	{
		return false;
	}
}


void getFiles1(string path, vector<string>& filenames)
{
    DIR *pDir;
    struct dirent ptr;
    if(!(pDir = opendir(path.c_str()))){
        cout<<"Folder doesn't Exist!"<<endl;
        return;
    }
    ptr = *readdir(pDir);

    while(&ptr != 0) {
        if (strcmp((ptr.d_name), ".") != 0 && strcmp(ptr.d_name, "..") != 0){
            filenames.push_back(path + "/" + ptr.d_name);
        }
    }
    closedir(pDir);
}


//filePath: "...../db1/col1"
void findpath(std::string filePath, std::string key3)
{

	vector<string> files;

	//Get all files under this path
	getFiles1(filePath, files);

	char str[30];
	int size = files.size();
	int nullSize = 0;
	

	std::string key0{ key3 };
	key3.append("\":");
	
	std::string key4 = "\"";
	key4.append(key3);

    // files[0] = {"name":"China","age":1,"province":[{"name":"Heilongjiang","cities":["Harbin","Daqing"]},{"name":"Guangdong","cities":["Guangzhou","Shenzhen"]}],"location":["up","down","right","left"],"fullname":{"InEnglish":"People's Republic of China"}}



	//std::cout << "The collection has " << endl;
	vector<string> fileshavekey;
	vector<string> fileshavekey_path;
	for (int i = 0; i < size; i++)
	{

		if (KeyCheck(files[i], key4)) {

			fileshavekey.push_back(files[i]);
			std::cout << "The collection has " << files[i].c_str() << " that contains that key." << endl;
		}
		
	}
	if (fileshavekey.size() == 0)
	{
		std::cout << "The database has no such file." << endl;
	}
	else {
		for (int i = 0; i < fileshavekey.size(); i++) {
			string::size_type iPos = (fileshavekey[i].find_last_of('\\') + 1) == 0 ? fileshavekey[i].find_last_of('/') + 1 : fileshavekey[i].find_last_of('\\') + 1;
			string FilePath = fileshavekey[i].substr(0, iPos);//Find the path of files
			if (std::find(fileshavekey_path.begin(), fileshavekey_path.end(), FilePath) == fileshavekey_path.end()) {
				fileshavekey_path.push_back(FilePath);
				std::cout << "The collection " << FilePath.c_str() << fileshavekey[i].c_str() << " that contains that key." << endl;
			}
		}
	}
	
	//return 0;
}