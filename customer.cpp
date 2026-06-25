#include <iostream>
#include <vector> 
#include "customer.h"

using namespace std;
int main() {
    vector<Customer> list;
    int n;

    cout << "Nhap so luong khach hang: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        Customer temp;
        cout << "\nNhap thong tin khach hang thu " << i + 1 << ":" << endl;
        cin >> temp;
        list.push_back(temp);
    }

    printCustomerList(list);

    return 0;
}
