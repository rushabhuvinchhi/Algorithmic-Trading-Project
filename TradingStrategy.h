//
// Created by vinchhi on 12/3/19.
//

#ifndef IEORCLASSPROJECT9_TRADINGSTRATEGY_H
#define IEORCLASSPROJECT9_TRADINGSTRATEGY_H
#include "AppBase.h"
#include "BookUpdate.h"
#include "Order.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <stack>
class Signal{
private:
    std::deque<BookUpdate> q5;
    std::deque<BookUpdate> q20;
    double total5;
    double total20;
    bool firstBuy;
    bool firstSell;
public:
    Signal():total5(0.0),total20(0.0),firstBuy(1),firstSell(1){}
    bool is_tradeable(BookUpdate &bu);
    void insert_book_update(BookUpdate &bu);
    double get_5min_moving_average();
    double get_20min_moving_average();
    bool go_long();
    bool go_short();

};

class Execution{
private:
    Order e;
    bool tradeable;
    int order_id;

public:
    Execution():tradeable(false),order_id(1){}
    bool insert_order(BookUpdate bu);
    bool is_tradeable();
    void set_tradeable(bool is_tradable);
    Order & get_order();
};

class TradingStrategy : public AppBase{
private:
    Signal signal;
    Execution execution;
    int order_id;
    std::unordered_map<std::string,int> positions;
    unsigned int number_of_rejections;
    unsigned int number_of_fills;
    double pnl;
    bool firstBuy, firstSell;
    std::vector<long> date;
    std::ofstream myfile;
    std::vector<int> islong;
    std::stack<int> oldquant; //keeping track of amendment orders
public:
    TradingStrategy(
            std::queue<Order> &strategy_to_ordermanager_,
            std::queue<ExecutionOrder> &ordermanager_to_strategy_,
            std::queue<Order> &ordermanager_to_simulator_,
            std::queue<ExecutionOrder> &simulator_to_ordermanager_,
            std::queue<BookUpdate> &bookbuilder_to_strategy_
    ):
            AppBase(strategy_to_ordermanager_,
                    ordermanager_to_strategy_,
                    ordermanager_to_simulator_,
                    simulator_to_ordermanager_,
                    bookbuilder_to_strategy_),
            signal(),
            execution(),
            order_id(1),
            number_of_rejections(0),
            number_of_fills(0),
            pnl(0){}
    virtual void start() ;
    virtual void stop() ;

    bool process_book_update(BookUpdate &bu);
    bool process_book_update_from_ring();
    bool process_execution();
    bool process_amendment(int quantity);
    bool process_market_response();
    int get_position(std::string symbol);
    double get_5min_moving_average();
    double get_20min_moving_average();
    bool go_long();
    bool go_short();
    unsigned int get_number_of_rejections();
    unsigned int get_number_of_fills();
    void reset_position();
    long long get_pnl();
    bool isWorking();

};

#endif //IEORCLASSPROJECT9_TRADINGSTRATEGY_H
