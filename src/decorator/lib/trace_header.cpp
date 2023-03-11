#include <sstream>

#include "trace_header.h"

namespace
{

class TracerWithHeader : public wacpp::ITracer
{
public:
    TracerWithHeader(std::shared_ptr<ITracer> inner, const std::string& header)
        : m_inner(inner), m_header(header)
    {
    }

    void trace(const std::string& message) override
    {
        std::stringstream ss;
        ss << "[" << m_header << "] " << message;
        m_inner->trace(ss.str());
    }

private:
    std::shared_ptr<ITracer> m_inner;
    std::string m_header;
};

}

namespace wacpp
{

Decoration<TraceHeader, std::string> with_header(std::string&& header)
{
    return with_decoration<TraceHeader>(std::move(header));
}

std::shared_ptr<ITracer> TraceHeader::make_decorator(std::shared_ptr<ITracer> tracer, std::string header)
{
    return std::make_shared<TracerWithHeader>(std::move(tracer), header);
}

}