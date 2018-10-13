#include "smoker.h"

#include <thread>
#include <iostream>

using namespace std;

void smoker::make_cigarettes()
{
    mp_external_supply->reset(); // use the supply
}

void smoker::smoke()
{
    cout << "Somker#" << m_id << " started smoking!" << endl;
    // Sleeps thread for random miliseconds (smoking time)
    auto t(chrono::milliseconds(m_dist_smoke(m_gen)));
    this_thread::sleep_for(t);
     cout << "Somker#" << m_id << " finished smoking!" << endl;
}

smoker::smoker(size_t id, ingredients::infinit_t infinite_supply, ingredients *external_supply)
    : m_id(id)
    , m_infinite_supply(infinite_supply)
    , mp_external_supply(external_supply)
    , m_gen(random_device()())
    , m_dist_smoke(1000, 5000)
{

}

void smoker::operator()()
{
    while(true) {
        mp_external_supply->wait_for_complete_with_internal_supply(m_infinite_supply);
        this->make_cigarettes();
        this->smoke();
    }
}
