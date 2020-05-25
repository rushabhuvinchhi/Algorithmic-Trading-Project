//
// Created by vinchhi on 12/4/19.
//

#include <gtest/gtest.h>
#include "../../PriceUpdate.h"
#include "../../BookUpdate.h"

TEST(PriceUpdateTest, PriceUpdateTest_DataStructure_Test)
{
    PriceUpdate p1(action_t::NEW,100,1000,"JPMX",true,"EUR/USD",1020,1);
    EXPECT_EQ(p1.get_action(),action_t::NEW);
    EXPECT_EQ(p1.get_price(),100);
    EXPECT_EQ(p1.get_quantity(),1000);
    EXPECT_EQ(strcmp(p1.get_symbol(),"EUR/USD"),0);
    EXPECT_TRUE(p1.get_is_buy());
    EXPECT_EQ(p1.get_epoch_time(),1020);
}
