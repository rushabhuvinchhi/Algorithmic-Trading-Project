#include <iostream>
#include "AppBase.h"
#include "BookUpdate.h"
#include "MarketSimulator.h"
#include "Order.h"
#include "OrderManager.h"
#include "MyOrderBook.h"
#include "TradingStrategy.h"


int main()
{
    //Initialise Communication buffers

    std::queue<Order> strategy_to_ordermanager;
    std::queue<ExecutionOrder> ordermanager_to_strategy;
    std::queue<Order> ordermanager_to_simulator;
    std::queue<ExecutionOrder> simulator_to_ordermanager;
    std::queue<BookUpdate> bookbuilder_to_strategy;

    //Initialise OrderBook

    MyOrderBook myBook(strategy_to_ordermanager, ordermanager_to_strategy,ordermanager_to_simulator,simulator_to_ordermanager,bookbuilder_to_strategy);
    //Reads from the Excel File and pushes to Strategy
    myBook.start();
    //print book
    std::cout << myBook << std::endl;


    //Initialise Trading Strategy

    TradingStrategy TS(strategy_to_ordermanager, ordermanager_to_strategy,ordermanager_to_simulator,simulator_to_ordermanager,bookbuilder_to_strategy);
    TS.start();
    //pushes to ordermanager
    TS.process_book_update_from_ring();


    //Initialise OrderManager

    OrderManager OM(strategy_to_ordermanager, ordermanager_to_strategy,ordermanager_to_simulator,simulator_to_ordermanager,bookbuilder_to_strategy);
    OM.start();
    //pushes to simulator
    OM.handle_order();


    //Initialise Simulator

    MarketSimulator SIM(strategy_to_ordermanager, ordermanager_to_strategy,ordermanager_to_simulator,simulator_to_ordermanager,bookbuilder_to_strategy);
    SIM.start();
    //pushes back to ordermanager
    SIM.handle_order();

    //pushes back to strategy
    OM.handle_execution_order();

    //TradingStrategy evaluates
    TS.process_market_response();

    std::cout << "Profit from Strategy : " << TS.get_pnl() << std::endl;
    std::cout << "Profit from Market Simulator: " << SIM.get_pnl() <<std::endl;

    myBook.stop();
    TS.stop();
    OM.stop();
    SIM.stop();

}