#ifndef SIDLIST_H
#define SIDLIST_H


#include <vector>

#include <atomic>
#include <mutex>
#include <condition_variable>

class SIDList
{
    std::vector<int> m_list;

    std::atomic<size_t> m_numConcurrentSearches = 0;
    std::atomic<size_t> m_numConcurrentInserts = 0;
    std::atomic<size_t> m_numConcurrentDels = 0;

    std::mutex m_mt;
    std::condition_variable m_cv;

public:
    SIDList(std::vector<int>& v);

    /*!
     * \brief search Search for a given value within the list
     * \param value
     * \return -1 if the the value was not in the list otherwise returns the index of item
     * return value is limited to the signed integer
     */
    int search(int value);

    /*!
     * \brief Insert the given value to the end of the list
     * \param value
     */
    void insert(int value);



    /*!
     * \brief del Remove the ginve index form list if the index is within the list
     * \param indx
     * \return true if the remove was successful otherwise false
     */
    bool del(int indx);

    bool empty(void);

    /*!
     * \brief print_status print the number of concurrent searches, deletes and inserts
     */
    void print_status();
};

#endif // SIDLIST_H
