#include <iostream>

#include "config_ser.h"

int main()
{
    using namespace wacpp;

    Config c{};

    ConfigSection s1{ "S1" };
    s1.insert("K1", "V1");
    c.insert(std::move(s1));

    ConfigSection s2{ "S2" };
    s2.insert("K2", "V2");
    c.insert(std::move(s2));

    ConfigSectionIniSerializer css{};
    ConfigIniSerializer cs{ css };
    cs.serialize(c, std::cout);

    return 0;
}
