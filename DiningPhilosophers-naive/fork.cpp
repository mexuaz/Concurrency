#include "fork.h"

using namespace std;

fork::fork(size_t id)
    : m_id(id)
{
}

size_t fork::id() const
{
    return m_id;
}

void fork::pick_up()
{
    unique_lock<mutex> guard(m_mt);
    m_cv.wait(guard, [&]{return m_available;});
    m_available = false;
}

void fork::put_down()
{
    unique_lock<mutex> guard(m_mt);
    m_available = true;
    m_cv.notify_one();
}
