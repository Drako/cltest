#ifndef CLDEVICES_HXX
#define CLDEVICES_HXX

#include <memory>
#include <string>

#include <CL/cl.h>

namespace cl
{
    namespace detail
    {
        struct Device;
    }

    class Platform;

    class Device
    {
    public:
        Device(Platform * platform, cl_device_id id);
        Device(Device &&) = default;
        Device(Device const & source);
        ~Device();

        Device & operator = (Device &&) = default;
        Device & operator = (Device const & source);

    private:
        std::unique_ptr<detail::Device> self;
    };
}

#endif // CLDEVICES_HXX
