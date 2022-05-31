//
// Created by Santiago Szterenberg on 31/05/2022.
//
#include <string>
#include "Buffer.h"
#ifndef EX3_PRODUCER_H
#define EX3_PRODUCER_H


class Producer {
public:
    int amountOfArticlesLeft;
    int idx;
    Buffer buffer;
    int sportsCount;
    int weatherCount;
    int newsCount;

    explicit
    Producer(Buffer &buffer, int idx, int amountOfArticles){
        this->amountOfArticlesLeft = amountOfArticles;
        this->idx = idx;
        this->buffer = buffer;
        this->sportsCount = 0;
        this->weatherCount = 0;
        this->newsCount = 0;
    }

    void decreaseArticleCount(){
        this->amountOfArticlesLeft--;
    }

    int getIdx(){
        return this->idx;
    }
    void incNews(std::string type){
        if (type == "SPORTS")
            this->sportsCount++;
        else if (type == "NEWS")
            this->newsCount++;
        else
            this->weatherCount++;
    }

    std::string getNewsCount(std::string type){
        if (type == "SPORTS")
            return std::to_string(this->sportsCount);
        else if (type == "NEWS")
            return std::to_string(this->newsCount);
        else
            return std::to_string(this->weatherCount);
    }

    std::string defineTypeArticle(){
        int randomNum = rand() % 3;
        std::string articleType;
        if (!randomNum)
            articleType = "SPORTS";
        else if (randomNum == 1)
            articleType = "NEWS";
        else
            articleType = "WEATHER";
        this->incNews(articleType);
        return articleType;
    }

    std::string produceArticle(){
        this->decreaseArticleCount();
        std::string articleType = defineTypeArticle();
        std::string producerIdx = std::to_string(this->getIdx());
        std::string typeCount = this->getNewsCount(articleType);
        return "Producer " + producerIdx + " " + articleType + " " + typeCount;
    }
};


#endif //EX3_PRODUCER_H
