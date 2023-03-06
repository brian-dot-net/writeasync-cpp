#include "coin.h"

namespace
{

class DoubleHeadedCoin : public wacpp::ICoin
{
    bool flip() override
    {
        return true;
    }
};

}

namespace wacpp
{

std::unique_ptr<ICoin> make_double_headed_coin()
{
    return std::make_unique<DoubleHeadedCoin>();
}

}