
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <thread>
#include <vector>
#include <numeric> // iota
#include <algorithm> // shuffle sort merge
#include <random>
#include <chrono>
#include <utility>

using namespace std;

int main(int argc, char** argv) {

    std::string pr(argv[0]);
    pr.erase(0, pr.find_last_of('/')+1);

    int nSplits = 8; // default size of spilit
    if(argc > 1 ) {
        stringstream(argv[1]) >> nSplits;
    }

    size_t sz = 1e8; // default size of list
    if(argc > 2) {
        stringstream(argv[2]) >> sz;
    }

    bool verbose = true; // default status for verbose
    if(argc > 3) {
        stringstream(argv[3]) >> verbose;
    }


    if(verbose) {
        cout << "The 06 Problem " << endl
             << "Required at least C++17 "
             << "Your C++ version is " << __cplusplus << endl
             << "Implemented by Amir Mehrafsa (mehrafsa@live.com)" << endl
             << "Usage :" << endl
             << pr << " [number of splits (=8)] [size of list (=1e8)] [verbose(=true)]" << endl;
    }


    auto is_power_of_two = [](int n){return n && !(n & (n - 1));};

    if(!is_power_of_two(nSplits)) {
        cerr << "Number of the spilits should be power of two!" << endl;
        return -1;
    }

    vector<int> ilist(sz); // initial list
    iota(ilist.begin(), ilist.end(), 0);
    shuffle(ilist.begin(), ilist.end(), mt19937{random_device{}()});

    int div = int(sz)/nSplits;

    //auto print_list = [](const vector<int>& l) {copy(cbegin(l), cend(l), ostream_iterator<int>(cout, " "));cout << endl;};

    if(verbose) {
        cout << "Initialization complete!" << endl;
    }


    auto start = chrono::high_resolution_clock::now();

    vector<pair<int, int>> lss(static_cast<size_t>(nSplits)); // this list stores the start and end positions of list
    for (int i = 0; i < nSplits-1; i++) {
        lss[static_cast<size_t>(i)]= make_pair(i*div, (i+1)*div);
    }
    lss[static_cast<size_t>(nSplits-1)] =  make_pair((nSplits-1)*div, ilist.size()); // this is better instead of having if-else in the for-loop

    vector<shared_ptr<thread>> ths(static_cast<size_t>(nSplits));
    auto th = ths.begin();
    for (const auto& l : lss) {
        *th = make_shared<thread>([&](){sort(ilist.begin()+ l.first, ilist.begin()+ l.second);});
        th++;
    }


    for(auto& th : ths) {
        if(th->joinable()) {
            th->join();
        }
    }

    while(lss.size() > 1) {

        decltype (ilist) tilist;
        decltype (lss) tlss;

        for(size_t i = 0; i < lss.size(); i+=2) {
            auto t = make_pair(tilist.size(), 0);
            merge(ilist.begin()+lss[i].first, ilist.begin()+lss[i].second, ilist.begin()+lss[i+1].first, ilist.begin()+lss[i+1].second, std::back_inserter(tilist));
            t.second = int(tilist.size());
            tlss.push_back(t);

        }

        lss.clear();
        swap(lss, tlss);

        ilist.clear();
        swap(ilist, tilist);
    }


    auto duration = chrono::high_resolution_clock::now() - start;

    if(verbose) {
        cout << "Number of splits: " << nSplits << ", Size of list: " << ilist.size()
             << endl << "total time spend (milliseconds): ";
    }
    cout << chrono::duration_cast<chrono::milliseconds>(duration).count() << endl;


    return 0;
}
