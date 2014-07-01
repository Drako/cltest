#ifndef CLPLATFORMS_HXX
#define CLPLATFORMS_HXX

#include <memory>
#include <string>

#include <CL/cl.h>

namespace cl
{
    namespace detail
    {
        struct Platform;
        struct Platforms;
    }

    class Device;

    class Platform
    {
    public:
        Platform(cl_platform_id id);
        Platform(Platform &&) = default;
        Platform(Platform const & source);
        ~Platform();

        Platform & operator = (Platform &&) = default;
        Platform & operator = (Platform const & source);

        cl_platform_id id() const;
        std::string name() const;
        std::string vendor() const;
        std::string extensions() const;
        std::string version() const;
        std::string profile() const;

        int device_count() const;

    private:
        std::string get_info(cl_platform_info info);

        std::unique_ptr<detail::Platform> self;
    };

    class PlatformIterator;

    class Platforms
    {
    public:
        Platforms();
        Platforms(Platforms &&) = default;
        Platforms(Platforms const & source);
        ~Platforms();

        Platforms & operator = (Platforms &&) = default;
        Platforms & operator = (Platforms const & source);

        unsigned count() const;
        Platform * operator [] (unsigned index);
        Platform const * operator [] (unsigned index) const;

        PlatformIterator begin();
        PlatformIterator end();

    private:
        std::unique_ptr<detail::Platforms> self;
    };

    class PlatformIterator
    {
    public:
        PlatformIterator(Platforms * platforms = nullptr, unsigned index = 0);
        PlatformIterator(PlatformIterator const &) = default;
        PlatformIterator(PlatformIterator &&) = default;
        ~PlatformIterator() = default;

        PlatformIterator & operator = (PlatformIterator const &) = default;
        PlatformIterator & operator = (PlatformIterator &&) = default;

        bool operator == (PlatformIterator const & rhs) const;
        bool operator != (PlatformIterator const & rhs) const;

        PlatformIterator operator ++ (int);
        PlatformIterator & operator ++ ();

        Platform * operator * () const;

    private:
        Platforms * platforms;
        unsigned index;
    };
}

#endif // CLPLATFORMS_HXX
