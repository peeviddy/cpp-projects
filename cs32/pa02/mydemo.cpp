// mydemo.cpp - demonstration program for Table
// patrick's demo program

#include <iostream>
#include <fstream>
#include "table.h"
using namespace std;

unsigned int user_get(Table &t);
unsigned int user_remove(Table &t);

int main() {
    
    cout << "\nDemonstrate larger table\n";
    ifstream input;
    input.open("fips.txt");
    if (!input.good()) {
        cout << "No fips.txt in current directory. Quitting\n";
        return 1;
    }
    
    Table *fipstable;
    fipstable = new Table(3142, input);
    
    cout << *fipstable << endl;
    
    return 0;
}

unsigned int user_get(Table &t) {
    unsigned int key;
    cout << "Enter key to get:\n";
    cin >> key;
    if (key != 0) {
        unsigned int start = Entry::access_count();
        cout << "data at key " << key << ": " << t.get(key) << endl;
        cout << "(accesses: " <<
            Entry::access_count() - start << ")\n";
    }
    return key;
}

unsigned int user_remove(Table &t) {
    unsigned int key;
    cout << "Enter key to remove:\n";
    cin >> key;
    if (key != 0) {
        unsigned int start = Entry::access_count();
        if (t.remove(key))
            cout << "removed key: " << key << endl;
        else
            cout << "did not find key: " << key << endl;
        cout << "(accesses: "
            << Entry::access_count() - start << ")\n";
    }
    return key;
}