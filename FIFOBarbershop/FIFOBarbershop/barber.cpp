#include "barber.h"

using namespace std;

Barber::Barber()
{

}

void Barber::new_customer(const std::shared_ptr<Customer>&& customer)
{
    unique_lock<mutex> guard(m_mt);
    if(m_waitingRoom.size() >= m_maxChairs) {
        return;
    }
    m_waitingRoom.push(move(customer));
    m_cv.notify_one();
}

void Barber::operator()()
{
    while(true) {
        shared_ptr<Customer> customer = nullptr;
        {
            unique_lock<mutex> guard(m_mt);
            m_cv.wait(guard, [&]() {
                return !m_waitingRoom.empty();
            });
            customer = move(m_waitingRoom.front());
            m_waitingRoom.pop();
        }
        (*customer)();
    }
}
