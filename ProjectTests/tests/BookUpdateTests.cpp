//
// Created by vinchhi on 12/4/19.
//

#include <gtest/gtest.h>
#include "../../BookUpdate.h"

TEST(BookUpdateTest, BookUpdateTest_DataStructure_Test)
{
    BookUpdate b1(0,100,10000,"JPMX",true,"USD/EUR",1000);
    EXPECT_EQ(b1.get_level(),0);
    EXPECT_EQ(b1.get_price(),100);
    EXPECT_EQ(b1.get_quantity(),10000);
    EXPECT_TRUE(b1.get_is_buy());
    EXPECT_EQ(strcmp(b1.get_venue(),"JPMX"),0);
    EXPECT_EQ(strcmp(b1.get_symbol(),"USD/EUR"),0);
    EXPECT_EQ(b1.get_epoch_time(),1000);
}

TEST(BookUpdate, BookUpdate_PriceUpdateConstructor_Test)
{
    PriceUpdate p1(action_t::NEW,100,1000,"JPMX",true,"USD/EUR",1000,1);
    BookUpdate b1(p1);
    EXPECT_EQ(b1.get_level(),0);
    EXPECT_EQ(b1.get_price(),100);
    EXPECT_EQ(b1.get_quantity(),1000);
    EXPECT_TRUE(b1.get_is_buy());
    EXPECT_EQ(strcmp(b1.get_venue(),"JPMX"),0);
    EXPECT_EQ(strcmp(b1.get_symbol(),"USD/EUR"),0);
    EXPECT_EQ(b1.get_epoch_time(),1000);

}
