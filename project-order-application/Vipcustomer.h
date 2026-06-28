#pragma once
#include "customer.h"

class Vipcustomer : public Customer
{
	private:
		bool freeShipping;
		double discountPercent;
		double minOrder;
	public:
		Vipcustomer();
		Vipcustomer(string name, string address, string phone);
		bool getFreeShipping() const;
		double applyDiscount(double total) const;
        friend istream& operator>>(istream&, Vipcustomer&);
};
