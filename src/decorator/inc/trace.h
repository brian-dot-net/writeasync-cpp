#include <memory>
#include <ostream>
#include <string>

namespace wacpp
{

class ITracer
{
public:
    virtual ~ITracer() = default;
    virtual void trace(const std::string& message) = 0;
};

std::unique_ptr<ITracer> make_ostream_tracer(std::ostream& out);

}