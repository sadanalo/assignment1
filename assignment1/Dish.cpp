//
// Created by alon on 04/11/18.
//

#include "Dish.h"

Dish::Dish(int d_id, std::string d_name, int d_price, DishType d_type) {
this->id=d_id;
this->name=d_name;
this->price=d_price;
this->type=d_type;
}


int Dish::getId() const {
    return id;
}

std::string Dish::getName() const {
    return name;
}

int Dish::getPrice() const {
    return price;
}

DishType Dish::getType() const {
    return type;
}

