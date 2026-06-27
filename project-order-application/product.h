#pragma once
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

class Product{
    private:
    string id;
    string name;
    double price;

    public:
    double getPrice() const { return price; }
    string getID() const { return id; }
    string getName() const { return name; }

    Product(string i, string n, double p) {
        id = i;
        name = n;
        price = p;
    }

    bool operator==(const Product& other) const {
        return this->id == other.id;
    }

    friend ostream& operator<<(ostream& os, const Product& p) {
        os << left << setw(10) << p.id 
           << "| " << setw(40) << p.name 
           << "| $" << fixed << setprecision(2)<<p.price<<endl;
        return os; 
    }
};