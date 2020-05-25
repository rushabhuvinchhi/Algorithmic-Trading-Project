//
// Created by vinchhi on 12/4/19.
//

#ifndef IEORCLASSPROJECT9_MDREADER_H
#define IEORCLASSPROJECT9_MDREADER_H
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "PriceUpdate.h"

class MDReader
{
    const std::string fileName;
    const std::string delimeter;
    const unsigned int number_of_line;
    const bool is_header;


public:
    MDReader(std::string filename,
             std::string delm = ",",
             unsigned int number_of_line_ = 10,
             bool is_header_ = true) :
            fileName(filename),
            delimeter(delm),
            number_of_line(number_of_line_),
            is_header(is_header_)
    { }

    std::vector<PriceUpdate> getData();

};
#endif //IEORCLASSPROJECT9_MDREADER_H
