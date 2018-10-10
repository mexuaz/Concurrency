#include "deer.h"
#include "elve.h"
#include "santa.h"


#include <iostream>
#include <string>
#include <array>
#include <mutex>
#include <condition_variable>

#include <thread>

using namespace std;

int main(int /*argc*/, char** argv) {

    std::string pr(argv[0]);
    pr.erase(0, pr.find_last_of('/')+1);

    cout << "The Santa Claus Problem " << endl
         << "Required at least C++17 "
         << "Your C++ version is " << __cplusplus << endl
         << "Implemented by Amir Mehrafsa (mehrafsa@live.com)" << endl
         << "Usage :" << endl
         << pr << endl;


    mutex mt;
    condition_variable cv;

    std::array<deer, 9> deers {{{&mt, &cv},
                                {&mt, &cv},
                                {&mt, &cv},
                                {&mt, &cv},
                                {&mt, &cv},
                                {&mt, &cv},
                                {&mt, &cv},
                                {&mt, &cv},
                                {&mt, &cv}
                               }};


    std::array<elve, 10> elves {{{&mt, &cv},
                                {&mt, &cv},
                                {&mt, &cv},
                                {&mt, &cv},
                                {&mt, &cv},
                                {&mt, &cv},
                                {&mt, &cv},
                                {&mt, &cv},
                                {&mt, &cv},
                                {&mt, &cv}
                               }};



    santa Santa(&mt, &cv);



    // runing 20 concurrent threads
    array<thread, 20> ths{{
            {thread(Santa)},
            {thread(deers[0])},
            {thread(deers[1])},
            {thread(deers[2])},
            {thread(deers[3])},
            {thread(deers[4])},
            {thread(deers[5])},
            {thread(deers[6])},
            {thread(deers[7])},
            {thread(deers[8])},
            {thread(elves[0])},
            {thread(elves[1])},
            {thread(elves[2])},
            {thread(elves[3])},
            {thread(elves[4])},
            {thread(elves[5])},
            {thread(elves[6])},
            {thread(elves[7])},
            {thread(elves[8])},
            {thread(elves[9])}
                          }};



    for(auto& th : ths) {
        if(th.joinable()) {
            th.join();
        }
    }



    return 0;
}
