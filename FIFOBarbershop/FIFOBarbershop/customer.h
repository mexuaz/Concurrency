#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <random>

class Customer
{
    static size_t s_id;

    size_t m_id; // self-generated id

    static std::random_device s_rd;
    static std::mt19937 s_gen;
    static std::uniform_int_distribution<size_t> s_dist_haircut_duration; // distrbution of random number for duration of haircut for each customer


    size_t m_hairCutLength = 0;
    bool m_hairCutDone = false; // This variable will be true after hair cut

public:
    Customer();

    ~Customer();

    size_t id() const;

    void operator()();
};

#endif // CUSTOMER_H
