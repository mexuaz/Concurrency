
#include "customer.h"
#include "barber.h"

#include <iostream>
#include <string>
#include <thread>
#include <random>
#include <chrono>

using namespace std;

int main(int /*argc*/, char** argv) {

    std::string pr(argv[0]);
    pr.erase(0, pr.find_last_of('/')+1);

    cout << "The FIFO Barbershop Problem " << endl
         << "Required at least C++17 "
         << "Your C++ version is " << __cplusplus << endl
         << "Implemented by Amir Mehrafsa (mehrafsa@live.com)" << endl
         << "Usage :" << endl
         << pr << endl;


    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<size_t> dist_customer_stopby(2000, 4000);


    Barber barber;
    thread th(&Barber::operator(), &barber);


    while(true) {
        barber.new_customer(make_shared<Customer>());
        this_thread::sleep_for(chrono::milliseconds(dist_customer_stopby(generator)));
    }



    th.join();




    return 0;
}
