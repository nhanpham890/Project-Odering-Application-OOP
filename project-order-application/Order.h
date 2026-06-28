#pragma once
#include "Customer.h"
#include "Cart.h"
#include <ctime>
#include <fstream>
#include <string>
#include <iostream>
#include "Vipcustomer.h"
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
    Order(const Customer& ct, const Cart& c, double ship = 25000);
    ~Order() {};
    void Receipt() const;
    string getOrderDate()    const { return NgayThanhChuoi(orderDate); }
    string getDeliveryDate() const { return NgayThanhChuoi(NgayToi()); }
};



