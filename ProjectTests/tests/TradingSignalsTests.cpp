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

TEST(SignalTest, MAworkingwell)
{
    Signal sig1;
    BookUpdate b1(0,10,10000,"GAIN",true,"EURUSD",0);
    BookUpdate b2(0,12,10000,"GAIN",false,"EURUSD",0);
    BookUpdate b3(0,14,10000,"GAIN",true,"EURUSD",280);
    BookUpdate b4(0,15,10000,"GAIN",false,"EURUSD",280);
    BookUpdate b5(0,14,10000,"GAIN",true,"EURUSD",290);
    BookUpdate b6(0,15,10000,"GAIN",false,"EURUSD",290);
    sig1.insert_book_update(b1);
    sig1.insert_book_update(b2);
    sig1.insert_book_update(b3);
    sig1.insert_book_update(b4);
    sig1.insert_book_update(b5);
    sig1.insert_book_update(b6);
    EXPECT_FLOAT_EQ(sig1.get_5min_moving_average(),40.0/3);
    BookUpdate b7(0,14,10000,"GAIN",true,"EURUSD",300);
    BookUpdate b8(0,16,10000,"GAIN",false,"EURUSD",300);
    sig1.insert_book_update(b7);
    sig1.insert_book_update(b8);
    EXPECT_FLOAT_EQ((sig1.get_20min_moving_average()),13.75);
    EXPECT_FLOAT_EQ((sig1.get_5min_moving_average()),13.75);
}

TEST(SignalTest,Signalworkingwell)
{
    Signal sig1;
    BookUpdate b1(0,10,10000,"GAIN",true,"EURUSD",0);
    BookUpdate b2(0,12,10000,"GAIN",false,"EURUSD",0);
    BookUpdate b3(0,14,10000,"GAIN",true,"EURUSD",280);
    BookUpdate b4(0,15,10000,"GAIN",false,"EURUSD",280);
    BookUpdate b5(0,14,10000,"GAIN",true,"EURUSD",290);
    BookUpdate b6(0,15,10000,"GAIN",false,"EURUSD",290);
    sig1.insert_book_update(b1);
    sig1.insert_book_update(b2);
    sig1.insert_book_update(b3);
    sig1.insert_book_update(b4);
    sig1.insert_book_update(b5);
    sig1.insert_book_update(b6);
    BookUpdate b7(0,14,10000,"GAIN",true,"EURUSD",300);
    BookUpdate b8(0,16,10000,"GAIN",false,"EURUSD",300);
    sig1.insert_book_update(b7);
    sig1.insert_book_update(b8);
    EXPECT_FALSE(sig1.go_long());
    EXPECT_FALSE(sig1.go_short());
}

TEST(TradingStrategy,TradeSignalTest)
{
    std::queue<Order> strategy_to_ordermanager;
    std::queue<ExecutionOrder> ordermanager_to_strategy;
    std::queue<Order> ordermanager_to_simulator;
    std::queue<ExecutionOrder> simulator_to_ordermanager;
    std::queue<BookUpdate> bookbuilder_to_strategy;
    BookUpdate b1(0,10,10000,"GAIN",true,"EURUSD",0);
    BookUpdate b2(0,12,10000,"GAIN",false,"EURUSD",0);
    BookUpdate b3(0,14,10000,"GAIN",true,"EURUSD",280);
    BookUpdate b4(0,15,10000,"GAIN",false,"EURUSD",280);
    BookUpdate b5(0,14,10000,"GAIN",true,"EURUSD",290);
    BookUpdate b6(0,15,10000,"GAIN",false,"EURUSD",290);
    BookUpdate b7(0,14,10000,"GAIN",true,"EURUSD",300);
    BookUpdate b8(0,16,10000,"GAIN",false,"EURUSD",300);
    BookUpdate b9(0,14,10000,"GAIN",true,"EURUSD",320);
    BookUpdate b10(0,15,10000,"GAIN",false,"EURUSD",320);
    bookbuilder_to_strategy.push(b1);
    bookbuilder_to_strategy.push(b2);
    bookbuilder_to_strategy.push(b3);
    bookbuilder_to_strategy.push(b4);
    bookbuilder_to_strategy.push(b5);
    bookbuilder_to_strategy.push(b6);
    bookbuilder_to_strategy.push(b7);
    bookbuilder_to_strategy.push(b8);
    bookbuilder_to_strategy.push(b9);
    bookbuilder_to_strategy.push(b10);
    TradingStrategy ts1(strategy_to_ordermanager,
                        ordermanager_to_strategy,
                        ordermanager_to_simulator,
                        simulator_to_ordermanager,
                        bookbuilder_to_strategy);
    ts1.process_book_update_from_ring();
    EXPECT_TRUE(strategy_to_ordermanager.front().isBuy());

}

TEST(TradingStrategy, PNL)
{
    std::queue<Order> strategy_to_ordermanager;
    std::queue<ExecutionOrder> ordermanager_to_strategy;
    std::queue<Order> ordermanager_to_simulator;
    std::queue<ExecutionOrder> simulator_to_ordermanager;
    std::queue<BookUpdate> bookbuilder_to_strategy;
    BookUpdate b1(0,10,10000,"GAIN",true,"EURUSD",0);
    BookUpdate b2(0,12,10000,"GAIN",false,"EURUSD",0);
    BookUpdate b3(0,14,10000,"GAIN",true,"EURUSD",280);
    BookUpdate b4(0,15,10000,"GAIN",false,"EURUSD",280);
    BookUpdate b5(0,14,10000,"GAIN",true,"EURUSD",290);
    BookUpdate b6(0,15,10000,"GAIN",false,"EURUSD",290);
    BookUpdate b7(0,14,10000,"GAIN",true,"EURUSD",300);
    BookUpdate b8(0,16,10000,"GAIN",false,"EURUSD",300);
    BookUpdate b9(0,14,10000,"GAIN",true,"EURUSD",320);
    BookUpdate b10(0,15,10000,"GAIN",false,"EURUSD",320);
    bookbuilder_to_strategy.push(b1);
    bookbuilder_to_strategy.push(b2);
    bookbuilder_to_strategy.push(b3);
    bookbuilder_to_strategy.push(b4);
    bookbuilder_to_strategy.push(b5);
    bookbuilder_to_strategy.push(b6);
    bookbuilder_to_strategy.push(b7);
    bookbuilder_to_strategy.push(b8);
    bookbuilder_to_strategy.push(b9);
    bookbuilder_to_strategy.push(b10);
    TradingStrategy ts1(strategy_to_ordermanager,
                        ordermanager_to_strategy,
                        ordermanager_to_simulator,
                        simulator_to_ordermanager,
                        bookbuilder_to_strategy);

    MarketSimulator simulator(strategy_to_ordermanager,
                              ordermanager_to_strategy,
                              ordermanager_to_simulator,
                              simulator_to_ordermanager,
                              bookbuilder_to_strategy);

    OrderManager order_manager(strategy_to_ordermanager,
                               ordermanager_to_strategy,
                               ordermanager_to_simulator,
                               simulator_to_ordermanager,
                               bookbuilder_to_strategy);

    MyOrderBook book(strategy_to_ordermanager,
                             ordermanager_to_strategy,
                             ordermanager_to_simulator,
                             simulator_to_ordermanager,
                             bookbuilder_to_strategy);
    ts1.process_book_update_from_ring();
    order_manager.handle_order();
    simulator.handle_order();
    order_manager.handle_execution_order();
    ts1.process_market_response();
    EXPECT_EQ(ts1.get_pnl(),simulator.get_pnl());
}
