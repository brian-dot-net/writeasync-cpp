#include <gtest/gtest.h>

#include <sstream>

#include "config_ser.h"

namespace
{

void serialize_ini_config(wacpp::RefOrUPtr<wacpp::ISerializer<wacpp::ConfigSection>>&& inner_ser)
{
    wacpp::ConfigIniSerializer ser{ std::move(inner_ser) };
    wacpp::Config c{};
    wacpp::ConfigSection s1{ "S1" };
    s1.insert("K1", "V1");
    wacpp::ConfigSection s2{ "S2" };
    s2.insert("K2", "V2");
    c.insert(std::move(s1));
    c.insert(std::move(s2));

    std::stringstream ss{};
    ser.serialize(c, ss);

    ASSERT_EQ("\n[S1]\nK1=V1\n[S2]\nK2=V2", ss.str());
}

}

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

TEST(config_ser_test, serialize_ini_config_ref)
{
    ConfigSectionIniSerializer inner_ser{};
    auto& inner_ser_ref{ inner_ser };
    serialize_ini_config(inner_ser_ref);
}

TEST(config_ser_test, serialize_ini_config_uptr)
{
    serialize_ini_config(make_config_section_ini_serializer());
}

}