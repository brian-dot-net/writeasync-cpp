#include <gtest/gtest.h>
#include <sstream>
#include "trace.h"

namespace wacpp::test
{

TEST(trace_test, traces_to_ostream)
{
    std::stringstream ss;
    auto tracer = make_ostream_tracer(ss);

    tracer->trace("message 1");
    tracer->trace("message 2");

    ASSERT_EQ("message 1\nmessage 2\n", ss.str());
}

}