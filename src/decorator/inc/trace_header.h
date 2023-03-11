#pragma once

#include "trace.h"
#include "decorator.h"

namespace wacpp
{

struct TraceHeader
{
    static std::shared_ptr<ITracer> make_decorator(std::shared_ptr<ITracer> tracer, std::string header);
};

Decoration<TraceHeader, std::string> with_header(std::string&& header);

}