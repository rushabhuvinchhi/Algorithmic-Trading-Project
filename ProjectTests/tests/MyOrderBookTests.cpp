//
// Created by vinchhi on 12/4/19.
//

#include <gtest/gtest.h>
#include "../../MDReader.h"
#include "../../PriceUpdate.h"
#include "../../TradingStrategy.h"
#include "../../BookUpdate.h"
#include "../../MarketSimulator.h"
#include "../../OrderManager.h"
#include "../../MyOrderBook.h"

TEST(OrderBookTests, OrderBookEmptyByDefault)
{
    std::queue<Order> strategy_to_ordermanager_;
    std::queue<ExecutionOrder> ordermanager_to_strategy_;
    std::queue<Order> ordermanager_to_simulator_;
    std::queue<ExecutionOrder> simulator_to_ordermanager_;
    std::queue<BookUpdate> bookbuilder_to_strategy_;
    MyOrderBook book(strategy_to_ordermanager_,ordermanager_to_strategy_,ordermanager_to_simulator_,simulator_to_ordermanager_,bookbuilder_to_strategy_);
    EXPECT_TRUE(book.is_empty());
}

TEST(OrderBookTests, MyOrderBookEmptyByDefault)
{
    std::queue<Order> strategy_to_ordermanager_;
    std::queue<ExecutionOrder> ordermanager_to_strategy_;
    std::queue<Order> ordermanager_to_simulator_;
    std::queue<ExecutionOrder> simulator_to_ordermanager_;
    std::queue<BookUpdate> bookbuilder_to_strategy_;
    MyOrderBook book(strategy_to_ordermanager_,ordermanager_to_strategy_,ordermanager_to_simulator_,simulator_to_ordermanager_,bookbuilder_to_strategy_);
    EXPECT_TRUE(book.is_empty());
}
TEST(OrderBookTests, PriceUpdateHandlingTest)
{
    std::queue<Order> strategy_to_ordermanager_;
    std::queue<ExecutionOrder> ordermanager_to_strategy_;
    std::queue<Order> ordermanager_to_simulator_;
    std::queue<ExecutionOrder> simulator_to_ordermanager_;
    std::queue<BookUpdate> bookbuilder_to_strategy_;
    MyOrderBook book(strategy_to_ordermanager_,ordermanager_to_strategy_,ordermanager_to_simulator_,simulator_to_ordermanager_,bookbuilder_to_strategy_);
    PriceUpdate p1(action_t::NEW,130,10000,"JPMX", true, "EUR/USD", 1022, 1);
    PriceUpdate p2(action_t::NEW,111,10000,"JPMX", false, "EUR/USD", 1022, 2);
    book.handle_price_update(p1);
    book.handle_price_update(p2);
    EXPECT_EQ(bookbuilder_to_strategy_.front().get_price(),130);
    bookbuilder_to_strategy_.pop();
    EXPECT_EQ(bookbuilder_to_strategy_.front().get_price(),111);
    auto bidask=book.get_bid_ask();
    EXPECT_TRUE(bidask.bid.is_initialized());
    auto bid=bidask.bid.get();
    EXPECT_EQ(111, bid.first);
    EXPECT_EQ(10000, bid.second);
    MyOrderBook::BidAsk result;
    result = book.get_bid_ask();
    EXPECT_EQ(*result.spread(),19);

}
