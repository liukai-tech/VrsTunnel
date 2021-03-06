#ifndef VRS_TUNNEL_TCP_SERVER_
#define VRS_TUNNEL_TCP_SERVER_

#include <memory>
#include <thread>
#include <atomic>
#include <sys/socket.h>

#include "tcp_client.hpp"

#include <iostream>

namespace VrsTunnel::Ntrip
{
    class tcp_server
    {
    public:
        tcp_server() = default;
        ~tcp_server();
        tcp_server(const tcp_server&) = delete;
        tcp_server(tcp_server&&) = delete;
        tcp_server& operator=(const tcp_server&) = delete;
        tcp_server& operator=(tcp_server&&) = delete;
       
        template<typename connect_listen>
        [[nodiscard]] bool start(int port, connect_listen& listener);

        void stop();
        
    private:
        int m_port{-1};
        std::thread m_thread_v4{};
        std::atomic<bool> stop_required{true};
        int m_servfd4{-1};
        struct sockaddr_in m_addr4{};
        void close(int& servfd);

        template<typename connect_listen>
        void run_accepting(struct sockaddr* addr, int sockfd, connect_listen& listener);

    };

    
}

#endif /* VRS_TUNNEL_TCP_SERVER_ */