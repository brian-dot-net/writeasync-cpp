#include <gtest/gtest.h>

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "config.h"

namespace
{

std::vector<std::string> get_all_values(const wacpp::ConfigSection& s)
{
    std::vector<std::string> values{};
    for (const auto& [name, value] : s)
    {
        values.push_back(name + "=" + value);
    }

    std::sort(values.begin(), values.end());
    return values;
}

int get_section_count(const wacpp::Config& c)
{
    int count = 0;
    for ([[maybe_unused]] const auto& _ : c)
    {
        ++count;
    }

    return count;
}

}

namespace wacpp::test
{

TEST(config_test, basic_section)
{
    ConfigSection s{ "S1" };

    ASSERT_EQ("S1", s.name());

    auto values = get_all_values(s);

    ASSERT_EQ(0, values.size());

    s.insert("K1", "V1");

    values = get_all_values(s);

    ASSERT_EQ(1, values.size());
    ASSERT_EQ("K1=V1", values[0]);
    ASSERT_EQ("V1", s.value("K1"));

    s.insert("K2", "V2");

    values = get_all_values(s);

    ASSERT_EQ(2, values.size());
    ASSERT_EQ("K1=V1", values[0]);
    ASSERT_EQ("V1", s.value("K1"));
    ASSERT_EQ("K2=V2", values[1]);
    ASSERT_EQ("V2", s.value("K2"));

    s.remove("K1");
    ASSERT_NO_THROW(s.remove("DoesNotExist"));

    values = get_all_values(s);

    ASSERT_EQ(1, values.size());
    ASSERT_EQ("K2=V2", values[0]);
    ASSERT_EQ("V2", s.value("K2"));

    ASSERT_THROW(s.value("K1"), std::runtime_error);
}

TEST(config_test, basic_config)
{
    Config c{};

    ASSERT_THROW(c.section("DoesNotExist"), std::runtime_error);
    ASSERT_NO_THROW(c.remove("DoesNotExist"));

    ASSERT_EQ(0, get_section_count(c));

    c.insert(ConfigSection{ "S1" });

    int count = 0;
    for (auto& [name, s] : c)
    {
        ASSERT_EQ("S1", name);
        ASSERT_EQ("S1", s.name());
        s.insert("K1", "V1");
        ++count;
    }

    ASSERT_EQ(1, count);

    const Config& cc{ c };

    count = 0;
    for (const auto& [name, s] : cc)
    {
        ASSERT_EQ("S1", name);
        ASSERT_EQ("S1", s.name());
        ASSERT_EQ("V1", s.value("K1"));
        ++count;
    }

    ASSERT_EQ(1, count);

    c.insert(ConfigSection{ "S2" });

    ASSERT_EQ(2, get_section_count(c));

    c.remove("S1");
    c.remove("S2");

    ASSERT_EQ(0, get_section_count(c));
}

}