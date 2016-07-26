// Patrick Vidican
// 4/24/16

#include <algorithm>
#include <vector>
#include "table.h"
using namespace std;

Table::Table( unsigned int max_entries ) { // an array of std::list to enable chaining woohoo
    numEntries = 0;
    CAPACITY = max_entries*2;
    datatable = new list<Entry> [ CAPACITY ];
}

Table::Table( unsigned int entries, std::istream &input ) {
    CAPACITY = entries*2;
    datatable = new list<Entry> [ CAPACITY ];
    Entry temp;
    for (int i = 0; i < entries; ++i){
        input >> temp;
        put( temp );
    }
}

// copy constructor
Table::Table( Table& t ){
    numEntries = t.numEntries;
    CAPACITY = t.CAPACITY;
    datatable = new list<Entry> [ CAPACITY ];
    for ( int i = 0; i < t.CAPACITY; ++i ){
        datatable[i] = t.datatable[i];
    }
}

// destructor
Table::~Table(){
    delete [] datatable; // this erases all the chained bits too
}

void Table::put(unsigned int key, std::string data){
    ++numEntries;
    unsigned int index = hash( key );
    Entry newentry( key, data );
    // if empty just stick it right there
    if ( datatable[ index ].empty() ){
        datatable[ index ].push_back( newentry );
    }
    else{ // check for a duplicate
        for (list<Entry>::iterator it = datatable[ index ].begin(), end = datatable[ index ].end(); it != end; ++it){ // check each element in spot j
            if ( it->get_key() == key ){ // if you find one erase it
                datatable[ index ].erase( it );
                break;
            }
        }
        datatable[ index ].push_back( newentry ); // either way you're adding it
    }
}

void Table::put(Entry e){
    ++numEntries;
    unsigned int index = hash( e.get_key() );
    // if empty just stick it right there
    if ( datatable[ index ].empty() ){
        datatable[ index ].push_back( e );
        numEntries++;
    }
    else{ // check for a duplicate
        for (list<Entry>::iterator it = datatable[ index ].begin(), end = datatable[ index ].end(); it != end; ++it){ // check each element in spot j
            if ( it->get_key() == e.get_key() ){ // if you find one erase it
                datatable[ index ].erase( it );
                break;
            }
        }
        datatable[ index ].push_back( e ); // either way you're adding it
    }
}

std::string Table::get(unsigned int key) const{
    unsigned int index = hash( key );
    if ( datatable[ index ].empty() ){
        return "";
    }
    else{ // check for a duplicate
        for (list<Entry>::iterator it = datatable[ index ].begin(), end = datatable[ index ].end(); it != end; ++it){ // check each element in spot j
            if ( it->get_key() == key ) return it->get_data();
        }
    }
}

bool Table::remove(unsigned int key){
    unsigned int index = hash( key );
    if ( datatable[ index ].empty() ){
        return false;
    }
    else{ // check for a duplicate
        for (list<Entry>::iterator it = datatable[ index ].begin(), end = datatable[ index ].end(); it != end; ++it){ // check each element in spot j
            if ( it->get_key() == key ){
                datatable[ index ].erase( it );
                --numEntries;
                return true;
            }
        }
        return false;
    }
}

std::ostream& operator<< (std::ostream &out, const Table &t){ // O(nlogn)
    std::vector<Entry> order;
    order.reserve( t.numEntries );
    for ( int i = 0; i < t.CAPACITY; ++i ){
        for ( Entry e: t.datatable[i] ){
            order.push_back( e );
        }
    }
    sort( order.begin(), order.end() );
    for ( Entry k: order ){
        out << k << endl;
    }
    return out;
}

// overloaded = operator
Table& Table::operator = ( const Table &t ){
    if ( this == &t ) return *this;
    if ( CAPACITY != t.CAPACITY ){
        delete [] datatable;
        datatable = new list<Entry> [ t.CAPACITY ];
    }
    for ( int i = 0; i < t.CAPACITY; ++i ){
        datatable[i] = t.datatable[i];
    }
    numEntries = t.numEntries;
    CAPACITY = t.CAPACITY;
    
    return *this;
}
