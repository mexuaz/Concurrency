#include "santa.h"

#include "deer.h"
#include "elve.h"

#include <thread>
#include <iostream>

using namespace std;


void santa::deliver_presents()
{
    this_thread::sleep_for(chrono::milliseconds(m_dist(m_gen)));
}

void santa::solve_problems()
{
    this_thread::sleep_for(chrono::milliseconds(m_dist(m_gen)));
}

santa::santa(std::mutex *mt, std::condition_variable *cv)
    : m_gen(random_device{}())
    , m_dist(100, 5000)
    , mp_mt(mt)
    , mp_cv(cv)
{

}

void santa::operator()()
{
    cout << "Santa is asleep ..." << endl;
    while(true) {
        // This is considered as sleep time for Santa
        {
            unique_lock<mutex> guard(*mp_mt);

            // wait until other deers to arrive
            mp_cv->wait(guard, [&](){
                /*
                 * Unlike the statement in the little book of semaphores
                 * it is not possible for both of the conditions to happend
                 * at the same time
                 */
                return deer::all_deers_ready() || elve::problems_need_attention();
            });
        }



        // we could use if--else block since it is unlikely for both
        // to happen at the same time but for book comfortance we use
        // to ordered if block

        // Delivering presents is in the proiority
        if(deer::all_deers_ready()) {
            cout << "Santa is waked up to deliver presents: ";
            deliver_presents();
            deer::set_all_deers_free();
            cout << "done!" << endl;
            mp_cv->notify_all();
        }



        if(elve::problems_need_attention()) {
            cout << "Santa is waked up to solve elves problem: ";
            solve_problems();
            elve::set_all_problems_solved();
            cout << "done!" << endl;
            mp_cv->notify_all();
        }

        cout << "Santa is back to sleep ..." << endl;
    }
}
