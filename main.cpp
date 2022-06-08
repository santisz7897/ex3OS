#include <iostream>
#include <queue>
#include <fstream>
#include "Buffer.h"
#include "Producer.h"
#include "Dispatcher.h"
#include "CoEditor.h"
#include "ScreenManager.h"
#include <pthread.h>
#include <thread>



void* producerFunc(void *args){
    Producer producer = *((Producer*)args);
    int articlesLeft = producer.amountOfArticlesLeft;
    for (int i = articlesLeft; i > 0; --i) {
        std::string article = producer.produceArticle();
        producer.pushArticle(article);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    producer.buffer->isStop = true;
    producer.pushArticle("DONE");
}

void* dispatcherFunc(void *args){
    Dispatcher dispatcher = *((Dispatcher*)args);
    while (dispatcher.numOfProducersStopped != dispatcher.totalBuffers){
        std::string article = dispatcher.getNewsFromProducer();
        if (article == "NEXT"){
            continue;
        }
        int num = dispatcher.getBufferNumCoEditor(article);
        if (article != "DONE"){
            dispatcher.coEditorsBuffers[num]->insert(article);
        }
    }
    for (int i = 0; i < 3; ++i) {
        dispatcher.coEditorsBuffers[i]->insert("DONE");
    }
    return ((void *) nullptr);
}

void* coEditorFunc(void *args){
    CoEditor coEditor = *((CoEditor*)args);
    while (true){
        std::string article = coEditor.extractFromDispatcher();
        if (article == "DONE"){
            coEditor.insertToScreenBuffer("DONE");
            return ((void *) nullptr);
        }
        coEditor.insertToScreenBuffer(article);

    }
}

void* screenManagerFunc(void *args){
    ScreenManager screenManager = *((ScreenManager*)args);
    while (screenManager.doneCount != 3){
        std::string article = screenManager.extractFromBuffer();
        if (article != "DONE")
            screenManager.printToScreen(article);
    }
    screenManager.printToScreen("DONE");
    return ((void *) nullptr);
}

int main(int argc, char *argv[]) {
    // read from config file
    char* configName = argv[1];
    std::ifstream config;
    config.open(configName);
    std::vector<int> sizeOfEveryBuffer;
    std::vector<int> amountOfArticles;
    int sizeOfScreenBuffer;
    // string to hold the input
    std::string line;
    int numOfProducers = 0;
    if ( config.is_open() ) {
        while ( config ) {
            std::getline(config, line);
            sizeOfScreenBuffer = std::stoi(line);
            std::getline(config, line);
            // if this is the producer number
            if (config)
                numOfProducers++;
                // else this is the last line in file
            else
                break;
            amountOfArticles.push_back(std::stoi(line));
            std::getline(config, line);
            sizeOfEveryBuffer.push_back(std::stoi(line));
            std::getline(config, line);
        }
    }

    const int SIZE = numOfProducers;
    sem_t producerSemaphore[SIZE];
    sem_t empty;
    pthread_mutex_t mutex;
    Buffer* buffers[SIZE];
    Buffer* coEditorBuffers[3];
    Buffer* screenManagerBuffer;
    Producer* producers[SIZE];
    Dispatcher* dispatcher;
    CoEditor* coEditors[3];
    ScreenManager* screenManager;
    // number of articles each producer will produce
    // size of every producer buffer
    // init producers and their buffers
    for (int i = 0; i < SIZE; ++i) {
        buffers[i] = new Buffer();
        buffers[i]->setSize(sizeOfEveryBuffer[i]);
        producers[i] = new Producer(buffers[i], i, amountOfArticles[i]);
    }
    // init buffer of screenManager
    screenManagerBuffer = new Buffer();
    screenManagerBuffer->setSize(sizeOfScreenBuffer);
    screenManager = new ScreenManager(screenManagerBuffer);
    // init coEditors and their buffers
    for (int i = 0; i < 3; ++i) {
        coEditorBuffers[i] = new Buffer();
        coEditorBuffers[i]->turnToUnbound();
        coEditors[i] = new CoEditor(coEditorBuffers[i], screenManagerBuffer);
    }
    bool allFalse[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        allFalse[i] = false;
    }
    dispatcher = new Dispatcher(buffers, coEditorBuffers, SIZE, allFalse);

    pthread_t producersThread[SIZE];
    pthread_t dispatcherT;
    pthread_t coEditorThread[3];
    pthread_t screenManagerThread;
    for (int i = 0; i < SIZE; ++i) {
        pthread_create(&producersThread[i], nullptr, producerFunc, (void *) producers[i]);
    }
    pthread_create(&dispatcherT, nullptr, dispatcherFunc, (void *) dispatcher);
    for (int i = 0; i < 3; ++i) {
        pthread_create(&coEditorThread[i], nullptr, coEditorFunc, (void *) coEditors[i]);
    }
    pthread_create(&screenManagerThread, nullptr, screenManagerFunc, (void *) screenManager);

    pthread_join(screenManagerThread, nullptr);
    return 0;
}


