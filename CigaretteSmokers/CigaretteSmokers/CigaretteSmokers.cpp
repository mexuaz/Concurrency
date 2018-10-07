#include "ingredients.h"
#include "supply_agent.h"
#include "smoker.h"

#include <iostream>
#include <string>
#include <array>
#include <thread>

using namespace std;

int main(int argc, char** argv) {

    std::string pr(argv[0]);
    pr.erase(0, pr.find_last_of('/')+1);

    cout << "Cigarette Smokers Problem " << endl
         << "Required at least C++17 "
         << "Your C++ version is " << __cplusplus << endl
         << "Implemented by Amir Mehrafsa (mehrafsa@live.com)" << endl
         << "Usage :" << endl
         << pr << endl;

    ingredients ings;

    supply_agent agent(&ings);

    array<smoker, 3> smokers {{
            {0, ingredients::infinit_t::tabacco, &ings},
            {1, ingredients::infinit_t::paper, &ings},
            {2, ingredients::infinit_t::matches, &ings}
            }};


    // Start threads
    array<thread, 4> threads {{
            {thread(agent)},
            {thread(smokers[0])},
            {thread(smokers[1])},
            {thread(smokers[2])}
                              }};



    // Wait for all threads to join
    for(auto& th : threads) {
        if(th.joinable()) {
            th.join();
        }
    }



    return 0;
}
