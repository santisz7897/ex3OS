//
// Created by Santiago Szterenberg on 01/06/2022.
//

#ifndef EX3_COEDITOR_H
#define EX3_COEDITOR_H

#include <string>
#include "Buffer.h"

class CoEditor {
public:
    Buffer* dispatcherBuffer;
    Buffer* screenBuffer;
    CoEditor(Buffer* dispatcher, Buffer* screenManager){
        this->dispatcherBuffer = dispatcher;
        this->screenBuffer = screenManager;
    }

    std::string extractFromDispatcher(){
        return this->dispatcherBuffer->remove();
    }

    void insertToScreenBuffer(std::string article){
        this->screenBuffer->insert(article);
    }
};


#endif //EX3_COEDITOR_H
