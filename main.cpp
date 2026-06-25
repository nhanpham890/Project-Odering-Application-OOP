#include <iostream>
#include "store.h"

using namespace std;

void displayMenu(){
    cout<<"\n\n             WELCOME TO OUR E-COMMERCE STORE               \n";
    cout<<"  1. View all products\n";
    cout<<"  2. Select a product to buy\n";
    cout<<"  3. View your cart\n";
    cout<<"  4. Checkout or Print Receipt\n";
    cout<<"  5. Exit\n\n";
    cout<<"Please enter your choice (1-5): ";
}

int main(){
    Store myStore;
    myStore.loadProducts("productsList.txt");
    int choice;

    while(true){
        displayMenu();

        if(!(cin>>choice)){
            cout<<"\n[!] Invalid input! Please enter a number.\n";
            cin.clear();             
            cin.ignore(10000, '\n'); 
            continue;                
        }

        switch(choice){
            case 1:
                myStore.showProducts();
                break;
            case 2:
                myStore.selectProduct();
                break;
            case 3:
                myStore.viewCart();
                break;
            case 4:
                myStore.checkOut();
                break;
            case 5:
                cout<<"\nThank you for shopping with us! Goodbye!\n";
                return 0; 
            default:
                cout<<"\n[!] Invalid choice! Please select a number from 1 to 5.\n";
                break;
        }
    }
}