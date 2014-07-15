#include "ClPlatform_Impl.hxx"
#include "ClDevice_Impl.hxx"
#include "ClContext_Impl.hxx"

namespace cl
{
    namespace impl
    {
        Platform::Platform(cl_platform_id id)
            : id_(id)
            , name_(get_info(CL_PLATFORM_NAME))
            , vendor_(get_info(CL_PLATFORM_VENDOR))
            , extensions_(get_info(CL_PLATFORM_EXTENSIONS))
            , version_(get_info(CL_PLATFORM_VERSION))
            , profile_(get_info(CL_PLATFORM_PROFILE))
        {
            load_devices();
        }

        std::string Platform::name() const
        {
            return name_;
        }

        std::string Platform::vendor() const
        {
            return vendor_;
        }

        std::string Platform::extensions() const
        {
            return extensions_;
        }

        std::string Platform::version() const
        {
            return version_;
        }

        std::string Platform::profile() const
        {
            return profile_;
        }

        unsigned Platform::device_count() const
        {
            return devices_.size();
        }

        Reference< ::cl::Device> Platform::device(unsigned index) const
        {
            return make_ref< ::cl::Device, ::cl::impl::Device>(id_, devices_[index]);
        }

        Reference< ::cl::Context> Platform::create_context() const
        {
            return make_ref< ::cl::Context, ::cl::impl::Context>(id_, devices_);
        }

        std::string Platform::get_info(cl_platform_info info)
        {
            std::size_t info_size = 0;
            clGetPlatformInfo(id_, info, 0, nullptr, &info_size);

            std::vector<char> buffer(info_size);
            clGetPlatformInfo(id_, info, info_size, buffer.data(), nullptr);

            return buffer.data();
        }

        void Platform::load_devices()
        {
            cl_uint device_count = 0;
            clGetDeviceIDs(id_, CL_DEVICE_TYPE_ALL, 0, nullptr, &device_count);

            if (device_count == 0)
                return;

            devices_.resize(device_count);
            clGetDeviceIDs(id_, CL_DEVICE_TYPE_ALL, device_count, devices_.data(), nullptr);
        }
    }
}
