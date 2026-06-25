#pragma once;
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "product.h"
#include "cart.h"
#include "customer.h"
#include "order.h"

using namespace std;

class Store{
    private:
    vector<Product> productList;
    Cart cart;
    vector<Customer> customerList;

    public:
    void loadProducts(string filename);
    void saveCustomer();
    void saveOrder(string phone, const Cart& currentCart);
    void showProducts();
    void selectProduct();
    void viewCart();
    void checkOut();
};