//
// Created by Santiago Szterenberg on 01/06/2022.
//

#ifndef EX3_SCREENMANAGER_H
#define EX3_SCREENMANAGER_H

#include <string>
#include <iostream>
#include "Buffer.h"

class ScreenManager {
public:
    Buffer* buffer;
    int doneCount;
    explicit ScreenManager(Buffer* buffer){
        this->buffer = buffer;
        this->doneCount = 0;
    }
    std::string extractFromBuffer(){
        std::string article = this->buffer->remove();
        if (article == "DONE"){
            this->doneCount++;
        }
        return article;
    }
    void printToScreen(std::string article){
        std::cout << article << std::endl;
    }
};


#endif //EX3_SCREENMANAGER_H
