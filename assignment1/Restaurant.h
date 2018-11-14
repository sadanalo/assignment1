
#ifndef RESTAURANT_H_
#define RESTAURANT_H_

#include <vector>
#include <string>
#include "Dish.h"
#include "Table.h"
#include "Action.h"


class Restaurant{
public:
    Restaurant();
    Restaurant(const std::string &configFilePath);
    void start();
    int getNumOfTables() const;
    Table* getTable(int ind);
    const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Dish>& getMenu();
    bool getStatus();//yot
    std::vector<Table*> getTables();//yot
    void setMenu(std::vector<Dish> &menu);//yot
    void setActionsLog(std::vector<BaseAction*> actionsLog);//yot
    void setTables(std::vector<Table*> tables);//yot
    void setStatus(bool open);//yot

    // Destructor
    virtual ~Restaurant();

    // Copy Constructor
    Restaurant(const Restaurant &other);

    // Move Constructor
    Restaurant(Restaurant &&other);

    // Copy Assignment operator
    Restaurant& operator=(const Restaurant &other);

    // Move Assignment operator
    Restaurant& operator=(Restaurant &&other);


private:
    bool open;
    std::vector<Table*> tables;
    void clear();


private:
    std::vector<Dish> menu;
    std::vector<BaseAction*> actionsLog;
};

#endif