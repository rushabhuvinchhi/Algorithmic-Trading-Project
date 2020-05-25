//
// Created by vinchhi on 12/3/19.
//

#include <fstream>
#include "TradingStrategy.h"

//Signal
bool Signal::is_tradeable(BookUpdate &bu) {return true;}

void Signal::insert_book_update(BookUpdate &bu)
{
    if(q5.empty())
    {
        q5.push_back(bu);
        total5 += bu.get_price();
        //std::cout << "Price = " << bu.get_price() << std::endl;
    }
    else
    {
        if (bu.get_epoch_time() - q5.front().get_epoch_time() > 300)
        {
            total5 -= q5.front().get_price();
            q5.pop_front();
        }
        q5.push_back((bu));
        total5 += bu.get_price();
        //std::cout << "Price = " << bu.get_price() << std::endl;
    }
    if(q20.empty())
    {
        q20.push_back(bu);
        total20 += bu.get_price();
    }
    else
    {
        if(bu.get_epoch_time() - q20.front().get_epoch_time() > 1200)
        {
            total20 -= q20.front().get_price();
            q20.pop_front();
        }
        q20.push_back((bu));
        total20 += bu.get_price();
    }
};
double Signal::get_5min_moving_average()
{
    //std::cout << (round(total5/q5.size() * 100)/100) << std::endl;
    return ((total5/q5.size() * 100)/100);
}
double Signal::get_20min_moving_average()
{
    //std::cout << (round(total20/q20.size() * 100)/100) << std::endl;
    return ((total20/q20.size() * 100)/100);
}
bool Signal::go_long()
{
    if( total20 * 1.0 / q20.size() < total5 * 1.0 / q5.size() && firstBuy)
    {
        firstBuy = false;
        firstSell = true;
        return true;
    }
    return false;
}
bool Signal::go_short()
{
    if( total20 * 1.0 / q20.size() > total5 * 1.0 / q5.size() && firstSell)
    {
        firstBuy = true;
        firstSell = false;
        return true;
    }
    return false;
}


//Execution
bool Execution::insert_order(BookUpdate bu)
{
    e.setSide(bu.get_is_buy());
    e.setPrice(bu.get_price());
    e.setQuantity(bu.get_quantity());
    e.setVenue(bu.get_venue());
    e.setType(ordertype::MARKET);
    e.setSymbol(bu.get_symbol());
    e.setOrderID(order_id++);
};
bool Execution::is_tradeable() {return tradeable;}
void Execution::set_tradeable(bool is_tradable){tradeable=is_tradable;};
Order & Execution::get_order() {return e;}


//TradingStrategy

//helper function to act according to what the strategy says - go long, go short or do nothing
bool TradingStrategy::isWorking()
{
    if(is_working)
        return true;
    else
        return false;
}
bool TradingStrategy::process_book_update(BookUpdate &bu)
{


    signal.insert_book_update(bu);
    if(!is_working)
        return false;

    if (signal.is_tradeable(bu))
    {
        if(signal.go_long())
        {
            if(bu.get_is_buy())
            {
                execution.insert_order(bu);
                execution.set_tradeable(true);
                pnl = pnl - bu.get_price() * bu.get_quantity();
                //std::cout << "Signal PNL is: " << pnl << std::endl;
                date.push_back(bu.get_epoch_time());
                islong.push_back(1);
                myfile << "Bought at time: " << bu.get_epoch_time() << "\t" << "PNL at this time is: " << pnl << "\n";
                return process_execution();
            }

        }
        if(signal.go_short())
        {
            if(!bu.get_is_buy())
            {
                execution.insert_order(bu);
                execution.set_tradeable(true);
                pnl = pnl + bu.get_price() * bu.get_quantity();
                //std::cout << "Signal PNL is: " << pnl << std::endl;
                date.push_back(bu.get_epoch_time());
                islong.push_back(-1);
                myfile << "Sold at time: " << bu.get_epoch_time() << "\t" << "PNL at this time is: " << pnl << "\n";
                return process_execution();
            }
        }

    }
    return false;

}

//extract each bookupdates from the ring
bool TradingStrategy::process_book_update_from_ring(){
    if(!is_working)
        return false;
    while(!bookbuilder_to_strategy.empty())
    {
        BookUpdate &bu = bookbuilder_to_strategy.front();
        bookbuilder_to_strategy.pop();
        process_book_update(bu);
    }
    return true;
}

bool TradingStrategy::process_amendment(int quantity) {
    if(!is_working)
        return false;

    oldquant.push(execution.get_order().getQuantity());
    execution.set_tradeable(true);
    execution.get_order().setAmend();
    execution.get_order().setQuantity(quantity);
    return process_execution();

}

//send it to ordermanager
bool TradingStrategy::process_execution() {
    if(!is_working)
        return false;
    Order order;
    if (execution.is_tradeable()) {
        order.setType(execution.get_order().getOrderType());
        order.setVenue(execution.get_order().getVenue());
        order.setQuantity(execution.get_order().getQuantity());
        order.setPrice(execution.get_order().getPrice());
        order.setOrderID(execution.get_order().getID());
        order.setSymbol(execution.get_order().getSymbol());
        order.setSide(execution.get_order().isBuy());
        if(execution.get_order().getAmend()){
            order.setAmend();
        }

        execution.set_tradeable(false);
        strategy_to_ordermanager.push(order);
    }
    return true;
}


bool TradingStrategy::process_market_response()
{
    while(!ordermanager_to_strategy.empty())
    {
        ExecutionOrder &order = ordermanager_to_strategy.front();
        ordermanager_to_strategy.pop();
        int position = (order.isBuy() ? order.getPrice() * order.getQuantity() : -order.getPrice() *
                                                                                 order.getQuantity());
        if (order.getState() == orderstate::ACKNOWLEDGED)
        {

        }
        else if (order.getState() == orderstate::REJECTED)
        {
            number_of_rejections++;
        }
        else if (order.getState() == orderstate::FILLED)
        {
            //use of flag to distinguish between long and short positions
            int flag;
            if (order.isBuy())
                flag = 1;
            else
                flag = -1;
            if (order.getAmend())
            {
                positions[order.getSymbol()] = positions[order.getSymbol()] - (flag) * (oldquant.top()) + position;
            }
            else
                positions[order.getSymbol()] += position;
            number_of_fills++;

        }
    }
    return true;
}

int TradingStrategy::get_position(std::string symbol)
{

    auto got = positions.find(symbol);
    if(got == positions.end())
    {
        return 0;
    }
    else
        return got->second;
}

unsigned int TradingStrategy::get_number_of_rejections()
{
    return number_of_rejections;
}

unsigned int TradingStrategy::get_number_of_fills()
{
    return number_of_fills;
}

void TradingStrategy::reset_position()
{
    positions.clear();
}
long long  TradingStrategy::get_pnl()
{
    return (long long)pnl;
}

bool TradingStrategy::go_long()
{
    return signal.go_long();
}

bool TradingStrategy::go_short()
{
    return signal.go_short();
}

double TradingStrategy::get_5min_moving_average()
{
    return signal.get_5min_moving_average();
}

double TradingStrategy::get_20min_moving_average()
{
    return signal.get_20min_moving_average();
}
void TradingStrategy::start()
{
    is_working=true;
    myfile.open("/home/vinchhi/Documents/untitled/ieorclassproject9/TradeTimings.txt");
}
void TradingStrategy::stop()
{
    myfile.close();
    positions.clear();
    is_working=false;
}
