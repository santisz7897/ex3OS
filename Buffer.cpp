//
// Created by Santiago Szterenberg on 31/05/2022.
//
#include <iostream>
#include <queue>
#include "Buffer.h"


void Buffer::insert(std::string item) {
    this->queue.push(item);
}

int Buffer::getSize() {
    return this->size;
}
std::string Buffer::remove(){
    std::string removedItem = this->queue.front();
    this->queue.pop();
    return removedItem;
}

void Buffer::turnToUnbound(){
    this->size = INT_MAX;
}

void Buffer::setSize(int size){
    this->size = size;
}

