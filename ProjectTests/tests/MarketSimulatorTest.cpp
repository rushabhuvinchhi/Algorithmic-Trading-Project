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

TEST(MarketSimulatorTest, MarketSimulatorTest_ProcessAcknowledgmentandFilL_Test)
{
    std::queue<Order> strategy_to_ordermanager_;
    std::queue<ExecutionOrder> ordermanager_to_strategy_;
    std::queue<Order> ordermanager_to_simulator_;
    std::queue<ExecutionOrder> simulator_to_ordermanager_;
    std::queue<BookUpdate> bookbuilder_to_strategy_;
    MarketSimulator simulator(strategy_to_ordermanager_,ordermanager_to_strategy_,ordermanager_to_simulator_,simulator_to_ordermanager_,bookbuilder_to_strategy_);
    OrderManager manager(strategy_to_ordermanager_,ordermanager_to_strategy_,ordermanager_to_simulator_,simulator_to_ordermanager_,bookbuilder_to_strategy_);
    Order b1(1,true,12,123,10000,"JPMX","EUR/USD",ordertype::LIMIT,0);
    simulator.start();
    manager.start();
    strategy_to_ordermanager_.push(b1);
    EXPECT_TRUE(manager.handle_order());
    EXPECT_TRUE(simulator.handle_order());
    EXPECT_EQ(simulator_to_ordermanager_.front().getState(),orderstate::ACKNOWLEDGED);
    simulator_to_ordermanager_.pop();
    EXPECT_EQ(simulator_to_ordermanager_.front().getState(),orderstate::FILLED);

}
TEST(MarketSimulator,MarketSimulator_ProcessReject_Test)
{
    std::queue<Order> strategy_to_ordermanager_;
    std::queue<ExecutionOrder> ordermanager_to_strategy_;
    std::queue<Order> ordermanager_to_simulator_;
    std::queue<ExecutionOrder> simulator_to_ordermanager_;
    std::queue<BookUpdate> bookbuilder_to_strategy_;
    MarketSimulator simulator(strategy_to_ordermanager_,ordermanager_to_strategy_,ordermanager_to_simulator_,simulator_to_ordermanager_,bookbuilder_to_strategy_);
    OrderManager manager(strategy_to_ordermanager_,ordermanager_to_strategy_,ordermanager_to_simulator_,simulator_to_ordermanager_,bookbuilder_to_strategy_);

    //Symbol not trading so reject
    Order b1(1,true,12,123,10000,"JPMX","EAB",ordertype::LIMIT,0);

    simulator.start();
    manager.start();
    strategy_to_ordermanager_.push(b1);
    EXPECT_TRUE(manager.handle_order());
    EXPECT_TRUE(simulator.handle_order());
    EXPECT_EQ(simulator_to_ordermanager_.front().getState(),orderstate::REJECTED);
    while(!simulator_to_ordermanager_.empty())
        simulator_to_ordermanager_.pop();
    while(!strategy_to_ordermanager_.empty())
        strategy_to_ordermanager_.pop();

    //Quantity too low
    Order b2(1,true,12,123,10,"JPMX","EUR/USD",ordertype::LIMIT,0);
    strategy_to_ordermanager_.push(b2);
    manager.handle_order();
    simulator.handle_order();
    EXPECT_EQ(simulator_to_ordermanager_.front().getState(),orderstate::REJECTED);
    while(!simulator_to_ordermanager_.empty())
        simulator_to_ordermanager_.pop();
    while(!strategy_to_ordermanager_.empty())
        strategy_to_ordermanager_.pop();
}
