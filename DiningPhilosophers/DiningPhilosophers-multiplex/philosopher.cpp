#include "philosopher.h"


#include <random>
#include <thread>
#include <iostream>

using namespace std;


atomic<int> philosopher::s_concurrentDining = 0;
mutex philosopher::s_mt;
condition_variable philosopher::s_cv;

void philosopher::think()
{
    // Sleeps thread for random miliseconds (thinking time)
    this_thread::sleep_for(chrono::milliseconds(m_dist_think(m_gen)));
}

chrono::nanoseconds philosopher::dine()
{
    // Sleeps or busy wait thread for random miliseconds (dining time)
    auto t(chrono::milliseconds(m_dist_eat(m_gen)));
    auto start = chrono::high_resolution_clock::now();
    while(t > chrono::high_resolution_clock::now()-start);
    //this_thread::sleep_for(t);
    return t;

}

philosopher::philosopher(size_t id, fork* leftFork, fork* rightFrok, spaghetti_bowl* bowl,
                         size_t max_think /*= 5*/, size_t max_eat /*= 500*/)
    : m_id(id)
    , mp_leftFork(leftFork)
    , mp_rightFork(rightFrok)
    , mp_bowl(bowl)
    , m_gen(random_device()())
    , m_dist_think(0, max_think)
    , m_dist_eat(0, max_eat)
{
}

void philosopher::operator()()
{
    while(!mp_bowl->empty()) {

        think();

        {
            unique_lock<mutex> guard(s_mt);
            s_cv.wait(guard, [](){return s_concurrentDining < 4;});
        }
        s_concurrentDining++; // Since this is an atomic variable the operation is well behaviour and does not need to be gaurded

        mp_leftFork->pick_up();
        mp_rightFork->pick_up();

        if(!mp_bowl->empty()) {
            unique_lock<mutex> guard(s_mt);
            cout << "Concurrent philosophers: " << s_concurrentDining
                 << " and spaghetti left " << chrono::duration_cast<chrono::seconds>( mp_bowl->left() ).count()
                 << " secs \r" << flush;
        }


        auto t = dine();

        mp_rightFork->put_down();
        mp_leftFork->put_down();

        s_concurrentDining--;
        s_cv.notify_one();

        mp_bowl->consume(t);

        m_dining_duration += t;
        m_dining_number +=1;




    } // loop until bowl is empty

    {
        unique_lock<mutex> guard(s_mt);
        cout << "Philosopher " << m_id << " finished eating "
             << "Spend " << chrono::duration_cast<chrono::seconds>(m_dining_duration).count() << " secs in "
             << m_dining_number << " attempts "
             << "on dining." << endl;

    }

}


