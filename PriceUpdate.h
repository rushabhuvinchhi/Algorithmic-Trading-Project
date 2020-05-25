//
// Created by vinchhi on 12/3/19.
//

#ifndef IEORCLASSPROJECT9_PRICEUPDATE_H
#define IEORCLASSPROJECT9_PRICEUPDATE_H
#include <string.h>

typedef double price_t;
typedef unsigned int quantity_t;
typedef unsigned int order_id_t;
typedef enum  {NEW,MODIFY,REMOVE} action_t;


class PriceUpdate {
private:
    order_id_t order_id;
    price_t price;
    quantity_t quantity;
    char venue[20];
    char symbol[20];
    bool is_buy;
    long long epoch_time;
    action_t action;

public:
    PriceUpdate(action_t action_,
                price_t price_,
                quantity_t quantity_,
                const char *venue_,
                bool is_buy_,
                const char *symbol_,
                long long epoch_time_,
                order_id_t order_id_):
            action(action_),
            price(price_),
            quantity(quantity_),
            is_buy(is_buy_),
            epoch_time(epoch_time_),
            order_id(order_id_)
    {
        strcpy(venue,venue_);
        strcpy(symbol,symbol_);
    }
    price_t get_price() const;
    quantity_t get_quantity() const ;
    order_id_t get_order_id() const;
    const char * get_venue() const;
    bool get_is_buy() const;
    const char * get_symbol() const;
    const action_t get_action() const;
    long long get_epoch_time() const;
};

#endif //IEORCLASSPROJECT9_PRICEUPDATE_H
