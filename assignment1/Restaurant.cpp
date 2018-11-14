
#include "Restaurant.h"

Restaurant::Restaurant(){}:

Restaurant::Restaurant(const std::string &configFilePath) {

}

void Restaurant::start() {

}


int Restaurant::getNumOfTables() const {
    return static_cast<int>(tables.size());
}

Table *Restaurant::getTable(int ind) {
    return tables[ind];
}

const std::vector<BaseAction *> &Restaurant::getActionsLog() const {
    return actionsLog;
}


std::vector<Dish> &Restaurant::getMenu() {
    return menu;
}

void Restaurant::setMenu(std::vector<Dish> &menu) {
    this->menu = menu;
}

void Restaurant::setActionsLog(std::vector<BaseAction *> actionsLog) {
    this->actionsLog = actionsLog;
}

void Restaurant::setTables(std::vector<Table *> tables) {
    this->tables = tables;
}

void Restaurant::setStatus(bool open) {
    this->open = open;
}

bool Restaurant::getStatus() {
    return open;
}

std::vector<Table *> Restaurant::getTables() {
    return tables;
}
//destructor
Restaurant::~Restaurant() {
    clear();
}
//copy constructor(with file)
Restaurant::Restaurant(const Restaurant &other) {

}
//move constructor
Restaurant::Restaurant(Restaurant &&other) : open(other.open), tables(other.tables), menu(other.menu), actionsLog(other.actionsLog) {
    other.clear();
}
// Copy Assignment operator
Restaurant &Restaurant::operator=(const Restaurant &other) {
    if(this != &other){
        clear();
        open = other.open;
        tables = other.tables;
        menu = other.menu;
        actionsLog = other.actionsLog;
    }
}
// Move Assignment operator
Restaurant &Restaurant::operator=(Restaurant &&other) {
    if(this != &other){
        clear();
        open = other.open;
        tables = other.tables;
        menu = other.menu;
        actionsLog = other.actionsLog;
        other.clear();
    }
}

void Restaurant::clear() {
    open = false;
    menu.clear();
    for (auto &i : actionsLog) {
        delete i;
    }
}







