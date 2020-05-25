//
// Created by vinchhi on 12/3/19.
//

#include "PriceUpdate.h"

price_t PriceUpdate::get_price() const {return price;}
quantity_t PriceUpdate::get_quantity() const {return quantity;}
order_id_t PriceUpdate::get_order_id() const {return order_id;}
const char * PriceUpdate::get_venue() const {return venue;}
bool PriceUpdate::get_is_buy() const {return is_buy;}
const char * PriceUpdate::get_symbol() const {return symbol;}
const action_t PriceUpdate::get_action() const {return action;}
long long PriceUpdate::get_epoch_time() const {return epoch_time;}
