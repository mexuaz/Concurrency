#include "sidlist.h"

#include <iostream>
#include <string>
#include <sstream>
#include <future>

#include <vector>
#include <numeric> // iota
#include <algorithm> // shuffle
#include <random>

using namespace std;

int main(int argc, char** argv) {

    std::string pr(argv[0]);
    pr.erase(0, pr.find_last_of('/')+1);

    cout << "The Search Insert Delete Problem " << endl
         << "Required at least C++17 "
         << "Your C++ version is " << __cplusplus << endl
         << "Implemented by Amir Mehrafsa (mehrafsa@live.com)" << endl
         << "Usage :" << endl
         << pr << " [size of list (=1e7)]" << endl;

    // default duration of spaghetti bowl
    size_t sz = 1e7;
    if(argc > 1 ) {
        stringstream(argv[1]) >> sz;
    }


    vector<int> v(sz);
    iota(v.begin(), v.end(), 0);
    shuffle(v.begin(), v.end(), mt19937{random_device{}()});


    mt19937 generator(random_device{}());
    uniform_int_distribution<size_t> dist_item(0, sz);
    uniform_int_distribution<size_t> dist_delay(100, 500);
    uniform_int_distribution<size_t> dist_method(0, 5);

    cout << "Initialization complete!" << endl;

    SIDList ls(v);


    vector<shared_ptr<future<int>>> search_results;
    vector<shared_ptr<thread>> insert_threads;
    vector<shared_ptr<future<bool>>> del_results;

    while(!ls.empty()) {

        switch (dist_method(generator)) {
        case 0:
        case 1:
        case 2:
            search_results.push_back(make_shared<future<int>>(async(&SIDList::search, &ls, dist_item(generator))));
            break;
        case 3:
        case 4:
            insert_threads.push_back(make_shared<thread>(&SIDList::insert, &ls, dist_item(generator)));
            break;
        case 5:
            del_results.push_back(make_shared<future<bool>>(async(&SIDList::del, &ls, dist_item(generator))));
            break;
        } // end of switch
        this_thread::sleep_for(chrono::milliseconds(dist_delay(generator)));

        //clean up search
        if(search_results.size() > 1e3) {
            for(auto& s : search_results) {
                s.get();
            }
            search_results.clear();
        }


        // clean up inserts
        if(insert_threads.size() > 1e3) {
            for(auto& i : insert_threads) {
                if(i->joinable()) {
                    i->join();
                }
            }
            insert_threads.clear();
        }


        // clean up deletes
        if(del_results.size() > 1e3) {
            for(auto& d : del_results) {
                d.get();
            }
            del_results.clear();
        }
    }


    return 0;
}
