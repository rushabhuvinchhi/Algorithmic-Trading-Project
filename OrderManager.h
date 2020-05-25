//
// Created by vinchhi on 12/4/19.
//

#ifndef IEORCLASSPROJECT9_ORDERMANAGER_H
#define IEORCLASSPROJECT9_ORDERMANAGER_H
#include "AppBase.h"
#include "Order.h"
#include <unordered_map>
#include <iostream>

class OrderManager : public AppBase{
public:
    unsigned int order_id;
    Order order;
    ExecutionOrder execution_order;
    std::unordered_map<unsigned int, ExecutionOrder> list_orders;
    std::unordered_map<std::string,int> positions;
    OrderManager(
            std::queue<Order> &strategy_to_ordermanager_,
            std::queue<ExecutionOrder> &ordermanager_to_strategy_,
            std::queue<Order> &ordermanager_to_simulator_,
            std::queue<ExecutionOrder> &simulator_to_ordermanager_,
            std::queue<BookUpdate> &bookbuilder_to_strategy_
    ):AppBase(strategy_to_ordermanager_,
              ordermanager_to_strategy_,
              ordermanager_to_simulator_,
              simulator_to_ordermanager_,
              bookbuilder_to_strategy_)
            ,order_id(0){};

    virtual void start() ;
    virtual void stop() ;
    void reset_position();

    bool handle_order();
    bool handle_execution_order();
    unsigned int get_number_of_open_orders();
    unsigned int get_number_of_non_acknowledged_orders();
    int get_position(std::string symbol);

};


#endif //IEORCLASSPROJECT9_ORDERMANAGER_H
