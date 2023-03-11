#include "trace.h"

namespace
{

class OstreamTracer : public wacpp::ITracer
{
public:
    OstreamTracer(std::ostream& out)
        : m_out(out)
    {
    }

    void trace(const std::string& message) override
    {
        m_out << message << std::endl;
    }

private:
    std::ostream& m_out;
};

}

namespace wacpp
{

std::shared_ptr<ITracer> make_ostream_tracer(std::ostream& out)
{
    return std::make_shared<OstreamTracer>(out);
}

}