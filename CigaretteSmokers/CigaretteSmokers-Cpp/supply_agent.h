#ifndef SUPPLY_AGENT_H
#define SUPPLY_AGENT_H

class ingredients; // forward declartion of class ingredients for friend mehtod purpose

#include <random>

class supply_agent
{
    ingredients* mp_ingredients;

    std::mt19937 m_gen;
    std::uniform_int_distribution<size_t> m_dist_supply_delay; // random duration for agent to prepare the supply in milliseconds
    std::uniform_int_distribution<size_t> m_dist_ingredients; // random number which ingredient to supply

    void prepare(); // dummy delay for agent to provide the ingredients


public:
    supply_agent(ingredients* ings);

    void set(bool tabacco, bool paper, bool matches);


    [[noreturn]] void operator()();

};

#endif // SUPPLY_AGENT_H
