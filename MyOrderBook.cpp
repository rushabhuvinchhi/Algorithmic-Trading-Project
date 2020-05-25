//
// Created by vinchhi on 12/3/19.
//

#include "MyOrderBook.h"



void MyOrderBook::start(){

    MDReader reader("/home/vinchhi/Documents/ieorclassproject7/EUR_USD_Week1.csv",",",50);

    // Get the data from CSV File
    dataList = reader.getData();

    // Handle each price update
    for(const PriceUpdate &pu : dataList)
    {
        handle_price_update(pu);
    }

}

void MyOrderBook::stop()
{}

void MyOrderBook::handle_price_update(const PriceUpdate &pu)
{
    std::cout << pu.get_epoch_time() << std::endl;
    switch(pu.get_action())
    {
        case action_t::NEW:

            if(pu.get_is_buy())
            {
                //Insert into the ask map
                asks.insert({pu.get_price(),pu});

                //Insert into the ask hash
                askhash[pu.get_order_id()] = asks.find(pu.get_price());

                //create a book update and send it to strategy
                BookUpdate bu(pu);
                bookbuilder_to_strategy.push(bu);

            }
            else
            {
                //Insert into bids map
                bids.insert({pu.get_price(),pu});

                //Insert into bids hash
                bidshash[pu.get_order_id()] = bids.find(pu.get_price());

                //create a book update and send it to strategy
                BookUpdate bu(pu);
                bookbuilder_to_strategy.push(bu);
            }

            break;
        case action_t::MODIFY:
            if(pu.get_is_buy())
            {
                asks.insert({pu.get_price(),pu});
                askhash[pu.get_order_id()] = asks.find(pu.get_price());
                BookUpdate bu(pu);
                bookbuilder_to_strategy.push(bu);
            }
            else
            {
                bids.insert({pu.get_price(),pu});
                bidshash[pu.get_order_id()] = bids.find(pu.get_price());
                BookUpdate bu(pu);
                bookbuilder_to_strategy.push(bu);
            }
            break;
        case action_t::REMOVE:
            if(pu.get_is_buy())
            {
                if(!asks.empty())
                {
                    asks.erase(askhash[pu.get_order_id()]);
                    askhash.erase(pu.get_order_id());
                }
            }
            else
            {
                if (!bids.empty())
                {
                    bids.erase(bidshash[pu.get_order_id()]);
                    bidshash.erase(pu.get_order_id());
                }
            }
            break;
    }

}
bool MyOrderBook::is_empty() const{
    return bids.empty() and asks.empty();
}

void MyOrderBook::clear()
{
    bids.clear();
    asks.clear();
}

std::ostream& operator<<(std::ostream &os, const MyOrderBook &book) {
    if (book.is_empty())
    {
        os << "ORDER BOOK EMPTY";
        return os;
    }

    os << "ASKS" << std::endl;
    for(auto it = book.asks.begin();
        it!=book.asks.end();
        ++it)
    {
        os << it->first << "\t" << (it->second).get_quantity() << std::endl;
    }
    os << "BIDS" << std::endl;

    for(auto it = book.bids.begin();
        it!=book.bids.end();
        ++it)
    {
        os << it->first << "\t" << (it->second).get_quantity() << std::endl;
    }
    return os;
}



std::ostream& operator<<(std::ostream &os, const MyOrderBook::BidAsk &ba) {
    auto print = [&](const MyOrderBook::BidAsk::Entry &e, const std::string &text)
    {
        bool have_value = e.is_initialized();
        if(have_value)
        {
            auto value = e.get();
            os << value.second << text << "s @" << value.first;

        } else{
            os << "NO" << text;
        }
    };
    print(ba.bid, "bid");
    os << ", ";
    print(ba.ask, "ask");
    return os;
}

boost::optional<int> MyOrderBook::BidAsk::spread() const{
    boost::optional<int> result;

    //Only if initialised
    if(bid.is_initialized() and ask.is_initialized())
        result=ask.get().first - bid.get().first;

    return result;
}




MyOrderBook::BidAsk MyOrderBook::get_bid_ask()
{
    BidAsk result;
    auto best_bid = bids.begin();
    if(best_bid != bids.end() )
    {
        result.bid = std::make_pair(best_bid->first,
                                    (bidshash[(best_bid->second).get_order_id()]->second).get_quantity());
    }
    auto best_ask = asks.begin();
    if(best_ask != asks.end() )
        result.ask = std::make_pair(best_ask->first,
                                    (askhash[(best_ask->second).get_order_id()]->second).get_quantity());
    return result;
}
