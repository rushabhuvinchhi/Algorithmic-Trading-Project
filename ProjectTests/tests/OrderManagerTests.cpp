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

TEST(OrderManagerTest,OrderManager_HandlingOrder_Test)
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
    EXPECT_EQ(ordermanager_to_simulator_.front().getPrice(),123);
    EXPECT_EQ(ordermanager_to_simulator_.front().getQuantity(),10000);
    EXPECT_EQ(ordermanager_to_simulator_.front().getID(),1);
    Order b2(1,true,13,123,10000,"JPMX","EUR/USD",ordertype::LIMIT,0);
    strategy_to_ordermanager_.push(b1);
    manager.handle_order();
    ordermanager_to_simulator_.pop();
    EXPECT_EQ(ordermanager_to_simulator_.front().getID(),2);

}

TEST(OrderManagerTest,OrderManager_HandlingExecutionOrder)
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
    manager.handle_order();
    Order b2(1,true,13,125,10001,"JPMX","EUR/USD",ordertype::LIMIT,0);
    strategy_to_ordermanager_.push(b2);
    manager.handle_order();
    simulator.handle_order();
    EXPECT_TRUE(manager.handle_execution_order());
    EXPECT_EQ(ordermanager_to_strategy_.front().getPrice(),123);
    EXPECT_EQ(ordermanager_to_strategy_.front().getQuantity(),10000);
    ordermanager_to_strategy_.pop(); //acknowledged
    ordermanager_to_strategy_.pop(); //filled
    EXPECT_EQ(ordermanager_to_strategy_.front().getPrice(),125);
    EXPECT_EQ(ordermanager_to_strategy_.front().getQuantity(),10001);
}

TEST(OrderManagerTest, OrderManagerTest_NumberofOpenandNonAck_Test)
{
    std::queue<Order> strategy_to_ordermanager_;
    std::queue<ExecutionOrder> ordermanager_to_strategy_;
    std::queue<Order> ordermanager_to_simulator_;
    std::queue<ExecutionOrder> simulator_to_ordermanager_;
    std::queue<BookUpdate> bookbuilder_to_strategy_;
    MarketSimulator simulator(strategy_to_ordermanager_,ordermanager_to_strategy_,ordermanager_to_simulator_,simulator_to_ordermanager_,bookbuilder_to_strategy_);
    OrderManager manager(strategy_to_ordermanager_,ordermanager_to_strategy_,ordermanager_to_simulator_,simulator_to_ordermanager_,bookbuilder_to_strategy_);
    simulator.start();
    manager.start();
    for(int i = 0; i < 3 ; i++)
    {
        Order o(1,true,i,125,10000,"JPMX","EUR/USD",ordertype::LIMIT,0);
        strategy_to_ordermanager_.push(o);
    }
    manager.handle_order();
    EXPECT_EQ(manager.get_number_of_non_acknowledged_orders(),3);
    simulator.handle_order();
    manager.handle_execution_order();
    EXPECT_EQ(manager.get_number_of_open_orders(),0);
}
TEST(OrderManagerTest, OrderManagerTest_Position_Test)
{
    std::queue<Order> strategy_to_ordermanager_;
    std::queue<ExecutionOrder> ordermanager_to_strategy_;
    std::queue<Order> ordermanager_to_simulator_;
    std::queue<ExecutionOrder> simulator_to_ordermanager_;
    std::queue<BookUpdate> bookbuilder_to_strategy_;
    MarketSimulator simulator(strategy_to_ordermanager_,ordermanager_to_strategy_,ordermanager_to_simulator_,simulator_to_ordermanager_,bookbuilder_to_strategy_);
    OrderManager manager(strategy_to_ordermanager_,ordermanager_to_strategy_,ordermanager_to_simulator_,simulator_to_ordermanager_,bookbuilder_to_strategy_);
    simulator.start();
    manager.start();
    for(int i = 0; i < 3 ; i++)
    {
        Order o(1,true,i,125,10000,"JPMX","EUR/USD",ordertype::LIMIT,0);
        strategy_to_ordermanager_.push(o);
    }
    manager.handle_order();

    simulator.handle_order();
    manager.handle_execution_order();
    EXPECT_EQ(manager.get_position("EUR/USD"),3750000);
}

