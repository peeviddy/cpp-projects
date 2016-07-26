// stuff.h
// CS 32: PA 03
// Patrick Vidican
// 5/30/16

#ifndef STUFF_H
#define STUFF_H

#include <string>
#include <iosfwd>
#include <cmath>
using namespace std;

class Stuff {
public:
    Stuff(string name = "", double height = 0);
    string getName() const { return name; }
    double getHeight() const { return height; }
    virtual double volume() const;
    virtual string toString() const;
    friend std::ostream& operator << (std::ostream &out, const Stuff &s);
    
protected:
    double height;
    string name;
};

class Rectangular : public Stuff {
public:
    Rectangular(string name = "", double height = 0, double width = 0, double depth = 0);
    virtual double volume() const;
    virtual string toString() const;
    
protected:
    double width;
    double depth;
};

class Cylindrical : public Stuff {
public:
    Cylindrical(string name = "", double height = 0, double diameter = 0);
    virtual double volume() const;
    virtual string toString() const;
    
protected:
    double diameter;
};

#endif
