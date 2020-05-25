//
// Created by vinchhi on 12/3/19.
//

#ifndef IEORCLASSPROJECT9_BOOKUPDATE_H
#define IEORCLASSPROJECT9_BOOKUPDATE_H
#include <string.h>
#include "PriceUpdate.h"

typedef double price_t;
typedef unsigned int quantity_t;
typedef unsigned int level_t;



class BookUpdate {
private:
    level_t level;
    price_t price;
    quantity_t quantity;
    char venue[20];
    char symbol[20];
    bool is_buy;
    long long epoch_time;
public:
    BookUpdate(level_t level_,
               price_t price_,
               quantity_t quantity_,
               const char *venue_,
               bool is_buy_,
               const char *symbol_,
               long long epoch_time_):
            level(level_),
            price(price_),
            quantity(quantity_),
            is_buy(is_buy_),
            epoch_time(epoch_time_)
    {
        strcpy(venue,venue_);
        strcpy(symbol,symbol_);
    }
    BookUpdate(PriceUpdate pu)
    {
        level = 0;
        price = pu.get_price();
        quantity = pu.get_quantity();
        is_buy = pu.get_is_buy();
        strcpy(venue,pu.get_venue());
        strcpy(symbol,pu.get_symbol());
        epoch_time = pu.get_epoch_time();
    }
    price_t get_price() const;
    quantity_t get_quantity() const;
    level_t get_level() const ;
    const char * get_venue() const;
    bool get_is_buy() const;
    const char * get_symbol() const;
    long long  get_epoch_time() const;
};
#endif //IEORCLASSPROJECT9_BOOKUPDATE_H
