#include "supply_agent.h"

#include "ingredients.h"

#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

void supply_agent::prepare()
{
    // Sleeps thread for random miliseconds (prepare time)
    auto t(chrono::milliseconds(m_dist_supply_delay(m_gen)));
    this_thread::sleep_for(t);
}



supply_agent::supply_agent(ingredients *ings)
    : mp_ingredients(ings)
    , m_gen(random_device()())
    , m_dist_supply_delay(1000, 5000)
    , m_dist_ingredients(0, 2)
{

}


void supply_agent::set(bool tabacco, bool paper, bool matches)
{
    unique_lock<mutex> guard(mp_ingredients->m_mt);
    mp_ingredients->m_cv_supply_used.wait(guard, [&]() {
        return !(mp_ingredients->m_tabacco || mp_ingredients->m_paper || mp_ingredients->m_matches);
    });
    mp_ingredients->m_tabacco = tabacco;
    mp_ingredients->m_paper = paper;
    mp_ingredients->m_matches = matches;
    mp_ingredients->m_cv_supply_ready.notify_all();
}

void supply_agent::operator()()
{
    while(true) {
        this->prepare();

        auto ing(m_dist_ingredients(m_gen));
        switch (ing) {
        case 0:
            this->set(true, true, false);
            cout << "Agent supplied: tabacco and paper" << endl;
            break;
        case 1:
            this->set(true, false, true);
            cout << "Agent supplied: tabacco and matches" << endl;
            break;
        default:
            this->set(false, true, true);
            cout << "Agent supplied: paper and matches" << endl;
        }
    } // End of infinite loop
}
