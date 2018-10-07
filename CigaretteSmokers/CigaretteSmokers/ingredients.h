#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#include "supply_agent.h" // becuase of the friend function class ingredients needs the full definition of class supply_agent

#include <mutex>
#include <condition_variable>

// This class is not copyable and should be shared
class ingredients
{
    bool m_tabacco = false;
    bool m_paper = false;
    bool m_matches = false;

    std::mutex m_mt; // This object deletes the copy constructor for the whole class
    std::condition_variable m_cv_supply_ready; // This object detelets teh copy constructors for the whole class
    std::condition_variable m_cv_supply_used;

    friend void supply_agent::set(bool tabacco, bool paper, bool matches);

public:
    enum class infinit_t {
        tabacco,
        paper,
        matches
    };


public:
    ingredients(bool tabacco = false, bool paper = false, bool matches = false);


    void wait_for_complete_with_internal_supply(infinit_t internal_supply);

    /*!
     * \brief reset Reset all values to false
     */
    void reset();

};

#endif // INGREDIENTS_H
