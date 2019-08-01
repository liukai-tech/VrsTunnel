#ifndef VRSTUNNEL_NTRIP_NTRIP_CLIENT_
#define VRSTUNNEL_NTRIP_NTRIP_CLIENT_

#include <string>
#include <vector>
#include <thread>
#include <variant>
#include <chrono>

#include "location.hpp"
#include "tcp_client.hpp"
#include "async_io.hpp"

namespace VrsTunnel::Ntrip
{
    struct MountPoint
    {
        std::string Raw;
        location Reference;
        std::string Name;
    };
    
    class NtripClient
    {
    private:
        std::string getName(std::string_view line);
        location getReference(std::string_view line);

    public:
        NtripClient() = default;
        ~NtripClient() = default;

        std::variant<std::vector<MountPoint>, io_status>
        getMountPoints(std::string address, int tcpPort, 
            std::string name = std::string(), std::string password = std::string());

        bool hasTableEnding(std::string_view data);

        std::vector<MountPoint> parseTable(std::string_view data);
    };

}

#endif