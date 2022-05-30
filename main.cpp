#include <iostream>
#include <queue>

class BoundedQ{
public:
    explicit
    BoundedQ(int size) {
        std::queue<std::string> hey;
        this->isStop = false;
        this->queue = hey;
        this->size = size;
    }
    bool isStop;
    std::queue<std::string> queue;
    int size;
    void pushItem(std::string item){
        this->queue.push(item);
    }
};



int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

