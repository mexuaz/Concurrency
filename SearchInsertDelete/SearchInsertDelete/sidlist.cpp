#include "sidlist.h"

#include <iostream>
#include <algorithm>
#include <thread>

using namespace std;

SIDList::SIDList(std::vector<int>& v)
    : m_list(move(v))
{

}

int SIDList::search(int value)
{
    {
        unique_lock<mutex> guard(m_mt);
        m_cv.wait(guard, [&]() {
            return m_numConcurrentDels==0;
        });
        m_numConcurrentSearches++;
        this->print_status();
    }

    this_thread::sleep_for(chrono::milliseconds(500));
    auto it = find(m_list.begin(), m_list.end(), value);
    m_numConcurrentSearches--;
    m_cv.notify_all();
    if(it != m_list.end()) {
        return -1;
    }
    return static_cast<int>(distance(m_list.begin(), it));
}

void SIDList::insert(int value)
{
    {
        unique_lock<mutex> guard(m_mt);
        m_cv.wait(guard, [&]() {
            return m_numConcurrentDels==0 && m_numConcurrentInserts==0;
        });
        m_numConcurrentInserts++;
        this->print_status();
    }
    this_thread::sleep_for(chrono::milliseconds(500));
    m_list.push_back(value);
    m_numConcurrentInserts--;
    m_cv.notify_all();
}

bool SIDList::del(int indx)
{
    if(indx >= static_cast<int>(m_list.size())) {
        return false;
    }
    {
        unique_lock<mutex> guard(m_mt);
        m_cv.wait(guard, [&](){
            return m_numConcurrentDels==0 && m_numConcurrentInserts==0 && m_numConcurrentSearches==0;
        });
        m_numConcurrentDels++;
        this->print_status();
    }

    m_list.erase(next(m_list.begin(), indx));
    m_numConcurrentDels--;
    m_cv.notify_all();
    return true;
}

bool SIDList::empty()
{
    lock_guard<mutex> guard(m_mt);
    return m_list.empty();
}

void SIDList::print_status()
{
    cout << "Searches: " << m_numConcurrentSearches
         << ", Inserts: " << m_numConcurrentInserts
         << ", Deletes: " << m_numConcurrentDels;

    if(m_numConcurrentDels>0 && (m_numConcurrentSearches || m_numConcurrentSearches)) {
        cout << endl << "--Error Caught--" << endl;
    }

    if(m_numConcurrentInserts > 1) {
        cout << endl << "--Error Caught--" << endl;
    }


    if(m_numConcurrentSearches > 1 && m_numConcurrentInserts == 1) {
        cout << endl << "**We are good (just to make sure things like this happens)**" << endl;
    }

    if(m_numConcurrentDels == 1) {
        cout << endl << "**We are good (just to make sure things like this happens)**" << endl;
    }


    cout << "\r" << flush;
}
