#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "product.h"
using namespace std;

class CartItem{
    private:
    Product product;
    int quantity;

    public:
    CartItem(Product p, int q) : product(p), quantity(q) {}
    
    Product getProduct() const {
        return product;
    }

    int getQuantity() const{
        return quantity;
    }

    void increaseQuantity(int amount = 1){
        quantity += amount;
    }

    double getCostTotal() const{
        return product.getPrice() * quantity;
    }
};

class Cart{
    private:
    vector<CartItem> items;

    public:
    vector<CartItem> getItems() const;
    void addProduct(Product selectedProduct);
    double calTotal() const;
    void displayCart();
    void cartClear() { items.clear(); };
};