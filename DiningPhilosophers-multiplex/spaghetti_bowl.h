#ifndef SPAGHETTI_BOWL_H
#define SPAGHETTI_BOWL_H

#include <chrono>
#include <mutex>


class spaghetti_bowl
{
    std::mutex m_mt; // This object has no longer copy contructor since mutex doesn't have one
    std::chrono::duration<size_t, std::nano> m_duration; // Duration of total bowl
    std::chrono::duration<size_t, std::nano> m_spend = std::chrono::duration<size_t, std::nano>::zero(); // Duration spend on bowl overall
public:
    spaghetti_bowl(const std::chrono::nanoseconds& duration = std::chrono::nanoseconds::zero());
    bool empty( void );
    void consume(const std::chrono::nanoseconds& tm);

    // Amount of spaghetti left to finish the bowl
    std::chrono::nanoseconds left( void ) const;

    // Amount of time spend on bowl
    std::chrono::nanoseconds spend( void ) const;

};

#endif // SPAGHETTI_BOWL_H
