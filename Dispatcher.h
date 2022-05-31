//
// Created by Santiago Szterenberg on 31/05/2022.
//

#ifndef EX3_DISPATCHER_H
#define EX3_DISPATCHER_H
const int SPORT = 0;
const int WEATHER = 1;
const int NEWS = 2;
#include <string>
#include "Buffer.h"

class Dispatcher {
public:
    Buffer producerBuffers[];
    Buffer coEditorsBuffers[];
    int numOfProducersLeft;
    int totalBuffers;
    int bufferIdx;
    Dispatcher(Buffer producerBuffers[], Buffer coEditorBuffers[], int num){
        this->producerBuffers = producerBuffers;
        this->coEditorsBuffers = coEditorBuffers;
        this->numOfProducersLeft = num;
        this->totalBuffers = num;
        this->bufferIdx = 0;
    }

    std::string getNewsFromProducer(){
        this->bufferIdx++;
        this->bufferIdx %= this->totalBuffers;
        Buffer buffer = this->producerBuffers[bufferIdx];
        return buffer.remove();
    }

    void insertToCoEditorBuffer(std::string article){
        printf("hry");
    }

};


#endif //EX3_DISPATCHER_H
