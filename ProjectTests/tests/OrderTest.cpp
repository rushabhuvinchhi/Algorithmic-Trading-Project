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

TEST(Order,Order_OrderDataStructure_Test)
{
    Order o1(100,true,1,10,1000,"JPMX","EURUSD",ordertype::LIMIT,false);

    EXPECT_EQ(o1.getID(),1);
    EXPECT_EQ(o1.getOrderType(),ordertype::LIMIT);
    EXPECT_EQ(o1.getPrice(),10);
    EXPECT_EQ(o1.getQuantity(),1000);
    EXPECT_EQ(strcmp(o1.getVenue(),"JPMX"),0);
    EXPECT_EQ(strcmp(o1.getSymbol(),"EURUSD"),0);
    EXPECT_EQ(o1.is_valid(), true);
    o1.setVenue("\0");
    EXPECT_FALSE(o1.is_valid());
    o1.setVenue("BARX");
    EXPECT_TRUE(o1.is_valid());
}

TEST(Order, Order_ExecutionOrderDataStructure_Test)
{
    Order o1(100,true,1,10,1000,"JPMX","EURUSD",ordertype::LIMIT,false);
    ExecutionOrder eo1(o1);
    EXPECT_EQ(eo1.getTimeStamp(),100);
    EXPECT_TRUE(eo1.isBuy());
    EXPECT_EQ(eo1.getPrice(),10);
    EXPECT_EQ(strcmp(eo1.getVenue(),"JPMX"),0);
    EXPECT_EQ(strcmp(eo1.getSymbol(),"EURUSD"),0);
}

TEST(Order,Order_DefaultValues_Test)
{
    Order o1;
    EXPECT_EQ(o1.getID(),0);
    EXPECT_EQ(o1.getOrderType(),ordertype::MARKET);
    EXPECT_EQ(o1.getPrice(),0);
    EXPECT_EQ(o1.getQuantity(),0);
    EXPECT_EQ(strcmp(o1.getVenue(),""),0);
    EXPECT_EQ(strcmp(o1.getSymbol(),""),0);
    EXPECT_EQ(o1.getAmend(), false);

}

TEST(Order,Order_SettingValues_Test)
{
    Order o1;
    o1.setOrderID(1);
    EXPECT_EQ(o1.getID(),1);
    o1.setType(ordertype::LIMIT);
    EXPECT_EQ(o1.getOrderType(),ordertype::LIMIT);
    o1.setPrice(100);
    EXPECT_EQ(o1.getPrice(),100);
    o1.setQuantity(10000);
    EXPECT_EQ(o1.getQuantity(),10000);
    o1.setSymbol("EUR/USD");
    o1.setVenue("JPMX");
    EXPECT_EQ(strcmp(o1.getVenue(),"JPMX"),0);
    EXPECT_EQ(strcmp(o1.getSymbol(),"EUR/USD"),0);
    o1.setAmend();
    EXPECT_EQ(o1.getAmend(), true);

}