#pragma once
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

class Product{
    private:
    int id;
    string name;
    float price;

    public:
    float getPrice();
    bool operator==(const Product& other) const {
        return this->id == other.id;
    }

    friend ostream& operator<<(ostream& os, const Product& p) {
        os << left << setw(10) << p.id 
           << "| " << setw(40) << p.name 
           << "| $" << fixed << setprecision(2) << p.price;
        return os; 
    }
};