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
    int numOfProducersStopped;
    int totalBuffers;
    int bufferIdx;

    Buffer** producerBuffers;
    Buffer** coEditorsBuffers;

    Dispatcher(Buffer* producerBuffers[], Buffer* coEditorBuffers[], int num){
        this->producerBuffers = producerBuffers;
        this->coEditorsBuffers = coEditorBuffers;
        this->numOfProducersStopped = 0;
        this->totalBuffers = num;
        this->bufferIdx = 0;
    }

    std::string getNewsFromProducer(){
        this->bufferIdx %= this->totalBuffers;
        Buffer* buffer = this->producerBuffers[bufferIdx];
        if (!canRemove(buffer)) {
            this->numOfProducersStopped++;
            return "DONE";
        }
        std::string article = buffer->remove();
        this->bufferIdx++;
        return article;
    }

    int getBufferNumCoEditor(std::string article){
        int len = article.size();
        char cpyArticle[len + 1];
        char* result;
        strcpy(cpyArticle, article.c_str());
        result = strtok(cpyArticle, " ");
        for (int i = 0; i < 2; ++i) {
            result = strtok(nullptr, " ");
        }
        std::cout << "Im entering someting" << std::endl;
        if (!strcmp(result, "SPORTS"))
            return 0;
        else if (!strcmp(result, "WEATHER"))
            return 1;
        else
            return 2;
    }
    bool canRemove(Buffer* buffer){
        std::string article = buffer->queue.front();
        if (article == "DONE")
            return false;
        return true;
    }
};


#endif //EX3_DISPATCHER_H
