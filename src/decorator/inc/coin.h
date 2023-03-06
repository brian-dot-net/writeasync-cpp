#include <memory>

namespace wacpp
{
class ICoin
{
public:
    virtual ~ICoin() = default;
    virtual bool flip() = 0;
};

std::unique_ptr<ICoin> make_double_headed_coin();

}