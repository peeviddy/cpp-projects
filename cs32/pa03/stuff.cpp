// stuff.cpp
// CS 32: PA 03
// Patrick Vidican
// 5/30/16

#include "stuff.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

//Constructors
Stuff::Stuff(string name, double height)
: name(name), height(height) {}

Rectangular::Rectangular(string name, double height, double width, double depth)
: Stuff(name, height), width(width), depth(depth) {}

Cylindrical::Cylindrical(string name, double height, double diameter)
: Stuff(name, height), diameter(diameter) {}

    
ostream& operator << (ostream &out, const Stuff &s){
    out << s.toString();
    return out;
}

double Stuff::volume() const{
    return height;
}

string Stuff::toString() const{
    ostringstream oss;
    oss << name << ":" << "height=" << height;
    return oss.str();
}
    
double Rectangular::volume() const{
    return height*width*depth;
}

string Rectangular::toString() const{
    ostringstream oss;
    oss << Stuff::toString();
    oss << ",width=" << width << ",depth=" << depth;
    return oss.str();
}
    
double Cylindrical::volume() const{
    return M_PI*height*((diameter/2)*(diameter/2));
}

string Cylindrical::toString() const{
    ostringstream oss;
    oss << Stuff::toString();
    oss << ",diameter=" << diameter;
    return oss.str();
}