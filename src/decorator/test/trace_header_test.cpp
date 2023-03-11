#include <gtest/gtest.h>
#include <sstream>
#include "trace_header.h"

namespace wacpp::test
{

TEST(trace_header_test, traces_to_ostream_with_header)
{
    std::stringstream ss;
    auto tracer = make_ostream_tracer(ss) * with_header("+++");

    tracer->trace("message 1");
    tracer->trace("message 2");

    ASSERT_EQ("[+++] message 1\n[+++] message 2\n", ss.str());
}

}