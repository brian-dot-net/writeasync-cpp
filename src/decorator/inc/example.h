#include <string>

namespace wacpp
{
class Example
{
public:
    Example(const std::string& name);

    std::string greet() const;

private:
    std::string m_name;
};
}