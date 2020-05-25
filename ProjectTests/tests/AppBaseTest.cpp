//
// Created by vinchhi on 12/4/19.
//

#include <gtest/gtest.h>
#include "../../AppBase.h"
#include "../../TradingStrategy.h"

TEST(AppBaseTest, AppBaseTest_NotWorkingByDefault_Test)
{
    std::queue<Order> strategy_to_ordermanager;
    std::queue<ExecutionOrder> ordermanager_to_strategy;
    std::queue<Order> ordermanager_to_simulator;
    std::queue<ExecutionOrder> simulator_to_ordermanager;
    std::queue<BookUpdate> bookbuilder_to_strategy;
    TradingStrategy ts1(strategy_to_ordermanager, ordermanager_to_strategy,ordermanager_to_simulator,
            simulator_to_ordermanager,bookbuilder_to_strategy);
    EXPECT_FALSE(ts1.isWorking());
    ts1.start();
    EXPECT_TRUE(ts1.isWorking());

}

