//
// Created by Santiago Szterenberg on 31/05/2022.
//

#ifndef EX3_DISPATCHER_H
#define EX3_DISPATCHER_H
const int SPORT = 0;
const int WEATHER = 1;
const int NEWS = 2;
#include <cstring>
#include "Buffer.h"

class Dispatcher {
public:
    int numOfProducersStopped;
    int totalBuffers;
    int bufferIdx;
    bool* isStopped;

    Buffer** producerBuffers;
    Buffer** coEditorsBuffers;

    Dispatcher(Buffer* producerBuffers[], Buffer* coEditorBuffers[], int num, bool isStopped[]){
        this->producerBuffers = producerBuffers;
        this->coEditorsBuffers = coEditorBuffers;
        this->numOfProducersStopped = 0;
        this->totalBuffers = num;
        this->bufferIdx = 0;
        this->isStopped = isStopped;
    }

    std::string getNewsFromProducer(){
        this->bufferIdx %= this->totalBuffers;
        Buffer* buffer = this->producerBuffers[bufferIdx];
        std::string article = "NEXT";
        if (!this->isStopped[bufferIdx]){
            article = buffer->remove();
            if (article == "DONE"){
                this->isStopped[bufferIdx] = true;
                this->numOfProducersStopped++;
            }
        }
        this->bufferIdx++;
        return article;

    }

    int getBufferNumCoEditor(std::string article){
        if (article == "DONE"){
            return -1;
        }
        int len = article.size();
        char cpyArticle[len + 1];
        char* result;
        strcpy(cpyArticle, article.c_str());
        result = strtok(cpyArticle, " ");
        for (int i = 0; i < 2; ++i) {
            result = strtok(nullptr, " ");
        }
        if (!strcmp(result, "SPORTS"))
            return 0;
        else if (!strcmp(result, "WEATHER"))
            return 1;
        else
            return 2;
    }
};


#endif //EX3_DISPATCHER_H
