#include "customer.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

size_t Customer::s_id = 0;

random_device Customer::s_rd;
mt19937 Customer::s_gen(s_rd());
uniform_int_distribution<size_t> Customer::s_dist_haircut_duration(1000, 10000);



Customer::Customer()
 : m_id(++s_id)
 , m_hairCutLength(s_dist_haircut_duration(s_gen))
{
    cout << "Customer#" << m_id << " entered the barbershop." << endl;
}

Customer::~Customer()
{
    if(m_hairCutDone) {
        cout << "Customer#" << m_id << " left the barbershop after haircut." << endl;
    } else {
        cout << "Customer#" << m_id << " left the barbershop without haircut." << endl;
    }
}

size_t Customer::id() const
{
    return m_id;
}

void Customer::operator()()
{
    cout << "Customer#" << m_id << " started the haircut." << endl;
    this_thread::sleep_for(chrono::milliseconds(m_hairCutLength));
    m_hairCutDone = true;
     cout << "Customer#" << m_id << " finished the haircut." << endl;
}
