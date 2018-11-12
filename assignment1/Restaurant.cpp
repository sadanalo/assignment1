//
// Created by alon on 04/11/18.
//

#include "Restaurant.h"
Restaurant::Restaurant():
        Restaurant::Restaurant() {

}

Restaurant::Restaurant(const std::string &configFilePath) {

}

void Restaurant::start() {

}

int Restaurant::getNumOfTables() const {
    return 0;
}

Table *Restaurant::getTable(int ind) {
    return nullptr;
}

const std::vector<BaseAction *> &Restaurant::getActionsLog() const {
    return <#initializer#>;
}


std::vector<Dish> &Restaurant::getMenu() {
    return menu;
}
