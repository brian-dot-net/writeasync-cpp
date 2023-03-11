#pragma once

#include "coin.h"
#include "trace.h"
#include "decorator.h"

namespace wacpp
{

struct CoinTrace
{
    static std::unique_ptr<ICoin> make_decorator(std::unique_ptr<ICoin> inner, std::shared_ptr<ITracer> tracer, const std::string& name);
};

Decoration<CoinTrace, std::shared_ptr<ITracer>, std::string> with_tracer(std::shared_ptr<ITracer> tracer, std::string&& name);

}