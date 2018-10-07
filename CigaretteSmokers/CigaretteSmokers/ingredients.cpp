#include "ingredients.h"

using namespace std;

ingredients::ingredients(bool tabacco /*= false*/, bool paper /*= false*/, bool matches /*= false*/)
    : m_tabacco(tabacco)
    , m_paper(paper)
    , m_matches(matches)
{

}


void ingredients::wait_for_complete_with_internal_supply(ingredients::infinit_t internal_supply)
{
    unique_lock<mutex> guard(m_mt);
    m_cv_supply_ready.wait(guard, [&]() {
        switch (internal_supply) {
        case ingredients::infinit_t::tabacco:
            return m_paper && m_matches;
        case ingredients::infinit_t::paper:
            return m_tabacco && m_matches;
        case ingredients::infinit_t::matches:
            return m_paper && m_tabacco;
        }
    });
}



void ingredients::reset()
{
    unique_lock<mutex> guard(m_mt);
    m_tabacco = false;
    m_paper = false;
    m_matches = false;
    m_cv_supply_used.notify_one();
}

