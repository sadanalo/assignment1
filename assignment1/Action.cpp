

#include "Action.h"
#include "Table.h"

BaseAction::BaseAction() {}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status = COMPLETED;
    errorMsg = "";
}

void BaseAction::error(std::string errorMsg)  {
    status = ERROR;
    this->errorMsg = errorMsg;
}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

std::string OpenTable::toString() const {
    std::string ans;
    for (int i = 0; i < customers.size(); ++i) {
        ans = ans + customers[i]->toString();
    }
    return ans;
}


void OpenTable::act(Restaurant &restaurant) {
    if (restaurant.getTable(tableId) == nullptr || restaurant.getTable(tableid).isOpen == false)
        error("table doesnt exixst or is already open");
    restaurant.getTable(tableid).openTable;
    for (int i = 0; i < customers.size(); ++i) {
        restaurant.getTable(tableid).addCustomer(customers[i]);
    }
}


OpenTable::OpenTable(int id, std::vector<Customer *> &customersList) : tableId(id), customers(customersList) {}


Order::Order(int id) : tableId(id) {}

void Order::act(Restaurant &restaurant) {
    std::string ppl_orders;
    std::vector<OrderPair> orders = restaurant.getTable(tableid).getOrders();
    std::vector<Customer> customers = restaurant.getTable(tableid).getCustomers();
    for (int i = 0; i < orders.size(); ++i) {
        ppl_orders += customers[i].getName() + "ordered" + orders[i].second.getName() + "/n";
        customers[i].order(restaurant.getMenu());
    }
    std::cout << ppl_orders << std:: endl ;
    complete();
}

std::string Order::toString() const {
    if (getStatus() == COMPLETED)
        return "lalala action open";
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId) : srcTable(src), dstTable(dst), id(customerId) {}

void MoveCustomer::act(Restaurant &restaurant) {

    //origin table exists and open
    if( restaurant.getTable(srcTable) == nullptr || restaurant.getTable(srcTable).isOpen == false){
        error("Cannot move customer");
        return;
    }
    //destination table exists and open
    if( restaurant.getTable(dstTable) == nullptr || restaurant.getTable(dstTable).isOpen == false){
        error("Cannot move customer");
        return;
    }
    //destination table not full
    if (restaurant.getTable(dstTable).getCustomers.size() + 1 == restaurant.getTable(dstTable).getCapacity) {
        error("Cannot move customer");
        return;
    }
    //the customer is in the origin table
    bool isInOrigin = false;
    for (int j = 0; j < restaurant.getTable(srcTable).getCustomers.size(); ++j) {
        if (restaurant.getTable(srcTable).getCustomers[i] == id)
            isInOrigin = true;
    }
    if(isInOrigin == false){
        error("Cannot move customer");
        return;
    }

    // the customer is not already in the destination table
    for (int i = 0; i < restaurant.getTable(dstTable).getCustomers.size(); i++) {
        if(restaurant.getTable(dstTable).getCustomers[i] == id)
            error("Cannot move customer");
        return;
    }

    restaurant.getTable(dstTable).addCustomer(id);

    //add dishes to dst
    for (int i = 0; i < restaurant.getTable(dstTable).getOrders().size; ++i) {
        if (restaurant.getTable(dstTable).getOrders()[i].first == id) // = customer id
            restaurant.getTable(dstTable).getOrders().push_back(id, restaurant.getTable(dst).getOrders()[i].second)
    }
    //remove dishes from src
    for (int i = 0; i < restaurant.getTable(srcTable).getOrders().size; ++i) {
        if (restaurant.getTable(srcTable).getOrders()[i].first == id) // = customer id
            while(restaurant.getTable(srcTable).getOrders()[i].first == id){
                restaurant.getTable(srcTable).getOrders().erase(id, restaurant.getTable(dst).getOrders()[i])
                i++;
            }
    }

    restaurant.getTable(srcTable).removeCustomer(id);
    //if src empty close src
    if (restaurant.getTable(srcTable).getCustomers.size() == 0)
        restaurant.getTable(srcTable).closeTable;
    complete();
}

std::string MoveCustomer::toString() const {
    if(getStatus() != COMPLETED)
        std:: cout << getErrorMsg() << std:: endl;
    std:: cout << "customer is moved" << std:: endl;
    return "customer is moved";
}

Close::Close(int id) :tableId(id) {}

void Close::act(Restaurant &restaurant) {
    if( restaurant.getTable(tableId) == nullptr || restaurant.getTable(tableId).isOpen == false)
        error("table does not exist or is not open");
    restaurant.getTable(tableId).closeTable();
}

std::string Close::toString() const {
    if(getStatus() != COMPLETED)
        return getErrorMsg();
    return "table" + std:: to_string(tableId) + " is closed";
}

CloseAll::CloseAll() :bill("") {}

void CloseAll::act(Restaurant &restaurant) {
    //print bill, then close each table
    for (int i = 0; i < restaurant.getNumOfTables(); ++i) {
        bill += "Table" + std::to_string(restaurant.getTable(i)) + "was closed. BILL" + restaurant.getTable(i).getBill + "NIS";
        restaurant.getTable(i).closeTable();
    }
    //todo exit the restaurant - closeAll should exit the "scanner" initilized in restaurant.start()?
}

std::string CloseAll::toString() const {
    return bill;
}

PrintMenu::PrintMenu() :toPrint("") {}

void PrintMenu::act(Restaurant &restaurant) {
    for (int i = 0; i < restaurant.getMenu().size(); ++i) {
        toPrint += restaurant.getMenu()[i].getName() + " ";
        toPrint += restaurant.getMenu()[i].getType() + " ";
        toPrint += restaurant.getMenu()[i].getPrice() + "/n";
    }
    std::cout << toPrint << std::endl;
}

std::string PrintMenu::toString() const {
    return toPrint;
}

PrintTableStatus::PrintTableStatus(int id) : tableId(id) {}

void PrintTableStatus::act(Restaurant &restaurant) {
    if(restaurant.getTable(tableId).getStatus() == false) {
        std::cout << "table " + std::to_string(tableId) + " is closed" << std::endl;
    }


    s = "Table status: open/n";
    s += "Customers:\n";
    for (int i = 0; i < restaurant.getTable(tableId).getCustomers().size(); ++i) {
        s += std::to_string(i) + " " + restaurant.getTable(tableId).getCustomers[i].getName() + "/n";
    }
    s.append("Orders\n");
    for (int j = 0; j < restaurant.getTable(tableId).getOrders().size(); ++j) {
        s += restaurant.getTable(tableId).getOrders[i].second.getName() + " " + "NIS" + " " + std::to_string(restaurant.getTable(tableId).getOrders[i].first);
    }
    s.append("Current bill: " );
    s.append(std::to_string(restaurant.getTable(tableId).getBill()));
    s.append("NIS");
    complete();

}

std::string PrintTableStatus::toString() const {
    return getErrorMsg();
}

PrintActionsLog::PrintActionsLog() {}

void PrintActionsLog::act(Restaurant &restaurant) {
    restaurant.getActionsLog(); //?
}

std::string PrintActionsLog::toString() const {
    std::string s;

}

BackupRestaurant::BackupRestaurant() {

}

void BackupRestaurant::act(Restaurant &restaurant) {

}

std::string BackupRestaurant::toString() const {
    return std::__cxx11::string();
}

RestoreResturant::RestoreResturant() {

}

void RestoreResturant::act(Restaurant &restaurant) {

}

std::string RestoreResturant::toString() const {
    return std::__cxx11::string();
}
