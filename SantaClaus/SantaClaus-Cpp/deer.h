#ifndef DEER_H
#define DEER_H

#include <random>
#include <atomic>
#include <mutex>
#include <condition_variable>

class deer
{
    static const size_t c_deersCount = 9;
    static std::atomic<size_t> s_deersReady;

    std::mt19937 m_gen;
    std::uniform_int_distribution<size_t> m_dist;

    std::mutex* mp_mt;
    std::condition_variable* mp_cv;

    void take_vacation();
    void deliver_presents();

public:
    deer(std::mutex* mt, std::condition_variable* cv);

    static bool all_deers_ready();

    static bool all_deers_done();

    static void set_all_deers_free();

    [[noreturn]] void operator()();
};

#endif // DEER_H
