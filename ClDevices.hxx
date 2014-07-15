#ifndef CLDEVICES_HXX
#define CLDEVICES_HXX

#include <string>

namespace cl
{
    struct Device
    {
    public:
        virtual ~Device() = default;

        virtual std::string name() const = 0;
    };
}

#endif // CLDEVICES_HXX
