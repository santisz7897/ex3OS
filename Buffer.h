//
// Created by Santiago Szterenberg on 31/05/2022.
//

#ifndef EX3_BUFFER_H
#define EX3_BUFFER_H
#include <pthread.h>
#include <sys/semaphore.h>

class Buffer {
public:
    sem_t full;
    sem_t empty;
    pthread_mutex_t mutex;
    std::queue<std::string> queue;
    int size;

    Buffer() {
        std::queue<std::string> newQueue;
        this->queue = newQueue;
        pthread_mutex_init(&mutex, nullptr);
        int hi = sem_init(&full, 0, 0);
        std::cout <<hi << std::endl;
        std::cout << std::endl;
    }
    void insert(std::string item) {
        sem_wait(&this->empty);
        pthread_mutex_lock(&this->mutex);
        this->queue.push(item);
        pthread_mutex_unlock(&this->mutex);
        sem_post(&this->full);
    }

    int getSize() {
        return this->queue.size();
    }
    std::string remove(){
        sem_wait(&this->full);
        pthread_mutex_lock(&this->mutex);
        std::string removedItem = this->queue.front();
        this->queue.pop();
        pthread_mutex_unlock(&this->mutex);
        sem_post(&this->empty);
        return removedItem;
    }

    void turnToUnbound(){
        this->size = INT16_MAX;
        int hey = sem_init(&this->empty, 0, INT16_MAX);
        std::cout << hey << std::endl;
    }

    void setSize(int size){
        this->size = size;
        int hey = sem_init(&this->empty, 0, size);
        std::cout << hey << std::endl;
    }


};


#endif //EX3_BUFFER_H
