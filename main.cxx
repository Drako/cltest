#include "ClPlatforms.hxx"
#include "ClDevices.hxx"
#include "ClContexts.hxx"

#include <iostream>

int main()
{
    auto platforms = cl::get_platforms();

    std::cout << "Platforms: " << platforms->count() << "\n";
    for (auto platform : *platforms)
    {
        std::cout << "==============================================\n";
        std::cout << "Name:           " << platform->name() << "\n";
        std::cout << "Vendor:         " << platform->vendor() << "\n";
        std::cout << "OpenCL-Version: " << platform->version() << "\n";
        std::cout << "OpenCL-Profile: " << platform->profile() << "\n";
        std::cout << "Devices:        " << platform->device_count() << "\n";
        for (unsigned idx = 0; idx < platform->device_count(); ++idx)
        {
            auto device = platform->device(idx);
            std::cout << "----------------------------------------------\n";
            std::cout << "Name:           " << device->name() << "\n";
        }
    }

    auto context = (*platforms)[0]->create_context();

    return 0;
}
