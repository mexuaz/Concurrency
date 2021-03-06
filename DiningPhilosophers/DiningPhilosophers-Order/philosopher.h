#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include "fork.h"
#include "spaghetti_bowl.h"

#include <chrono>
#include <random>

#include <atomic>



class philosopher
{
    size_t m_id;
    fork* mp_leftFork;
    fork* mp_rightFork;
    spaghetti_bowl* mp_bowl;

    bool m_left_first = true;

    static std::atomic<int> s_concurrentDining; // To keep number of concurrent philosphers dining at least one fork in hand



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
                bool left_first = true,
                size_t max_think = 5, size_t max_eat = 20000);

    void operator()();
};

#endif // PHILOSOPHER_H
