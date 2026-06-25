#pragma once
#include "Customer.h"
#include "Cart.h"
#include <ctime>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

class Order {
private:
    Customer customer;
    Cart cart;
    Date orderDate;
    double shippingCost;

    bool Namnhuan(int year) const;
    int Dungngay(int month, int year) const;
    Date addDays(Date date, int days) const;
    Date NgayHientai() const;
    string layso0(int Num) const;
    string NgayThanhChuoi(Date date) const;
    Date NgayToi() const;

public:
    Order(Customer customer, Cart cart, double shippingCost = 25000);
    ~Order();
    void Receipt() const;
};



