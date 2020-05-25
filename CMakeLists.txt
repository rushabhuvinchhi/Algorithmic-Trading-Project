cmake_minimum_required(VERSION 3.12)
project(ieorclassproject9)

set(CMAKE_CXX_STANDARD 11)
find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

link_libraries( -lboost_system -lboost_thread -lboost_regex -lboost_filesystem -lboost_random -lboost_date_time -lboost_log -lboost_program_options -lboost_signals )
set(SOURCE_FILES main.cpp MDReader.h MDReader.cpp OrderManager.h OrderManager.cpp MarketSimulator.h MarketSimulator.cpp Order.h Order.cpp AppBase.h AppBase.cpp BookUpdate.h BookUpdate.cpp MyOrderBook.h MyOrderBook.cpp PriceUpdate.h PriceUpdate.cpp TradingStrategy.h TradingStrategy.cpp)

add_executable(ieorclassproject9 ${SOURCE_FILES})
#add_executable(ieorclassproject9 main.cpp AppBase.cpp AppBase.h MDParser/MDReader.h MDParser/MDReader.cpp PriceUpdate.h PriceUpdate.cpp MyOrderBook.cpp MyOrderBook.h BookUpdate.h BookUpdate.cpp Order.h Order.cpp TradingStrategy.h TradingStrategy.cpp)


add_subdirectory(ProjectTests)


target_link_libraries(ieorclassproject9 ${Boost_LIBRARIES} )