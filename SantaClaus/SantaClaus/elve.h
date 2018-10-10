#ifndef ELVE_H
#define ELVE_H

#include <random>
#include <atomic>
#include <mutex>
#include <condition_variable>

class elve
{
    static const size_t c_elvesProblemCount = 3;
    static std::atomic<size_t> s_elevesProblemReady;
    static std::atomic<bool> s_elves_are_with_santa;

    std::mt19937 m_gen;
    std::uniform_int_distribution<size_t> m_dist;

    std::mutex* mp_mt;
    std::condition_variable* mp_cv;

    void make_toys();
    void solve_problem();

public:
    elve(std::mutex* mt, std::condition_variable* cv);

    static bool problems_need_attention();

    static bool all_problems_solved();

    static void set_all_problems_solved();

    [[noreturn]] void operator()();
};

#endif // ELVE_H
