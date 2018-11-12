//
// Created by alon on 04/11/18.
//

#include "Customer.h"
#include <limits>

Customer::Customer(std::string c_name, int c_id):id(c_id) , name(c_name) {}

std::string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}

std::vector<int> &Customer::getOrders() {
    return orders;
}

//class vegetarian customer/////////////////////////////////

VegetarianCustomer::VegetarianCustomer(std::string name, int id) : Customer(name, id) {

}


std::vector<int> VegetarianCustomer::order(const std::vector<Dish> &menu) {

    int lowestVegDishId = std::numeric_limits <int>::infinity();
    int mostExpensiveBvgPrice = -1;
    int mostExpensiveBvgId = std::numeric_limits <int>::infinity();

    for (int j = 0; j < menu.size(); ++j) {

        //checking which dish is Veg and has the lowest ID//
        if (menu[j].getType() == VEG && menu[j].getId() <= lowestVegDishId) {
            lowestVegDishId = menu[j].getId();

        }
        //checking which beverage has the highest price and lowest ID//
        if (menu[j].getType() == BVG && menu[j].getPrice() > mostExpensiveBvgPrice) {
            mostExpensiveBvgPrice = menu[j].getPrice();
            mostExpensiveBvgId = menu[j].getId();
        }
       //checking if there are two beverages with the same (highest) price//
        if (menu[j].getType() == BVG && menu[j].getPrice() == mostExpensiveBvgPrice) {
            if (menu[j].getId() <= mostExpensiveBvgId) {
                mostExpensiveBvgId = menu[j].getId();
            }
        }
    }
    //making  sure that there is a veg dish in the menu//
    if (lowestVegDishId < std::numeric_limits <int>::infinity()) {
        getOrders().push_back(lowestVegDishId);
    }
    //making sure that there is a soft drink in the menu//
    if (mostExpensiveBvgId < std::numeric_limits <int>::infinity()) {
        getOrders().push_back(mostExpensiveBvgId);
    }

    return getOrders();
}

std::string VegetarianCustomer::toString() const {
    return this->getName();

}
//class cheap customer/////////////////////////////////////
CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {

    }
std::vector<int> CheapCustomer::order(const std::vector<Dish> &menu) {

    int cheapestDishID= -1;
    int cheapestDishPrice = std::numeric_limits <int>::infinity();

    for (int i = 0; i < menu.size(); ++i) {
        if (menu[i].getPrice() < cheapestDishPrice) {
            cheapestDishPrice = menu[i].getPrice();
            cheapestDishID = menu [i].getId();
        }
        if(menu[i].getPrice() == cheapestDishPrice){
            if(menu[i].getId() <= cheapestDishID){
                cheapestDishID = menu[i].getId();
            }
        }
    }
//checking if the costumer ordered already //
    if( getOrders().size() == 0  ) {
    getOrders().push_back(cheapestDishID);
    }

        return getOrders();
    }



std::string CheapCustomer::toString() const {
    return this->getName();
}

//class spicy customer/////////////////////////////////////////////

SpicyCustomer::SpicyCustomer(std::string name, int id) : Customer(name, id) {
}

std::vector<int> SpicyCustomer::order(const std::vector<Dish> &menu) {
    int mostExpensiveSpcPrice = -1;
    int mostExpensiveSpcId = -1;

   //first Order- most expensive Spc dish//
   if(getOrders().size() == 0) {
       for (int i = 0; i < menu.size(); ++i) {
           if (menu[i].getType() == SPC && menu[i].getPrice() > mostExpensiveSpcPrice) {
               mostExpensiveSpcId = menu[i].getId();
               mostExpensiveSpcPrice = menu[i].getPrice();
           }
           if (menu[i].getType() == SPC && menu[i].getPrice() == mostExpensiveSpcPrice) {
             if(menu[i].getId() <= mostExpensiveSpcId){
                 mostExpensiveSpcId = menu[i].getId();
             }
           }
       }
      //making sure there is a spicy dish in the menu//
       if (mostExpensiveSpcId != -1) {
           getOrders().push_back(mostExpensiveSpcId);
       }
   }
    //further orders-cheapest bvg//
    if(getOrders().size() > 0) {
        int cheapestBvgPrice = std::numeric_limits<int>::infinity();
        int cheapestBvgId = -1;

        for (int j = 0; j < menu.size(); ++j) {
            if (menu[j].getType() == BVG && menu[j].getPrice() < cheapestBvgPrice) {
                cheapestBvgId = menu[j].getId();
                cheapestBvgPrice = menu[j].getPrice();
            }
            if(menu[j].getType() == BVG && menu[j].getPrice() == cheapestBvgPrice){
                if(menu[j].getId() <= cheapestBvgId){
                    cheapestBvgId = menu[j].getId();
                }
            }
        }
        //making sure there is a Bvg on the menu//
        if (cheapestBvgId != -1) {
            getOrders().push_back(cheapestBvgId);
        }
    }
    return getOrders();
}

std::string SpicyCustomer::toString() const {
    return this->getName();
}

// alcoholic customer//
AlchoholicCustomer::AlchoholicCustomer(std::string name, int id) : Customer(name, id), lastOrderedAlcPrice(-1) {

}

std::vector<int> AlchoholicCustomer::order(const std::vector<Dish> &menu) {

    int nextCheapAlcPrice = std::numeric_limits<int>::infinity();
    int nextCheapAlcId = -1;

  if(getOrders()[0] == 0) {    //assuming that a vector<int> default initialization is 0//
      for (int i = 0; i < menu.size(); ++i) {
          if (menu[i].getType() == ALC && menu[i].getPrice() < nextCheapAlcPrice) {
              nextCheapAlcId = menu[i].getId();
              nextCheapAlcPrice = menu[i].getPrice();
          }
      }
  }
  else {
      for (int i = 0; i < menu.size(); ++i) {
          if (menu[i].getType() == ALC && menu[i].getPrice() < nextCheapAlcPrice &&
              menu[i].getPrice() >= lastOrderedAlcPrice) {
              nextCheapAlcId = menu[i].getId();
              nextCheapAlcPrice = menu[i].getPrice();
          }
          if (menu[i].getType() == ALC && menu[i].getPrice() == nextCheapAlcPrice &&
              menu[i].getPrice() >= lastOrderedAlcPrice) {
              if (menu[i].getId() <= nextCheapAlcId) {
                  nextCheapAlcId = menu[i].getId();
              }
          }

      }

      if (nextCheapAlcPrice == lastOrderedAlcPrice) {
          if(nextCheapAlcId < getOrders()[getOrders().size()-1]){ //last ordered Alc was with the same price but higher ID//
              getOrders().push_back(nextCheapAlcId);
              return getOrders();
          }else{  //last ordedred Alc was the most expensive one//
            return getOrders();
          }
      }

      if(nextCheapAlcPrice > lastOrderedAlcPrice || (nextCheapAlcPrice == lastOrderedAlcPrice && nextCheapAlcId < getOrders()[getOrders().size()-1]) {
          lastOrderedAlcPrice = nextCheapAlcPrice;
      }
  }
}



return getOrders();

}

std::string AlchoholicCustomer::toString() const {
    return getName();
}
