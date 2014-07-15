#ifndef CLCONTEXT_IMPL_HXX
#define CLCONTEXT_IMPL_HXX

#include "ClContexts.hxx"

#include <vector>

#include <CL/cl.h>

namespace cl
{
    namespace impl
    {
        class Context
            : public ::cl::Context
        {
        public:
            Context(cl_platform_id platform, std::vector<cl_device_id> const & devices);
            virtual ~Context();

        private:
            cl_context context_;
        };
    }
}

#endif // CLCONTEXT_IMPL_HXX
