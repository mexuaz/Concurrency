#include "philosopher.h"

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

int main(int argc, char** argv) {

    std::string pr(argv[0]);
    pr.erase(0, pr.find_last_of('/')+1);

    cout << "Dining Philosophers Problem Naive Version (Deadlock possbile) " << endl
         << "Required at least C++11 "
         << "Your C++ version is " << __cplusplus << endl
         << "Implemented by Amir Mehrafsa (mehrafsa@live.com)" << endl
         << "Usage :" << endl
         << pr << " [amount of spaghetti in minutes(=1)]" << endl;

    // default duration of spaghetti bowl
    chrono::duration<size_t, nano> duration = 1min;
    if(argc > 1 ) {
        duration = chrono::minutes(atol(argv[1]));
    }


    spaghetti_bowl bowl(duration);

    array<fork, 5> frk {{{0}, {1}, {2}, {3}, {4}}};

    // Initialize philosophers
    vector<philosopher> phls;
    for(size_t i = 0; i < frk.size(); i++) {
        phls.push_back(philosopher(i, &frk[(i+1)%frk.size()], &frk[i], &bowl, i!=frk.size()-1?true:false));
    }

    // Start threads
    vector<thread> ths;
    for(const auto& p : phls) {
        ths.push_back(thread(p));
    }


    // Wait for all threads to join
    for(auto& th : ths) {
        if(th.joinable()) {
            th.join();
        }
    }

    auto tm_total = chrono::duration_cast<chrono::seconds>(duration).count();
    auto tm_spend = chrono::duration_cast<chrono::seconds>(bowl.spend()).count();

    cout << "The total amount of spaghetti was: " << tm_total << " secs" << endl
         << "The amount spend on spaghetti was: " << tm_spend << " secs" << endl
         << "Performance: Program runs " << double(tm_total)/tm_spend << "x times faster than its sequential version."
         << endl;

    cout << "Program Ended without deadlock :-|" << endl;

    return 0;
}
