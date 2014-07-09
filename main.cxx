#include "ClPlatforms.hxx"

#include <iostream>

int main()
{
    cl::Platforms platforms;

    std::cout << "Platforms: " << platforms.count() << "\n";
    for (auto platform : platforms)
    {
        std::cout << "==============================================\n";
        std::cout << "Name:           " << platform->name() << "\n";
        std::cout << "Vendor:         " << platform->vendor() << "\n";
        std::cout << "OpenCL-Version: " << platform->version() << "\n";
        std::cout << "OpenCL-Profile: " << platform->profile() << "\n";
        std::cout << "Devices:        " << platform->device_count() << "\n";
    }

    return 0;
}
