#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include "fork.h"
#include "spaghetti_bowl.h"

#include <chrono>
#include <random>

#include <atomic>
#include <mutex>
#include <condition_variable>


class philosopher
{
    size_t m_id;
    fork* mp_leftFork;
    fork* mp_rightFork;
    spaghetti_bowl* mp_bowl;

    static std::atomic<int> s_concurrentDining; // To keep number of concurrent philosphers dining at least one fork in hand
    static std::mutex s_mt;
    static std::condition_variable s_cv;


    std::mt19937 m_gen;
    std::uniform_int_distribution<size_t> m_dist_think; // duration for think in miliseconds
    std::uniform_int_distribution<size_t> m_dist_eat; // duration for eat in milisconds

    std::chrono::duration<size_t, std::nano> m_dining_duration = std::chrono::duration<size_t, std::nano>::zero();
    size_t m_dining_number = 0;


    void think();

    /*!
     * \brief dine
     * \return The amount of time spend on dining
     */
    std::chrono::nanoseconds dine();

public:
    philosopher(size_t id, fork* leftFork, fork* rightFrok, spaghetti_bowl* bowl,
                size_t max_think = 5, size_t max_eat = 100);

    void operator()();
};

#endif // PHILOSOPHER_H
