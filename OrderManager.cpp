//
// Created by vinchhi on 12/4/19.
//

#include "OrderManager.h"

void OrderManager::start()
{
    is_working=true;
}
void OrderManager::stop()
{
    list_orders.clear();
    is_working=false;
}

void OrderManager::reset_position()
{
    positions.clear();
}

bool OrderManager::handle_execution_order(){
    if(!is_working)
        return false;
    int number_of_orders_gone = order_id + 1 ;
    while(!simulator_to_ordermanager.empty())
    {
        const ExecutionOrder &e = simulator_to_ordermanager.front();
        execution_order = e;
        simulator_to_ordermanager.pop();
        execution_order.setOrderID(e.getID());
        execution_order.setState(e.getState());
        ordermanager_to_strategy.push(execution_order);
        list_orders[--number_of_orders_gone] = execution_order;
        if(e.getState() == orderstate::ACKNOWLEDGED)
        {
            const ExecutionOrder & e1 = simulator_to_ordermanager.front();
            execution_order = e1;
            simulator_to_ordermanager.pop();
            execution_order.setOrderID(e1.getID());
            execution_order.setState(e1.getState());
            ordermanager_to_strategy.push(execution_order);
            list_orders[number_of_orders_gone] = execution_order;
        }
    }
    return true;
};


unsigned int OrderManager::get_number_of_open_orders()
{
    unsigned int count = 0;
    auto i = list_orders.begin();
    while(i!=list_orders.end())
    {
        if((i->second).getState() == orderstate::OPEN || (i->second).getState() == orderstate::ACKNOWLEDGED )
            count++;
        i++;
    }
    return count;
}


unsigned int OrderManager::get_number_of_non_acknowledged_orders()
{
    unsigned int count = 0;
    auto i = list_orders.begin();
    while(i!=list_orders.end())
    {
        if((i->second).getState() == orderstate::OPEN) {
            count++;
        }
        i++;
    }
    return count;
}

int OrderManager::get_position(std::string symbol)
{
    std::unordered_map<std::string,int>::const_iterator got = positions.find(symbol);
    if(got == positions.end())
        return 0;
    else
        return got->second;
}

bool OrderManager::handle_order(){
    if(!is_working)
        return false;
    while(!strategy_to_ordermanager.empty())
    {
        const Order &e = strategy_to_ordermanager.front();
        strategy_to_ordermanager.pop();
        order_id++;
        order = e;
        std::unordered_map<std::string, int>::const_iterator got = positions.find(order.getSymbol());
        if (got == positions.end())
            positions[e.getSymbol()] = 0;
        int position = (e.isBuy() ? e.getPrice() * e.getQuantity() : -e.getPrice() * e.getQuantity());
        if (e.getQuantity() < 10  )
        {

            execution_order = e;
            execution_order.setOrderID(order_id);
            execution_order.setState(orderstate::REJECTED);
            ordermanager_to_strategy.push(execution_order);
            return false;
        }
        order.setOrderID(order_id);
        list_orders[order_id] = order;
        positions[e.getSymbol()] += position;
        list_orders[order_id].setState(orderstate::OPEN);
        if (e.getAmend())
        {
            order.setAmend();
        }
        ordermanager_to_simulator.push(order);
    }
    return true;
}