//
//  main.cpp
//  basic_multithreading
//
//  Created by Robin Kalia on 1/28/18.
//

#include "MultiThreadingLib.hpp"


int32_t main(int32_t argc, char* argv[])
{
    MultiThreadingLib mtl;
    int32_t numThreads;
    std::cout << "******* Testing Multiple Printout of Messages *******\n\n";
    std::cout << "\nEnter the number of threads: ";
    std::cin >> numThreads;
    
    mtl.printMessages(numThreads);
    
    std::cout << "******* Testing Condition Variables for reducing the value of a number *******\n\n";
    int32_t cvNum;
    std::cout << "\nEnter the number to be reduced: ";
    std::cin >> cvNum;
    
    mtl.testConditionVariables(cvNum);
    
    return 0;
}
