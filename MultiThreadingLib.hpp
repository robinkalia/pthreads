//
//  basic_multithreading.hpp
//  basic_multithreading
//
//  Created by Robin Kalia on 1/28/18.
//

#ifndef MULTI_THREADING_LIB_HPP
#define MULTI_THREADING_LIB_HPP

#include "ProducerConsumerBuff.hpp"

class MultiThreadingLib {

private:
    static const uint8_t NUM_PRINTS = 10;
    static void* printThreadMessage(void* threadIndex);
    static void* reduceNumber(void* number);
    ProducerConsumerBuff pcBuffer;

    void produce(void *value);
    void* consume();

public:
    MultiThreadingLib() {
    }
    
    ~MultiThreadingLib() {
    }
    
    void printMessages(int32_t numThreads);
    void testConditionVariables(int32_t number);
    void testProducerConsumerProblem();
    
    static pthread_cond_t cv;
    static pthread_mutex_t mutex;
    static const uint8_t SLEEPING_INTERVAL_SECS = 1;
};


#endif /* MULTI_THREADING_LIB_HPP */
