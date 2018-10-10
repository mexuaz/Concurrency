#include "deer.h"

#include <thread>

using namespace std;

atomic<size_t> deer::s_deersReady = 0;

void deer::take_vacation()
{
    this_thread::sleep_for(chrono::milliseconds(m_dist(m_gen)));
}

void deer::deliver_presents()
{
    this_thread::sleep_for(chrono::milliseconds(m_dist(m_gen)));
}

deer::deer(mutex *mt, condition_variable *cv)
    : m_gen(random_device{}())
    , m_dist(100, 5000)
    , mp_mt(mt)
    , mp_cv(cv)
{

}

bool deer::all_deers_ready()
{
    return s_deersReady == c_deersCount;
}

bool deer::all_deers_done()
{
    return s_deersReady == 0;
}

void deer::set_all_deers_free()
{
    s_deersReady = 0;
}

void deer::operator()()
{
    while(true) {

        take_vacation();


        {
            unique_lock<mutex> guard(*mp_mt);

            s_deersReady++;

            // wait until other deers to return from vacation
            mp_cv->wait(guard, [&](){
                return deer::all_deers_ready();
            });
        }
        mp_cv->notify_all();

        deliver_presents();

        // Santa will decrease the s_deersReady to zero

        {
            unique_lock<mutex> guard(*mp_mt);

            // wait until other deers deliver the presents
            mp_cv->wait(guard, [&](){
                return deer::all_deers_done();
            });
        }


        auto k = 0;
    }

}
