#ifndef CLDEVICE_IMPL_HXX
#define CLDEVICE_IMPL_HXX

#include "ClDevices.hxx"

#include <CL/cl.h>

namespace cl
{
    namespace impl
    {
        class Device
            : public ::cl::Device
        {
        public:
            Device(cl_platform_id pid, cl_device_id did);
            virtual ~Device() = default;

            virtual std::string name() const;

        protected:
            cl_platform_id platform_id_;
            cl_device_id device_id_;
            std::string name_;

        private:
            std::string get_info(cl_device_info info);
        };
    }
}

#endif // CLDEVICE_IMPL_HXX
