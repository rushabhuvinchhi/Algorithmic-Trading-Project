//
// Created by vinchhi on 12/3/19.
//

#ifndef IEORCLASSPROJECT9_MYORDERBOOK_H
#define IEORCLASSPROJECT9_MYORDERBOOK_H
#include "AppBase.h"
#include "MDReader.h"
#include "PriceUpdate.h"
#include <map>
#include <iostream>
#include <boost/optional.hpp>
#include <unordered_map>
#include "BookUpdate.h"
typedef std::multimap<price_t,PriceUpdate>::iterator MapIter;
typedef std::multimap<price_t,PriceUpdate>::reverse_iterator MapReverseIter;
typedef std::unordered_map<order_id_t ,MapIter>::iterator HashmapIter;

//Multimaps: price -> order
typedef std::multimap<price_t,PriceUpdate,std::greater<price_t > > BidsMap;
typedef std::multimap<price_t,PriceUpdate,std::less<price_t > > AsksMap;

// Hashmaps: order id -> multimap iterator (for quick lookup by order ID)
typedef std::unordered_map<order_id_t ,MapIter> BidsHash;
typedef std::unordered_map<order_id_t ,MapIter> AsksHash;

class MyOrderBook : public AppBase
{
private:
    std::vector<PriceUpdate> dataList;
    BidsMap bids;
    BidsHash bidshash;
    AsksMap asks;
    AsksHash askhash;
public:
    MyOrderBook(std::queue<Order> &strategy_to_ordermanager_,
                std::queue<ExecutionOrder> &ordermanager_to_strategy_,
                std::queue<Order> &ordermanager_to_simulator_,
                std::queue<ExecutionOrder> &simulator_to_ordermanager_,
                std::queue<BookUpdate> &bookbuilder_to_strategy_):
                AppBase(strategy_to_ordermanager_,
                        ordermanager_to_strategy_,
                        ordermanager_to_simulator_,
                        simulator_to_ordermanager_,
                        bookbuilder_to_strategy_){};

    struct BidAsk
    {
        typedef boost::optional<std::pair<int, int>> Entry;
        Entry bid, ask;
        boost::optional<int> spread() const;
    };
    virtual void start();
    virtual void stop();

    bool is_empty() const;
    void handle_price_update(const PriceUpdate &pu);
    void clear();

    BidAsk get_bid_ask() ;
    friend std::ostream & operator << (std::ostream &os, const MyOrderBook &book);
    friend std::ostream & operator << (std::ostream &os, const MyOrderBook::BidAsk &ba);
};
#endif //IEORCLASSPROJECT9_MYORDERBOOK_H
