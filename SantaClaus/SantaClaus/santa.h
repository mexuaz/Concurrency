#ifndef SANTA_H
#define SANTA_H


#include <random>

#include <atomic>

#include <mutex>
#include <condition_variable>

class santa
{
    std::mt19937 m_gen;
    std::uniform_int_distribution<size_t> m_dist;

    std::mutex* mp_mt;
    std::condition_variable* mp_cv;

    void deliver_presents();

    void solve_problems();

public:
    santa(std::mutex* mt, std::condition_variable* cv);

    [[noreturn]] void operator()();
};

#endif // SANTA_H
