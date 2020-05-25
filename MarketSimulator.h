//
// Created by vinchhi on 12/4/19.
//

#ifndef IEORCLASSPROJECT9_MARKETSIMULATOR_H
#define IEORCLASSPROJECT9_MARKETSIMULATOR_H
#include "AppBase.h"
#include "Order.h"
#include <set>
#include <queue>
#include <string>
#include <iostream>

class MarketSimulator : public AppBase {
public:
    unsigned execution_id;
    std::set<std::string> list_symbols;
    double pnl;
    MarketSimulator(
            std::queue<Order> &strategy_to_ordermanager_,
            std::queue<ExecutionOrder> &ordermanager_to_strategy_,
            std::queue<Order> &ordermanager_to_simulator_,
            std::queue<ExecutionOrder> &simulator_to_ordermanager_,
            std::queue<BookUpdate> &bookbuilder_to_strategy_
    );
    bool handle_order();

    virtual void start() {is_working=true;}
    virtual void stop() {is_working=false;}
    long long get_pnl();

};


#endif //IEORCLASSPROJECT9_MARKETSIMULATOR_H
