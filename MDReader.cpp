//
// Created by vinchhi on 12/4/19.
//
#include "MDReader.h"

using namespace boost::posix_time;

using namespace std;

std::vector<PriceUpdate> MDReader::getData()
{
    unsigned int current_number_of_line = 0;
    std::ifstream file(fileName);

    if (!file)
    {
        cerr << "File could not be opened!\n"; // Report error
        cerr << "Error code: " << strerror(errno); // Get some info as to why
        exit(1);
    }

    std::vector<PriceUpdate> dataList;

    std::string line = "";
    // Iterate through each line and split the content using delimeter
    bool is_header_handled = false;

    unsigned int order_id = 0;

    while (getline(file, line))
    {
        if (is_header and !is_header_handled)
        {
            is_header_handled = true;
            continue;
        }
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        std::vector<std::string> vec;
        boost::algorithm::split(vec, line, boost::is_any_of(delimeter));

        std::string ts(vec[3]);
        ptime t(time_from_string(ts));
        ptime start(boost::gregorian::date(1970, 1, 1));
        time_duration dur = t - start;
        time_t epoch = dur.total_seconds();

        PriceUpdate pu1(static_cast<action_t>(0), std::stof(vec[4]), 100000, "GAIN", true, vec[2].c_str(),
                        (long long ) epoch, order_id++);
        PriceUpdate pu2(static_cast<action_t>(0), std::stof(vec[5]), 100000, "GAIN", false, vec[2].c_str(),
                        (long long) epoch, order_id++);
        dataList.push_back(pu1);
        dataList.push_back(pu2);

        if (number_of_line != 0 and current_number_of_line++ >= number_of_line)
        {
            break;
        }

    }
    // Close the File
    file.close();

    return dataList;
}