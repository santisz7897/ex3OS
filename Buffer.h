//
// Created by Santiago Szterenberg on 31/05/2022.
//

#ifndef EX3_BUFFER_H
#define EX3_BUFFER_H


class Buffer {
public:
    bool isStop;
    std::queue<std::string> queue;
    int size;

    Buffer(){

    }
    Buffer(std::queue<std::string> &queue) {
        this->queue = queue;
        this->isStop = false;
    }
    void insert(std::string item);
    std::string remove();
    void turnToUnbound();
    void setSize(int size);
    int getSize();
};


#endif //EX3_BUFFER_H
