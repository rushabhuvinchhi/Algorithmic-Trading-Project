include_directories(${gtest_SOURCE_DIR}/include $gtest_SOURCE_DIR)


add_executable(RunTests MDReadertests.cpp TradingSignalsTests.cpp OrderTest.cpp AppBaseTest.cpp BookUpdateTests.cpp PriceUpdateTest.cpp MarketSimulatorTest.cpp OrderManagerTests.cpp MyOrderBookTests.cpp)
target_link_libraries(RunTests /home/vinchhi/Documents/untitled/ieorclassproject9/MDReader.cpp)
target_link_libraries(RunTests /home/vinchhi/Documents/untitled/ieorclassproject9/PriceUpdate.cpp)
target_link_libraries(RunTests /home/vinchhi/Documents/untitled/ieorclassproject9/TradingStrategy.cpp)
target_link_libraries(RunTests /home/vinchhi/Documents/untitled/ieorclassproject9/BookUpdate.cpp)
target_link_libraries(RunTests /home/vinchhi/Documents/untitled/ieorclassproject9/Order.cpp)
target_link_libraries(RunTests /home/vinchhi/Documents/untitled/ieorclassproject9/OrderManager.cpp)
target_link_libraries(RunTests /home/vinchhi/Documents/untitled/ieorclassproject9/AppBase.cpp)
target_link_libraries(RunTests /home/vinchhi/Documents/untitled/ieorclassproject9/MarketSimulator.cpp)
target_link_libraries(RunTests /home/vinchhi/Documents/untitled/ieorclassproject9/MyOrderBook.cpp)
target_link_libraries(RunTests gtest gtest_main )
