#include "Vipcustomer.h"
#include "customer.h"
Vipcustomer::Vipcustomer()
{
	freeShipping= true;
	discountPercent= 0.20;
	minOrder= 10;
}
Vipcustomer::Vipcustomer(string name, string address, string phone) : Customer(name, address, phone) {
	freeShipping= true;
	discountPercent= 0.20;
	minOrder= 10;
}
bool Vipcustomer::getFreeShipping() const {
    return freeShipping;
}
double Vipcustomer::applyDiscount(double total) const {
        if (total >=minOrder) {
        	return total * (1- discountPercent);
        	
		}
		return total;
}
istream& operator>>(istream& in, Vipcustomer& v) {
	string name, address, phone; 
    cout << "Enter name: ";
    getline(in, name);
    cout << "Enter address: ";
    getline(in, address);
    cout << "Enter phone: ";
    getline(in, phone);
    v.setName(name);
    v.setAddress(address);
    v.setPhone(phone);
    return in;
}
