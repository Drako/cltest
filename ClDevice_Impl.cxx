#include "ClDevice_Impl.hxx"

#include <vector>

namespace cl
{
    namespace impl
    {
        Device::Device(cl_platform_id pid, cl_device_id did)
            : platform_id_(pid)
            , device_id_(did)
            , name_(get_info(CL_DEVICE_NAME))
        {
        }

        std::string Device::name() const
        {
            return name_;
        }

        std::string Device::get_info(cl_device_info info)
        {
            std::size_t info_size = 0;
            clGetDeviceInfo(device_id_, info, 0, nullptr, &info_size);

            std::vector<char> buffer(info_size);
            clGetDeviceInfo(device_id_, info, info_size, buffer.data(), nullptr);

            return buffer.data();
        }
    }
}
