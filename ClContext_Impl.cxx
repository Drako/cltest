#include "ClContext_Impl.hxx"

namespace cl
{
    namespace impl
    {
        Context::Context(cl_platform_id platform, std::vector<cl_device_id> const & devices)
        {
            cl_context_properties const context_properties[] =
            {
                CL_CONTEXT_PLATFORM, reinterpret_cast<cl_context_properties>(platform),
                0, 0
            };

            cl_int error = 0;
            context_ = clCreateContext(context_properties, devices.size(), devices.data(), nullptr, nullptr, &error);
        }

        Context::~Context()
        {
            clReleaseContext(context_);
        }
    }
}
