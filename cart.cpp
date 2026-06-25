#include <cart.h>

void Cart::addProduct(Product selectedProduct){
    for(int i = 0; i < items.size(); i++){
        if(items[i].getProduct() == selectedProduct){
            items[i].increaseQuantity();
            cout<<"- Increasing Quantity of the product successfully!";
            return;
        }
    }
    CartItem newItem(selectedProduct, 1);
    items.push_back(newItem);
    cout<<"- Product added to cart!";
}

double Cart::calTotal() const{
    double total = 0;
    for (int i = 0; i < items.size(); i++){
        total += items[i].getCostTotal();
    }
    return total;
}

vector<CartItem> Cart::getItems() const{
    return items;
}

void Cart::displayCart(){
    if(items.empty()){
        cout << "\n================================================================================\n";
        cout << "                       Your Cart is empty!\n";
        cout << "================================================================================\n\n";
        return;
    }

    for(int i = 0; i < items.size(); i++){
        Product p = items[i].getProduct();
        cout << left << setw(5) << (i + 1);

        cout << p; 

        cout << right << setw(10) << items[i].getQuantity()
             << right << setw(14) << "$" << fixed << setprecision(2) << items[i].getCostTotal() << endl;
    }

    cout << "================================================================================\n";
    cout << right << setw(65) << "TONG CONG TAT CA: " 
         << right << setw(14) << "$" << fixed << setprecision(2) << calTotal() << endl;
    cout << "================================================================================\n\n";
}