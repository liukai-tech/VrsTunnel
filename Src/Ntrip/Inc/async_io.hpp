#ifndef ASYNCHRONOUS_INPUT_OUTPUT_
#define ASYNCHRONOUS_INPUT_OUTPUT_

#include <aio.h>
#include <memory>
#include <cstring>
#include <sys/ioctl.h>
#include <unistd.h>


namespace VrsTunnel::Ntrip
{
    enum class io_status { InProgress, Error, Success };

    class async_io
    {
        async_io(const async_io&)               = delete;
        async_io& operator=(const async_io&)    = delete;
        async_io(async_io&&)                    = delete;
        async_io& operator=(async_io&&)         = delete;

        // control block to ckeck transmission status
        struct aiocb m_read_cb { 0 };
        std::unique_ptr<char[]> m_data;

        public:
        async_io(int sockfd) noexcept;
        [[nodiscard]] io_status check() noexcept;
        [[nodiscard]] io_status write(const char* data, int size);
        int available() noexcept;
        std::unique_ptr<char[]> read(int size);
        ssize_t end() noexcept;
    };
};

#endif /* ASYNCHRONOUS_INPUT_OUTPUT_ */