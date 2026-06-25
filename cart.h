#pragma once
#include <iostream>
#include <vector>
#include "product.h"
using namespace std;

class CartItem{
    private:
    Product product;
    int quantity;

    public:
    CartItem(Product p, int q){
        p = product;
        q = quantity;
    }
    
    Product getProduct(){
        return product;
    }

    int getQuantity(){
        return quantity;
    }

    void increaseQuantity(int amount = 1){
        quantity = amount + 1;
    }

    float getCostTotal(){
        return product.getPrice() * quantity;
    }
};

class Cart{
    private:
    vector<CartItem> items;

    public:
    void addProduct(Product selectedProduct);
    float calTotal();
    void displayCart();
};