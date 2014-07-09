#include "ClPlatforms.hxx"
#include "ClDevices.hxx"

#include <vector>

namespace cl
{
    namespace detail
    {
        struct Platform
        {
            cl_platform_id id;
            std::string name;
            std::string vendor;
            std::string extensions;
            std::string version;
            std::string profile;

            std::vector< ::cl::Device> devices;
        };

        struct Platforms
        {
            std::vector< ::cl::Platform> platforms;
        };

        // only a stub... real version is in ClDevices.cxx
        struct Device {};
    }

    Platform::Platform(cl_platform_id id)
        : self(new detail::Platform)
    {
        self->id = id;
        self->name = get_info(CL_PLATFORM_NAME);
        self->vendor = get_info(CL_PLATFORM_VENDOR);
        self->extensions = get_info(CL_PLATFORM_EXTENSIONS);
        self->version = get_info(CL_PLATFORM_VERSION);
        self->profile = get_info(CL_PLATFORM_PROFILE);
        load_devices();
    }

    Platform::Platform(Platform const & source)
        : self(new detail::Platform(*(source.self.get())))
    {
    }

    Platform::~Platform()
    {
    }

    Platform & Platform::operator = (Platform const & source)
    {
        self.reset(new detail::Platform(*(source.self.get())));
        return (*this);
    }

    cl_platform_id Platform::id() const
    {
        return self->id;
    }

    std::string Platform::name() const
    {
        return self->name;
    }

    std::string Platform::vendor() const
    {
        return self->vendor;
    }

    std::string Platform::extensions() const
    {
        return self->extensions;
    }

    std::string Platform::version() const
    {
        return self->version;
    }

    std::string Platform::profile() const
    {
        return self->profile;
    }

    unsigned Platform::device_count() const
    {
        return static_cast<unsigned>(self->devices.size());
    }

    Device const * Platform::device(unsigned index) const
    {
        if (index >= device_count())
            return nullptr;
        return &(self->devices[index]);
    }

    std::string Platform::get_info(cl_platform_info info)
    {
        std::size_t info_size = 0;
        clGetPlatformInfo(self->id, info, 0, nullptr, &info_size);

        std::vector<char> buffer(info_size);
        clGetPlatformInfo(self->id, info, info_size, buffer.data(), nullptr);

        return buffer.data();
    }

    void Platform::load_devices()
    {
        cl_uint devices = 0;
        clGetDeviceIDs(self->id, CL_DEVICE_TYPE_ALL, 0, nullptr, &devices);

        if (devices == 0)
            return;

        std::vector<cl_device_id> ids;
        clGetDeviceIDs(self->id, CL_DEVICE_TYPE_ALL, devices, ids.data(), nullptr);

        self->devices.reserve(devices);
        for (auto id : ids)
            self->devices.push_back(Device(this, id));
    }

    Platforms::Platforms()
        : self(new detail::Platforms)
    {
        cl_uint platform_count = 0;
        clGetPlatformIDs(0, nullptr, &platform_count);

        if (platform_count == 0)
            return;

        std::vector<cl_platform_id> ids(platform_count);
        clGetPlatformIDs(platform_count, ids.data(), nullptr);

        self->platforms.reserve(platform_count);
        for (auto id : ids)
            self->platforms.push_back(Platform(id));
    }

    Platforms::Platforms(Platforms const & source)
        : self(new detail::Platforms(*(source.self.get())))
    {
    }

    Platforms::~Platforms()
    {
    }

    Platforms & Platforms::operator = (Platforms const & source)
    {
        self.reset(new detail::Platforms(*(source.self.get())));
        return (*this);
    }

    unsigned Platforms::count() const
    {
        return static_cast<unsigned>(self->platforms.size());
    }

    Platform * Platforms::operator [] (unsigned index)
    {
        if (index >= count())
            return nullptr;
        return &(self->platforms[index]);
    }

    Platform const * Platforms::operator [] (unsigned index) const
    {
        if (index >= count())
            return nullptr;
        return &(self->platforms[index]);
    }

    PlatformIterator Platforms::begin()
    {
        return PlatformIterator(this);
    }

    PlatformIterator Platforms::end()
    {
        return PlatformIterator();
    }

    PlatformIterator::PlatformIterator(Platforms * platforms /* = nullptr */, unsigned index /* = 0 */)
        : platforms(platforms)
        , index(index)
    {
        if (!platforms || index >= platforms->count())
        {
            this->platforms = nullptr;
            this->index = 0;
        }
    }

    bool PlatformIterator::operator == (PlatformIterator const & rhs) const
    {
        return (platforms == rhs.platforms && index == rhs.index);
    }

    bool PlatformIterator::operator != (PlatformIterator const & rhs) const
    {
        return (platforms != rhs.platforms || index != rhs.index);
    }

    PlatformIterator PlatformIterator::operator ++ (int)
    {
        PlatformIterator old(*this);
        if (platforms && (index < platforms->count()))
        {
            if (++index == platforms->count())
            {
                platforms = nullptr;
                index = 0;
            }
        }
        return old;
    }

    PlatformIterator & PlatformIterator::operator ++ ()
    {
        if (platforms && (index < platforms->count()))
        {
            if (++index == platforms->count())
            {
                platforms = nullptr;
                index = 0;
            }
        }
        return (*this);
    }

    Platform * PlatformIterator::operator * () const
    {
        if (!platforms || index > platforms->count())
            return nullptr;
        return (*platforms)[index];
    }
}
