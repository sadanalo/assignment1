
#include "Restaurant.h"

Restaurant::Restaurant():

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


