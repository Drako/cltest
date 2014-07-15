#ifndef CLPLATFORM_IMPL_HXX
#define CLPLATFORM_IMPL_HXX

#include "ClPlatforms.hxx"

#include <vector>

#include <CL/cl.h>

namespace cl
{
    namespace impl
    {
        class Platform
            : public ::cl::Platform
        {
        public:
            Platform(cl_platform_id id);
            virtual ~Platform() = default;

            virtual std::string name() const;
            virtual std::string vendor() const;
            virtual std::string extensions() const;
            virtual std::string version() const;
            virtual std::string profile() const;

            virtual unsigned device_count() const;
            virtual Reference< ::cl::Device> device(unsigned index) const;

            virtual Reference< ::cl::Context> create_context() const;

        protected:
            cl_platform_id id_;
            std::string name_;
            std::string vendor_;
            std::string extensions_;
            std::string version_;
            std::string profile_;

            std::vector<cl_device_id> devices_;

        private:
            std::string get_info(cl_platform_info info);
            void load_devices();
        };
    }
}

#endif // CLPLATFORM_IMPL_HXX
