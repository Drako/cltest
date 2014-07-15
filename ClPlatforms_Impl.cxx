#include "ClPlatforms_Impl.hxx"
#include "ClPlatform_Impl.hxx"

namespace cl
{
    namespace impl
    {
        Platforms::Platforms()
        {
            cl_uint platform_count = 0;
            clGetPlatformIDs(0, nullptr, &platform_count);

            if (platform_count == 0)
                return;

            platforms_.resize(platform_count);
            clGetPlatformIDs(platform_count, platforms_.data(), nullptr);
        }

        PlatformIterator Platforms::end() const
        {
            return PlatformIterator();
        }

        PlatformIterator Platforms::begin() const
        {
            return PlatformIterator(this);
        }

        Reference< ::cl::Platform> Platforms::operator [](unsigned index) const
        {
            return make_ref< ::cl::Platform, ::cl::impl::Platform>(platforms_[index]);
        }

        unsigned Platforms::count() const
        {
            return platforms_.size();
        }
    }

    Reference<Platforms> get_platforms()
    {
        return make_ref<Platforms, impl::Platforms>();
    }
}
