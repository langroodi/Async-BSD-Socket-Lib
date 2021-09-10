#ifndef NETWORK_SOCKET_H
#define NETWORK_SOCKET_H

#include <string>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

namespace AsyncBsdSocketLib
{
    /// @brief TCP/IP network socket
    class NetworkSocket
    {
    private:
        const std::string mIpAddress;
        const uint16_t mPort;

    protected:
        /// @brief Socket descriptor
        int mDescriptor;

        /// @brief Constructor
        /// @param ipAddress Binding IPv4 address
        /// @param port Binding port number
        NetworkSocket(std::string ipAddress, uint16_t port);

    public:
        virtual ~NetworkSocket() noexcept;

        /// @brief Socket descriptor
        /// @returns A non-negative number if the socket has been already set up
        int Descriptor() const noexcept;

        /// @brief Try to setup the socket
        /// @returns True if the socket is successfully set up; otherwise false
        virtual bool TrySetup() noexcept = 0;

        /// @brief Try to close the socket
        /// @returns True if the socket closed successfully; otherwise false
        virtual bool TryClose() noexcept;
    };
}

#endif