#include "store.h"

void Store::loadProducts(string filename){
    ifstream file(filename);
    if(!file){
        cout<<"can not open this file name:  "<<filename<<endl;
    }

    string line;
    while(getline(file, line)){
        string idStr, name, priceStr;

        size_t pos1 = line.find('|');
        idStr = line.substr(0,pos1);

        size_t pos2 = line.find('|', pos1 + 1);
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);

        priceStr = line.substr(pos2 + 1);
        double price = stod(priceStr);
        Product p(idStr, name, price);
        productList.push_back(p);
    }
    file.close();
}

void Store::saveCustomer(){
    ofstream file("customers.txt");
    if (!file) {
            cout << "Loi: Khong the tao file luu khach hang!\n";
            return;
        }

    for(size_t i = 0; i < customerList.size(); i++){
        file<<customerList[i].getName()<<"|"
            <<customerList[i].getAddress()<<"|"
            <<customerList[i].getPhone()<<endl;
    }

    file.close();

}

void Store::saveOrder(string phone, const Cart& currentCart){
    ofstream file("order.txt", ios::app);
    if (!file) {
            cout << "Error: can not create saving file!\n";
            return;
        }
    
    vector<CartItem> items = currentCart.getItems();
    for(size_t i = 0; i < items.size(); i++){
        Product p = items[i].getProduct();
        file<<phone<<'|'<<p.getID()<<'|'<<items[i].getQuantity()<<endl;
    }

    file.close();
}

void Store::showProducts(){
    cout<<"\n============================== Products List ==============================\n";
    for(size_t i = 0 ; i < productList.size(); i++){
        cout<<productList[i];
    }
}

void Store::selectProduct(){
    showProducts();
    int quantity;
    string id, strquantity;
    bool flag = false;

    while(!flag){
        cout<<"Typing the id of the product or 'Q' to quit: ";
        cin>>id;

        if(id == "Q" or id == "q"){ 
            cout<<"- Canceled product selection\n";
            return;
        }

        for(size_t i = 0; i < productList.size(); i++ ){
            if(productList[i].getID() == id){
                flag = true;
                
                while(true){
                    cout<<"Typing the quantity: ";
                    cin>>strquantity;
                    try{
                        quantity = stoi(strquantity);

                        if(quantity > 0 ){
                            break;
                        }else{
                            cout<<"Enter a number > 0\n";
                        }
                    }catch(...){
                        cout<<"Invalid format! Numbers only\n";
                    }
                }
                for(int j = 0; j < quantity; j++){
                    cart.addProduct(productList[i]);
                }
                break; 
            }
        } 

        if(!flag){
            cout<<"\nCan not find this id: "<<id<<endl;
        }
    } 
}

void Store::viewCart(){
    cart.displayCart();
}

void Store::checkOut(){
    if(cart.calTotal() == 0){
        cout<<"There is not any products in your cart, please select product for payment!";
        return;
    }
    
    Customer currentCust;
    cout<<"Customer Information Registration\n";
    cin>>currentCust;

    customerList.push_back(currentCust);
    saveCustomer();

    saveOrder(currentCust.getPhone(), cart);
    double shippingCost = 25000;
    Order finalOrder(currentCust, cart, shippingCost);
    finalOrder.Receipt();

    cart.cartClear();
    cout<<"- Successful! Your cart has been cleared\n";

}