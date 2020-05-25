//
// Created by vinchhi on 12/3/19.
//

#include "BookUpdate.h"

price_t BookUpdate::get_price() const {return price;}
quantity_t BookUpdate::get_quantity() const {return quantity;}
level_t BookUpdate::get_level() const {return level;}
const char * BookUpdate::get_venue() const {return venue;}
bool BookUpdate::get_is_buy() const {return is_buy;}
const char * BookUpdate::get_symbol() const {return symbol;}
long long BookUpdate::get_epoch_time() const {return epoch_time;}