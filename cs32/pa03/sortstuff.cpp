// sortstuff.cpp
// cmc, 5/14/2016

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "stuff.h"
using namespace std;

int main(int argc, char *argv[]) {
    // declare utility functions
    vector<Stuff *> readItems(ifstream &);
    void sort(vector<Stuff *> &);
    void printItems(vector<Stuff *> &, string);

    // open data file, or quit if problem
    ifstream input;
    if (argc > 1) {
        input.open(argv[1]);
        if (input.fail()) {
            cerr << "failed opening " << argv[1] << endl;
            return 1;
        }
    }
    else {
        cout << "usage: " << argv[0] << " filename\n";
        return 2;
    }

    // read items into a vector and close file
    vector<Stuff *> items;
    items = readItems(input);
    input.close();

    // sort items and show results
    sort(items);
    printItems(items, string("Items (sorted by volume):"));
}

// utility reads Stuff items into vector until end of input
vector<Stuff *> readItems(ifstream &input) {
    vector<Stuff *> items;
    string line, name, shape;
    double h, w, d;
        
    while (!input.eof()) {
        input >> name >> shape;
        if (input.eof()) break;
        switch (shape[0]) {
            case 'R':
                input >> h >> w >> d;
                items.push_back(new Rectangular(name, h, w, d));
                break;
            case 'C':
                input >> h >> d;
                items.push_back(new Cylindrical(name, h, d));
        }
    }

    return items;
}

// simple selection sort - sorts from greatest to least volume
void sort(vector<Stuff *> &items) {
    int n = items.size();
    for (int i=0; i<n; i++)
        for (int j=0; j<i; j++)
            if (items[j]->volume() < items[i]->volume()) {
                Stuff *temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
}

// utility prints table of volumes and item descriptions with title
void printItems(vector<Stuff *> &items, string title) {
    cout << endl << title << endl;
    cout << "    Volume\tDescription" << endl;
    cout << "    ------\t-----------" << endl;

    double v, h, totalVolume = 0, maxHeight = 0;
    cout.precision(1);
    for (size_t i=0; i < items.size(); i++) {
        Stuff &f = *items[i];
        v = f.volume();
        h = f.getHeight();
        cout << setw(10) << fixed << showpoint
             << v << '\t' << f << endl;
        totalVolume += v;
        if (h > maxHeight)
            maxHeight = h;
    }

    cout << "    ------" << endl
         << setw(10) << setprecision(1) << totalVolume
         << "\tTotal cubic feet" << endl;
    cout << "Maximum height is " << maxHeight << " feet." << endl;
}