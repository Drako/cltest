#include "ClDevices.hxx"
#include "ClPlatforms.hxx"

namespace cl
{
    namespace detail
    {
        struct Device
        {
            ::cl::Platform * platform;
            cl_device_id id;
        };
    }

    Device::Device(Platform * platform, cl_device_id id)
        : self(new detail::Device)
    {
        self->platform = platform;
        self->id = id;
    }

    Device::Device(Device const & source)
        : self(new detail::Device(*(source.self.get())))
    {
    }

    Device::~Device()
    {
    }

    Device & Device::operator = (Device const & source)
    {
        self.reset(new detail::Device(*(source.self.get())));
        return (*this);
    }
}
