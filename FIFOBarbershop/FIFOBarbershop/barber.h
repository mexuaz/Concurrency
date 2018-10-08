#ifndef BARBER_H
#define BARBER_H

#include "customer.h"

#include <queue>
#include <mutex>
#include <condition_variable>


class Barber
{
    size_t m_maxChairs = 4; // Maximum number of chairs at barbershop
    std::queue<std::shared_ptr<Customer>> m_waitingRoom;

    std::mutex m_mt;
    std::condition_variable m_cv;

public:
    Barber();

    void new_customer(const std::shared_ptr<Customer>&& customer);

    [[noreturn]] void operator()(); // Do hair cut
};

#endif // BARBER_H
