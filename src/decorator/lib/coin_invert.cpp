#include <sstream>
#include "coin_invert.h"

namespace
{

class InvertedCoin : public wacpp::ICoin
{
public:
    InvertedCoin(std::unique_ptr<wacpp::ICoin> inner)
        : m_inner(std::move(inner))
    {
    }

    bool flip() override
    {
        return !m_inner->flip();
    }

private:
    std::unique_ptr<wacpp::ICoin> m_inner;
};

}

namespace wacpp
{

std::unique_ptr<ICoin> make_inverted_coin(std::unique_ptr<ICoin> inner)
{
    return std::make_unique<InvertedCoin>(std::move(inner));
}

Decoration<CoinInvert> with_inversion()
{
    return with_decoration<CoinInvert>();
}

std::unique_ptr<ICoin> CoinInvert::make_decorator(std::unique_ptr<ICoin> inner)
{
    return make_inverted_coin(std::move(inner));
}
}