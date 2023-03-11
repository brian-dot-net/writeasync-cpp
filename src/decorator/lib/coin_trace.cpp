#include <sstream>
#include "coin_trace.h"

namespace
{

class TracedCoin : public wacpp::ICoin
{
public:
    TracedCoin(std::unique_ptr<wacpp::ICoin> inner, std::shared_ptr<wacpp::ITracer> tracer, const std::string& name)
        : m_inner(std::move(inner)), m_tracer(std::move(tracer))
    {
        std::stringstream ss;
        ss << "Flipping " << name << "...";
        m_tracer->trace(ss.str());
    }

    bool flip() override
    {
        bool result = m_inner->flip();
        if (result)
        {
            m_tracer->trace("It was heads!");
        }
        else
        {
            m_tracer->trace("It was tails!");
        }

        return result;
    }

private:
    std::unique_ptr<wacpp::ICoin> m_inner;
    std::shared_ptr<wacpp::ITracer> m_tracer;
};

}

namespace wacpp
{

Decoration<CoinTrace, std::shared_ptr<ITracer>, std::string> with_tracer(std::shared_ptr<ITracer> tracer, std::string&& name)
{
    return with_decoration<CoinTrace>(std::move(tracer), std::move(name));
}

std::unique_ptr<ICoin> CoinTrace::make_decorator(std::unique_ptr<ICoin> inner, std::shared_ptr<ITracer> tracer, std::string name)
{
    return std::make_unique<TracedCoin>(std::move(inner), std::move(tracer), name);
}

}