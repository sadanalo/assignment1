
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



private:
    bool open;
    std::vector<Table*> tables;


private:
    std::vector<Dish> menu;
    std::vector<BaseAction*> actionsLog;
};

#endif