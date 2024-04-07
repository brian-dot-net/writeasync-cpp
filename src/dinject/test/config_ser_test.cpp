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

TEST(config_ser_test, serialize_ini_config)
{
    ConfigIniSerializer ser{};
    Config c{};
    ConfigSection s1{ "S1" };
    s1.insert("K1", "V1");
    ConfigSection s2{ "S2" };
    s2.insert("K2", "V2");
    c.insert(std::move(s1));
    c.insert(std::move(s2));

    std::stringstream ss{};
    ser.serialize(c, ss);

    ASSERT_EQ("\n[S1]\nK1=V1\n[S2]\nK2=V2", ss.str());
}

}