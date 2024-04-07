#include <gtest/gtest.h>

#include <sstream>

#include "config_ser.h"

namespace wacpp::test
{

TEST(config_ser_test, serialize_ini_section)
{
    ConfigSectionIniSerializer ser{};
    ConfigSection s{ "S1" };
    s.insert("K1", "V1");
    s.insert("K2", "V2");

    std::stringstream ss{};

    ser.serialize(s, ss);

    ASSERT_EQ("[S1]\nK1=V1\nK2=V2", ss.str());
}

}