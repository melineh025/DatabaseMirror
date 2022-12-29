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
#include <pthread.h>
#include <cstdio>
using namespace rapidjson;
using namespace std;



///
void print_q(std::string f, std::string key)
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


#include <string>
#include <thread>
std::vector<std::string> queries;
int current_thread = 0;
int queNum = 0; //number of queries
std::string KEY_NAME;


void* query_array(void* arg)
{
  const auto processor_count = std::thread::hardware_concurrency(); //get number of cpu cores
  int num = current_thread++;
  for (int i = num * (queNum / processor_count); i < ((num + 1) * (queNum  / processor_count)); i++) {
        print_q(queries[i], KEY_NAME);
    }
}

void linearQuery() {
   std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

   for(int i = 0; i < queNum; i++) {
        print_q(queries[i], KEY_NAME);
        std::cout << std::endl;
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Linear Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Linear Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    //double time = double(end - start);
    //std::cout << "Linear search time: " << time << std::endl;

}
void multipleQuery() {
    std::string k;
    std::string value;
    const auto processor_count = std::thread::hardware_concurrency(); //get number of cpu cores
    std::cout << processor_count << std::endl;

    std::cout << "How many queries would you like to perform?\n";
    getline(cin >> ws, k);
    queNum = stoi(k);

    std::cout << "Enter key to query: \n" << endl;
    getline(cin >> ws, KEY_NAME);

    std::string path;
    for(int i = 0; i < queNum ; i++ ) {
        std::cout << "Enter query path: " << endl;
        getline(cin >> ws, path);
        queries.push_back(path);
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();


    //create number of thread = cpu cores
    pthread_t threads[processor_count];


    for (int i = 0; i < processor_count; i++){
        pthread_create(&threads[i], NULL, query_array, (void*)NULL);
               // std::cout << "working" << std::endl;

    }
    for (int i = 0; i <  processor_count; i++) {
        pthread_join(threads[i], NULL);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "\nMulti-Thread Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Multi-Thread Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

}

