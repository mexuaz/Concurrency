#include "spaghetti_bowl.h"

using namespace std;

spaghetti_bowl::spaghetti_bowl(const chrono::nanoseconds& duration /*= std::chrono::nanoseconds::zero()*/)
    : m_duration(duration)
{

}

bool spaghetti_bowl::empty()
{
    lock_guard<mutex> guard(m_mt);
    return m_duration == chrono::nanoseconds::zero();

}

void spaghetti_bowl::consume(const chrono::nanoseconds &tm)
{
    if(empty()) {
        return;
    }

    lock_guard<mutex> guard(m_mt);

    static auto start = chrono::high_resolution_clock::now();

    if( tm > m_duration) {
        m_spend = chrono::high_resolution_clock::now() - start;
        m_duration = chrono::nanoseconds::zero();
        return;
    }
    m_duration -= tm;
}

chrono::nanoseconds spaghetti_bowl::left() const
{
    return m_duration;
}

chrono::nanoseconds spaghetti_bowl::spend() const
{
    return m_spend;
}
