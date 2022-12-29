# PandaExpress - Document Store Senior Project
This CLI program allows users to perform processing on JSON documents.
Key Features Include:
1) Create Read Update Delete( CRUD) functions for .json files
2) Interactive Menu Command-line Interface
3) Path Querying and Filtering
4) Multi-threaded Queries
5) Database, Collection, and Document creation on system
6) File and Memory Persistence
## Requirements
To run this CLI program, you will need to have the following:
* C++ 11 or above
* Linux Operating System ( or linux terminal)
* [RapidJSON parser](https://github.com/Tencent/rapidjson)
* gcc version 8.4.0

## Installation
To run this program:
* Clone github repo and enter PandaExpress folder
* Open Linux terminal and type:
    g++ -pthread -o run newMain.cpp
* Run your executuable like: (This starts the program)
 ./run


## Tutorial
**System Menu**


After ./run you will see a menu like


0) Search if Database Exists
1) View and Select Database
2) Create New Database
3) Path Query and Filter
4) Multiple Path Query
5) Quit

**Note:** Start by pressing "2" then enter to create databases BEFORE searching

Selecting "1" make sure to type out the whole database name like "db1" then press enter

Selecting "2" adds a new directory inside PandaExpress to represent new database

Selecting "3" Asks user to input a path such as "db1/col1/doc1.json" to the json document and
            then a key. Outputs the key value pair. If object is nested, it will call again to ask for the nested key.
            
Selecting "4" Asks the user for multiple paths such as the previous selection and a key to
look for in such paths. It optimizes throughput by dividing up the vector of paths we want to 
query and assigning threads to part of the array based on the number of cpu cores.





**Database Menu**

0) Search if Collection Exists
1) View and Select Collection
2) Create New Collection
3) Quit to Main Menu

**Note:** Start by Creating a new collection BEFORE Searching

Selecting "1" lists the collections available and asks for input. Enter for example "col1"

Selecting "2" adds collection folder to the specific database 





**Collection Menu**

0) Search if Document Exists
1) View and Select Document
2) Create New Document (.json)
3) Quit to Main Menu

**Note:** Create a new document BEFORE searching 

Selecting "1" lists the documents and asks for input. Example: "doc1.json"

Selecting "2" creates .json file in specfied collection and db hierachy




**Document Menu**
1) Search K-V Pair
2) Insert New K-v Pair
3) Delete Entry
4) Update Existing K-V Pair
5) Exit to Main Menu

CRUD on document level:

Selecting "1" asks for a key, and displays the value if found in json file

Selecting "2" asks for a new key and a new value and appends to the json file

Selecting "3" asks for a key, then deletes the key value pair

Selecting "4" asks for a key, a new value, then updates the key-value pair if it exists


## Path Queries
This program allows for single and multiple path queries from the root menu.
Example i/o after selecting query:

    Enter Path Query:
        db1/col1/doc1.json
     What key would you like to find:
        ab
     "ab" : "ba"
## Multi-threading
When doing multiple-queries, we assign cpu cores to work on part of the vector of our path query
requests. For example we have an array of path query requests: ["db1/col1/doc1.json", ... , "db1/col1/doc10.json"]
Using the c++ pthread library, we split the cores to work on part of the array.


## Team Members
- Elbert Nguyen
- Melineh Mansour Cheharmohali
- Ligang Zou
- Xirong Xie

*Team PandaExpress 2022, University of California, Riverside.
 Made with :heart: in Riverside, CA.*
