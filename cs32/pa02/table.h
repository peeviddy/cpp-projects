// table.h

#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <iostream>
#include <list>
#include <cstdlib>
#include "entry.h"
using namespace std;

class Table {

public:
    Table( unsigned int max_entries = 100 );                     // constructor
	Table( unsigned int entries, std::istream &input);           // constructor
	
	Table( Table &t );											 // copy constructor
	~Table();													 // destructor

	void put(unsigned int key, std::string data);
	void put(Entry e);
	std::string get(unsigned int key) const;
	bool remove(unsigned int key);
	
	friend std::ostream& operator << (std::ostream &out, const Table &t);
	Table& operator = ( const Table &t );

private:
	unsigned int numEntries = 0;
	unsigned int CAPACITY;
	list<Entry> *datatable;
	unsigned int hash( unsigned int key ) const { return key%CAPACITY; };
};

#endif