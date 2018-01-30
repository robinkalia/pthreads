
#include <iostream>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>

#ifndef PRODUCER_CONSUMER_BUFF_HPP
#define PRODUCER_CONSUMER_BUFF_HPP

class ProducerConsumerBuff {
public:
    static const int32_t MAX_SLOT_SIZE = 1000;

    void* buffer[MAX_SLOT_SIZE];
    sem_t freeSlot;
    sem_t usedSlot;
    pthread_mutex_t lock;
    int32_t nextInputSlot;
    int32_t nextOutputSlot;

    ProducerConsumerBuff() {
        this->init();    
    }

    ~ProducerConsumerBuff() {
        this->free();
    }
    
    void free() {
        pthread_mutex_destroy(&lock);
        sem_destroy(&freeSlot);
        sem_destroy(&usedSlot);
    }
    
    void init() {
        pthread_mutex_init(&lock, nullptr);
        sem_init(&freeSlot, 0, MAX_SLOT_SIZE);
        sem_init(&usedSlot, 0, 0);
        this->nextInputSlot = 0;
        this->nextOutputSlot = 0;
    }
};



#endif // PRODUCER_CONSUMER_BUFF_HPP