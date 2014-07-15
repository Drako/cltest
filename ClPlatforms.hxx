#ifndef CLPLATFORMS_HXX
#define CLPLATFORMS_HXX

#include "ClReference.hxx"

#include <string>

#include <CL/cl.h>

namespace cl
{
    struct Device;
    struct Context;

    struct Platform
    {
        virtual ~Platform() = default;

        virtual std::string name() const = 0;
        virtual std::string vendor() const = 0;
        virtual std::string extensions() const = 0;
        virtual std::string version() const = 0;
        virtual std::string profile() const = 0;

        virtual unsigned device_count() const = 0;
        virtual Reference<Device> device(unsigned index) const = 0;

        virtual Reference<Context> create_context() const = 0;
    };

    class PlatformIterator;

    struct Platforms
    {
    public:
        virtual ~Platforms() = default;

        virtual unsigned count() const = 0;
        virtual Reference<Platform> operator [] (unsigned index) const = 0;

        virtual PlatformIterator begin() const = 0;
        virtual PlatformIterator end() const = 0;
    };

    Reference<Platforms> get_platforms();

    class PlatformIterator
    {
    public:
        PlatformIterator(Platforms const * platforms = nullptr, unsigned index = 0);
        PlatformIterator(PlatformIterator const &) = default;
        PlatformIterator(PlatformIterator &&) = default;
        ~PlatformIterator() = default;

        PlatformIterator & operator = (PlatformIterator const &) = default;
        PlatformIterator & operator = (PlatformIterator &&) = default;

        bool operator == (PlatformIterator const & rhs) const;
        bool operator != (PlatformIterator const & rhs) const;

        PlatformIterator operator ++ (int);
        PlatformIterator & operator ++ ();

        Reference<Platform> operator * () const;

    private:
        Platforms const * platforms;
        unsigned index;
    };
}

#endif // CLPLATFORMS_HXX
