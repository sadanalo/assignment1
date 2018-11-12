#include "Table.h"
#include <iostream>

Table::Table(int t_capacity) : capacity(t_capacity) {}

int Table::getCapacity() const {
    return capacity;
}

void Table::addCustomer(Customer *customer) {
    customersList.push_back(customer);
}

void Table::removeCustomer(int id) {
    for (int i = 0; i < customersList.size(); ++i) {
        if (customersList[i]->getId() == id) {
            customersList.erase(customersList.begin() + i);
            delete (customersList.at(i));           //need delete?
            return;
        }
    }
}
Customer *Table::getCustomer(int id) {
    for (int i = 0; i < customersList.size(); ++i) {
        if (customersList[i]->getId() == id)
            return customersList[i];
    }
    std::cout << "customer doesnt exist" << std::endl;
    return 0;
}

std::vector<Customer *> &Table::getCustomers() {
    return customersList;
}

std::vector<OrderPair> &Table::getOrders() {
    return orderList;
}

void Table::order(const std::vector<Dish> &menu) {
    for (int i = 0; i < customersList.size(); ++i) {
        std:: vector <int> orders = customersList[i]->order(menu);
        for (int j = 0; j < orders.size(); ++j) {
            OrderPair p = std::make_pair(customersList[i]->getId(),getDish(menu,orders[j]));
            orderList.push_back(p);
        }
    }

}

void Table::openTable() {
    open = true;
}

void Table::closeTable() {
    open = false;
}

int Table::getBill() {
    int bill = 0;
    for (int i = 0; i < orderList.size(); ++i) {
        bill = bill + orderList[i].second.getPrice();
    }
    return bill;
}

bool Table::isOpen() {
    return open;
}

Dish Table::getDish(const std::vector<Dish> &menu, int d_id) {
    for( auto dish : menu){
        if (dish.getId() == d_id)
            return dish;
    }
    std:: cout <<"the dish is not in the menu"<< std::endl;
}
