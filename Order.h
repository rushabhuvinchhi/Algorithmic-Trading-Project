//
// Created by vinchhi on 12/3/19.
//

#ifndef IEORCLASSPROJECT9_ORDER_H
#define IEORCLASSPROJECT9_ORDER_H
#include <string.h>
enum ordertype {LIMIT, MARKET};
enum orderstate {OPEN, ACKNOWLEDGED, FILLED, CANCELLED, REJECTED};


class Order{
private:
    unsigned int timestamp;
    bool is_buy;
    unsigned int id;
    double price;
    unsigned int quantity;
    char venue[20];
    char symbol[20];
    ordertype type;
    bool amend;
public:
    Order(unsigned int timestamp_=0,
          bool is_buy_=true,
          unsigned int id_=0,
          double price_=0,
          unsigned int quantity_=0,
          const char * venue_="",
          const char * symbol_="",
          ordertype type_=ordertype::MARKET,
          bool amend_ = 0)
    {
        is_buy=is_buy_;
        timestamp=timestamp_;
        id=id_;
        price=price_;
        quantity=quantity_;
        strcpy(venue,venue_);
        type=type_;
        strcpy(symbol,symbol_);
        amend = amend_;
    }
    Order&operator = (const Order &o)
    {
        is_buy = o.isBuy();
        timestamp = o.getTimeStamp();
        id = o.getID();
        price = o.getPrice();
        quantity = o.getQuantity();
        strcpy(venue,o.getVenue());
        strcpy(symbol,o.getSymbol());
        type = o.getOrderType();
        amend = o.getAmend();
    }
    const char * getVenue() const;
    const char * getSymbol() const;
    unsigned int getID() const;
    ordertype getOrderType() const;
    void setType(ordertype e);
    bool is_valid() const;
    unsigned int getQuantity() const;
    double getPrice() const;
    void setVenue(const char * venue_);
    void setQuantity(unsigned int quantity_);
    void setSymbol(const char * symbol_);
    void setPrice(double price_);
    void setSide(bool is_buy_);
    void setOrderID(unsigned int id_);
    void setTimeStamp(unsigned int timestamp_);
    void setAmend();
    bool getAmend() const;
    unsigned int getTimeStamp() const;
    bool isBuy() const;

};


class ExecutionOrder : public Order
{
private:
    orderstate state;
    unsigned int execution_id;
public:
    ExecutionOrder():Order(),state(orderstate::OPEN) {}
    ExecutionOrder(const Order &o):Order(o.getTimeStamp(),
                                         o.isBuy(),o.getID(),o.getPrice(),o.getQuantity(),
                                         o.getVenue(),o.getSymbol(),o.getOrderType()){};
    orderstate getState() const {return state;};
    void setState(orderstate e){state=e;}
    void setExecutionID(unsigned int id){execution_id=id;}
    unsigned int getExecutionID() const { return execution_id;}
};

#endif //IEORCLASSPROJECT9_ORDER_H
