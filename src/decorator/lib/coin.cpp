#include <random>
#include "coin.h"

namespace
{

class DoubleHeadedCoin : public wacpp::ICoin
{
public:
    bool flip() override
    {
        return true;
    }
};

class FairCoin : public wacpp::ICoin
{
public:
    FairCoin()
        : m_rand(0, 1)
        , m_engine()
    {
        m_engine.seed();
    }

    bool flip() override
    {
        return m_rand(m_engine) == 1;
    }

private:
    std::uniform_int_distribution<int> m_rand;
    std::mt19937 m_engine;
};

}

namespace wacpp
{

std::unique_ptr<ICoin> make_double_headed_coin()
{
    return std::make_unique<DoubleHeadedCoin>();
}

std::unique_ptr<ICoin> make_fair_coin()
{
    return std::make_unique<FairCoin>();
}

}