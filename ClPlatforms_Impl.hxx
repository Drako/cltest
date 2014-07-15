#ifndef CLPLATFORMS_IMPL_HXX
#define CLPLATFORMS_IMPL_HXX

#include "ClPlatforms.hxx"

#include <vector>

#include <CL/cl.h>

namespace cl
{
    namespace impl
    {
        class Platforms
            : public ::cl::Platforms
        {
        public:
            Platforms();
            virtual ~Platforms() = default;

            virtual unsigned count() const;
            virtual Reference< ::cl::Platform> operator [] (unsigned index) const;

            virtual PlatformIterator begin() const;
            virtual PlatformIterator end() const;

        private:
            std::vector<cl_platform_id> platforms_;
        };
    }
}

#endif // CLPLATFORMS_IMPL_HXX
