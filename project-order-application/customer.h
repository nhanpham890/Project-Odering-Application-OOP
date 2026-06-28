#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Customer {
protected :
    string name;
    string phone;
    string address;

public:
    Customer(string n = "", string p = "", string a = "") 
        : name(n), phone(p), address(a) {}

    string getName() const { return name; }
    void setName(string n) { name = n; }
    string getPhone() const { return phone; }
    void setPhone(string p) { phone = p; }
    string getAddress() const { return address; }
    void setAddress(string a) { address = a; }
    friend istream& operator>>(istream& is, Customer& c) {

    cout << "Nhap ten khach hang: "; 
    getline(is, c.name);

    cout << "Nhap so dien thoai: "; 
    getline(is, c.phone);   

    cout << "Nhap dia chi: "; 
    getline(is, c.address);

    return is;
}
    friend ostream& operator<<(ostream& os, const Customer& c) {
        os << "Ten: " << c.name <<endl<< "SDT: " << c.phone<<endl<< "Dia chi: " << c.address<<endl;
        return os;
    }
};

template <typename T>
void printCustomerList(const vector<T>& list) {
    cout << "\n--- DANH SACH KHACH HANG ---" << endl;
    for (size_t i = 0; i < list.size(); ++i) {
        cout << i + 1 << ". " << list[i] << endl;
    }
}
