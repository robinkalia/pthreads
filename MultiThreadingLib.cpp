//
//  basic_multithreading.cpp
//  basic_multithreading
//
//  Created by Robin Kalia on 1/28/18.
//

#include <iostream>
#include <stdint.h>
#include <pthread.h>

#include <chrono>
#include <thread>

#include "MultiThreadingLib.hpp"


void* MultiThreadingLib::printThreadMessage(void* threadIndex)
{
    int *threadID = (int *)threadIndex;
    for (int32_t i=0; i<NUM_PRINTS; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(SLEEPING_INTERVAL_SECS));
        std::cout << "Hello from thread " << *threadID << ": " << i+1 << std::endl;
    }
    
    return nullptr;
}

void MultiThreadingLib::printMessages(int32_t numThreads)
{
    pthread_t threadID[numThreads];
    void *threadResult[numThreads];
    
    for (int32_t i=0; i<numThreads; i++) {
        int32_t val = i+1;
        pthread_create(&threadID[val-1], nullptr, printThreadMessage, &val);
    }
    
    for (int32_t i=0; i<numThreads; i++)
        pthread_join(threadID[i], &threadResult[i]);
}

void* MultiThreadingLib::reduceNumber(void* number)
{
    int32_t targetNum = *((int *)number);
    
    while (targetNum > 0) {
        pthread_mutex_lock(&mutex);
        --targetNum;
        pthread_mutex_unlock(&mutex);
    }
    
    *((int *)number) = 0;
    
    std::cout << "Signaling the waiting thread with final value of Number = " << number << std::endl;
    pthread_cond_signal(&cv);
    
    return nullptr;
}

void MultiThreadingLib::testConditionVariables(int32_t number)
{
    pthread_cond_init(&cv, nullptr);
    pthread_mutex_init(&mutex, nullptr);
    
    pthread_t threadID;
    void* threadResult;
    
    std::cout << "Initial Value of Number = " << number << std::endl;
    
    pthread_create(&threadID, nullptr, reduceNumber, &number);
    
    pthread_mutex_lock(&mutex);
    while (number != 0)
        pthread_cond_wait(&cv, &mutex);
    pthread_mutex_unlock(&mutex);
    
    std::cout << "Final Value of Number = " << number << std::endl;
    
    pthread_join(threadID, &threadResult);
    
    pthread_cond_destroy(&cv);
    pthread_mutex_destroy(&mutex);
}


void MultiThreadingLib::produce(void *value) 
{
    sem_wait(&pcBuffer.freeSlot);
    pthread_mutex_lock(&pcBuffer.lock);
    pcBuffer.buffer[pcBuffer.nextInputSlot++] = value;
    if (pcBuffer.nextInputSlot == ProducerConsumerBuff::MAX_SLOT_SIZE)      pcBuffer.nextInputSlot = 0;
    pthread_mutex_unlock(&pcBuffer.lock);
    sem_post(&pcBuffer.usedSlot);
}

void* MultiThreadingLib::consume() 
{
    void* value = nullptr;
    sem_wait(&pcBuffer.usedSlot);
    pthread_mutex_lock(&pcBuffer.lock);
    value = pcBuffer.buffer[pcBuffer.nextOutputSlot++];
    if (pcBuffer.nextOutputSlot == ProducerConsumerBuff::MAX_SLOT_SIZE)   pcBuffer.nextOutputSlot = 0;
    pthread_mutex_unlock(&pcBuffer.lock);
    sem_post(&pcBuffer.freeSlot);

    return value;
}

void MultiThreadingLib::testProducerConsumerProblem() 
{
    pcBuffer.init();

    pcBuffer.free();
}


