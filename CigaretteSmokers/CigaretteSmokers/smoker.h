#ifndef SMOKER_H
#define SMOKER_H

#include "ingredients.h"

#include <random>

class smoker
{
    size_t m_id;

    ingredients::infinit_t m_infinite_supply; // infinite (interal supply) of one type
    ingredients* mp_external_supply; // external supply of ingredients by agent (shared memory)

    std::mt19937 m_gen;
    std::uniform_int_distribution<size_t> m_dist_smoke; // duration for making cigarettes in milisecon

    void make_cigarettes();

    void smoke();

public:
    smoker(size_t id, ingredients::infinit_t infinite_supply, ingredients* external_supply);

    [[ noreturn ]] void operator()();
};

#endif // PHILOSOPHER_H
