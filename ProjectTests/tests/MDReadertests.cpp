//
// Created by vinchhi on 12/3/19.
//
#include <gtest/gtest.h>
#include "../../MDReader.h"
#include "../../PriceUpdate.h"

TEST(MDParserTest,isWellParsed)
{
    MDReader reader("/home/vinchhi/Documents/ieorclassproject7/EUR_USD_Week1.csv",",",5);
    std::vector<PriceUpdate> dataList = reader.getData();
    char testsymbol[8] = "EUR/USD";
    EXPECT_EQ(strcmp(dataList[0].get_symbol(),testsymbol),0);
    EXPECT_EQ(dataList[0].get_epoch_time(),1535907608);
    EXPECT_FLOAT_EQ(dataList[0].get_price(),1.1595);
}

