#include "Circular buffer.h"

int main() {
    CircularBuffer<int> buffer(8);

    for (int i = 0; i < 5; ++i) {
        buffer.push_back(i+1);
    }

    std::cout<<"Buffer s: "<<buffer.size()<<", c: "<<buffer.capacity()<<" is:\n";
    for (int i = 0; i < buffer.size(); ++i) {
        std::cout<<buffer[i]<<"\n";
    }
    std::cout<<"\n";

    auto it2 = buffer.begin()+2;
    buffer.insert(it2, 999);
    std::cout<<"IT2: "<<"Buffer s: "<<buffer.size()<<", c: "<<buffer.capacity()<<" is:\n";;
    for (int i = 0; i < buffer.size(); ++i) {
        std::cout<<buffer[i]<<"\n";
    }
    std::cout<<"\n";

    auto it3 = buffer.begin()+3;
    buffer.insert(it3, 111);
    std::cout<<"IT3: "<<"Buffer s: "<<buffer.size()<<", c: "<<buffer.capacity()<<" is:\n"; ;
    for (int i = 0; i < buffer.size(); ++i) {
        std::cout<<buffer[i]<<"\n";
    }
    std::cout<<"\n";

    it3-it2;
    buffer.insert(it2, 333);
    std::cout<<"IT2: "<<"Buffer s: "<<buffer.size()<<", c: "<<buffer.capacity()<<" is:\n";;
    for (int i = 0; i < buffer.size(); ++i) {
        std::cout<<buffer[i]<<"\n";
    }
    std::cout<<"\n";


    buffer.insert(it3, 333);
    std::cout<<"IT3: "<<"Buffer s: "<<buffer.size()<<", c: "<<buffer.capacity()<<" is:\n";;
    for (int i = 0; i < buffer.size(); ++i) {
        std::cout<<buffer[i]<<"\n";
    }
    std::cout<<"\n";


    return 0;
}