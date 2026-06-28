#include "Order.h"
#include <string>

bool Order::Namnhuan(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Order::Dungngay(int month, int year) const {
    int result;
    switch(month) {
        case 4: case 6: case 9: case 11:
            result = 30; break;
        case 2:
            result = Namnhuan(year) ? 29 : 28; break;
        default:
            result = 31; break;
    }
    return result;
}
Order::Order(const Customer& ct, const Cart& c, double ship) 
    : customer(ct), cart(c), shippingCost(ship) 
{
    cout << "Enter order date (dd mm yyyy): ";
    cin >> orderDate.day >> orderDate.month >> orderDate.year;
}

Date Order::addDays(Date date, int days) const {
    date.day += days;
    while (date.day > Dungngay(date.month, date.year)) {
        date.day   -= Dungngay(date.month, date.year);
        date.month++;
        if (date.month > 12) {
            date.month = 1;
            date.year++;
        }
    }
    return date;
}

Date Order::NgayHientai() const {
    Date date;
    time_t t = time(0);
    tm* now = localtime(&t);

    date.day = now->tm_mday;
    date.month = now->tm_mon + 1;    
    date.year = now->tm_year + 1900; 

    return date;
}

string Order::layso0(int Num) const {
    if (Num < 10)
    return "0" + to_string(Num);
    return to_string(Num);
}

string Order::NgayThanhChuoi(Date date) const {
    return layso0(date.day)      + "/" +
           layso0(date.month)    + "/" +
           to_string(date.year);
}

Date Order::NgayToi() const {
    return addDays(orderDate, 3);
}



void Order::Receipt() const {
    cout<<"\n==================== ORDER DETAILS ===================="<<endl;

    cout<<"Order Date: "<<NgayThanhChuoi(orderDate)<<endl;
    cout<<"Expected Delivery: "<< NgayThanhChuoi(NgayToi())<<endl;
    cout<<"-------------------------------------------------------"<<endl;
    
    cout<<"Customer Name: " << customer.getName()<<endl;
    cout<<"Phone Number: " << customer.getPhone()<<endl;
    cout<<"Delivery Address: " << customer.getAddress()<<endl;
    cout<<"-------------------------------------------------------"<<endl;

    cout<<"Items Ordered: "<<endl;
    vector<CartItem> items = cart.getItems();
    for(size_t i = 0; i < items.size(); i++){
        Product p = items[i].getProduct();
        double itemCostTotal = p.getPrice() * items[i].getQuantity();

        cout<<"- "<<p.getName()<<" (ID: "<<p.getID()<<")"<<endl;
        cout<<"Quantity: "<<items[i].getQuantity()<<" | Price: "<<p.getPrice()<<endl;
    }
    double totalAmount = cart.calTotal() + shippingCost;

    cout<<"Cart subtotal: "<<cart.calTotal()<<endl;
    cout<<"Shipping fee: "<<shippingCost<<endl;
    cout<<"- Total: "<<totalAmount<<endl;
}