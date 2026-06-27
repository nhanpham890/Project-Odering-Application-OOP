#include "store.h"

void Store::loadProducts(string filename){
    ifstream file(filename);
    if(!file){
        cout<<"can not open this file name:  "<<filename<<endl;
        return;
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
    if(!file){
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

string Store::checkPhone(){
    cout<<"Typing your phone number: ";
    string phoneCheck;
    cin>>phoneCheck;

    ifstream fileIn("order.txt");
    if(!fileIn){
        cout<<"Can not open order history!"<<endl;
        return "";
    }

    vector<string>notCancelOrders;
    vector<string>orderToCancel;

    string line;
    while(getline(fileIn, line)){
        if(line.empty()) continue;
        string phoneOrdered;

        size_t pos1 = line.find('|');
        phoneOrdered = line.substr(0,pos1);

        if(phoneCheck == phoneOrdered){
            fileIn.close();
            return phoneCheck;
        }
    }

    fileIn.close();
    cout<<"Can not find any oders with this phone number: "<<phoneCheck<<endl;
    return "";
}

void Store::cancelOrder( ){
    cout<<"CANCEL THE ORDER"<<endl;
    string phoneCheck = checkPhone();
    if(phoneCheck == ""){
        return;
    }

    ifstream fileIn("order.txt");
    if(!fileIn){
        cout<<"Can not open order history!"<<endl;
        return;
    }

    vector<string>notCancelOrders;
    vector<string>orderToCancel;
    string line;

    while(getline(fileIn, line)){
        if(line.empty()) continue;

        size_t pos1 = line.find('|');
        string phoneOrdered = line.substr(0,pos1);

        if(phoneCheck == phoneOrdered){
            orderToCancel.push_back(line);
        }else{
            notCancelOrders.push_back(line);
        }
    }
    fileIn.close();

    while (!orderToCancel.empty())
    {
        cout<<endl<<"Product that odered with: "<<phoneCheck<<endl;
        for(size_t i = 0; i < orderToCancel.size(); i++){
        size_t pos1 = orderToCancel[i].find('|');
        size_t pos2 = orderToCancel[i].find('|', pos1 + 1);
        string id = orderToCancel[i].substr(pos1 + 1, pos2 - pos1 - 1);
        int quantity = stoi(orderToCancel[i].substr(pos2 + 1));

        string producName = "unknow";
        for(size_t j = 0; j < productList.size(); j++){
            if(productList[j].getID() == id){
                producName = productList[j].getName();
                break;
            }
        }

        cout<<i + 1<<" | "<<producName<<" | "<<id<<" | "<<quantity<<endl;
        }
        
        string cancelID;
        cout<<"Typing the id of the product you want to cancel ('q' or 'Q' to quit): ";
        cin>>cancelID;

        if(cancelID == "q" or cancelID == "Q" ){
            break;
        }

        bool found = false;

        for(size_t i = 0; i < orderToCancel.size(); i++){
            size_t pos1 = orderToCancel[i].find('|');
            size_t pos2 = orderToCancel[i].find('|', pos1 + 1);
            string id = orderToCancel[i].substr(pos1 + 1, pos2 - pos1 - 1);
            int quantity = stoi(orderToCancel[i].substr(pos2 + 1));

            if(cancelID == id){
                found = true;
                char confirm;
                cout<<"Are you sure to cancel this product "<<id<<" (Y/N): ";
                cin>>confirm;

                if(confirm == 'y' or confirm == 'Y'){
                    vector<string> tempOrders;
                    for(size_t j = 0; j < orderToCancel.size(); j++){
                        if(i != j){
                            tempOrders.push_back(orderToCancel[j]);
                        }
                    }

                    orderToCancel = tempOrders;
                    cout<<"- product ID: "<<cancelID<<" successfully cancel\n";
                    break;
                }else{
                    cout<<"Action absorted";
                }
                break;
            }  
        }

        if(!found){
            cout<<"Can not find this product ID: "<<cancelID<<endl;
            cout<<"Try again"<<endl;
            }
    }
    ofstream fileOut("order.txt");
    for(size_t i = 0; i < notCancelOrders.size(); i++){
        fileOut<<notCancelOrders[i]<<endl;
    }
    for(size_t i = 0; i < orderToCancel.size(); i++){
        fileOut<<orderToCancel[i]<<endl;
    }
    fileOut.close();
    cout<<"Order history updated successfully";
}