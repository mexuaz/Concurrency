#include "elve.h"

#include <thread>

using namespace std;

atomic<size_t> elve::s_elevesProblemReady = 0;
std::atomic<bool> elve::s_elves_are_with_santa = false;

void elve::make_toys()
{
    this_thread::sleep_for(chrono::milliseconds(m_dist(m_gen)));
}

void elve::solve_problem()
{
    this_thread::sleep_for(chrono::milliseconds(m_dist(m_gen)));
}

elve::elve(mutex *mt, condition_variable *cv)
    : m_gen(random_device{}())
    , m_dist(100, 5000)
    , mp_mt(mt)
    , mp_cv(cv)
{

}

bool elve::problems_need_attention()
{
    return s_elevesProblemReady == c_elvesProblemCount;
}

bool elve::all_problems_solved()
{
    return s_elevesProblemReady == 0;
}

void elve::set_all_problems_solved()
{
    s_elevesProblemReady = 0;
}

void elve::operator()()
{
    while(true) {

        make_toys();


        {
            unique_lock<mutex> guard(*mp_mt);

            // wait until 3 problems of elves get solved
            // this condition is for if there is already 3
            // problems and there are elves with new problems
            // they should wait for the other 3 elves problems to be
            // solved
            mp_cv->wait(guard, [&](){
                return !s_elves_are_with_santa;
            });

            s_elevesProblemReady++;

            // wait until 3 problems are ready
            // this condition is for moments where there are
            // less than 3 problmes
            mp_cv->wait(guard, [&](){
                return elve::problems_need_attention();
            });

            s_elves_are_with_santa = true;
        }
        mp_cv->notify_all();

        solve_problem();

        {
            unique_lock<mutex> guard(*mp_mt);

            // wait until all problems are solved
            mp_cv->wait(guard, [&](){
                return elve::all_problems_solved();
            });

            s_elves_are_with_santa = false;
        }

        // Don't notify other elves untill all the problems get solved
        mp_cv->notify_all();
    }

}
