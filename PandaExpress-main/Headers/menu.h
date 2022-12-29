#include <iostream>
void MainMenu() {
    std::cout << "\nPandaExpress Database System" << std::endl;
    std::cout << "\n\n";
    std::cout << "0) Search if Database Exists\n";
    std::cout << "1) View and Select Databases \n";
    std::cout << "2) Create New Database\n";
    std::cout << "3) Path Query and Filter\n";
    std::cout << "4) Multiple Path Query\n";
    std::cout << "5) Quit";
    std::cout << "===============================\n";
}


void DatabaseMenu() {
    std::cout << "\n\n";
    std::cout << "0) Search if Collection Exists\n";
    std::cout << "1) View and Select Collections\n";
    std::cout << "2) Create New Collection\n";
    std::cout << "3) Quit to Main Menu\n";
    std::cout << "===============================\n";
    
}

void CollectionMenu() {
    std::cout << "\n\n";
    std::cout << "0) Search if Document Exists\n";
    std::cout << "1) View and Select Document\n";
    std::cout << "2) Create New Document (.json) \n";
    std::cout << "3) Quit to Main Menu\n";
    std::cout << "===============================\n";
}


void DocumentMenu () {
    std::cout << "\n";
    std::cout << "1) Search K-V  Pair\n";
    std::cout << "2) Insert New K-V Pair\n";
    std::cout << "3) Delete Entry\n";
    std::cout << "4) Update Existing K-V Pair\n";
    std::cout << "5) Exit to Main Menu";
    std::cout << "===============================\n";

}
