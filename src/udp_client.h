#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include <array>
#include <sys/socket.h>
#include "./network_socket.h"

namespace AsyncBsdSocketLib
{
    /// @brief UDP client which can play both client and listener roles
    class UdpClient : public NetworkSocket
    {
    private:
        std::string mNicIpAddress;
        bool mIsMulticast;

    public:
        UdpClient() = delete;

        /// @brief Unicast UDP socket constructor
        /// @param ipAddress Binding IP address
        /// @param port Binding port number
        UdpClient(std::string ipAddress, uint16_t port);

        /// @brief Multicast UDP socket constructor
        /// @param ipAddress Binding IP address
        /// @param port Binding port number
        /// @param nicIpAddress Multocast traffic network interface IP address
        UdpClient(std::string ipAddress, uint16_t port, std::string nicIpAddress);

        int Connection() const noexcept override;

        bool TrySetup() noexcept override;

        /// @brief Try to send a byte array to a destination
        /// @tparam N Send buffer size
        /// @param buffer Send buffer byte array
        /// @param ipAddress Destination IP address
        /// @param port Destination port number
        /// @returns True if the sending was successful; otherwise false
        template <std::size_t N>
        bool TrySend(
            const std::array<uint8_t, N> &buffer,
            std::string ipAddress,
            uint16_t port) const noexcept;

        /// @brief Try to receive a byte array from a source
        /// @tparam N Receive buffer size
        /// @param buffer Receive buffer byte array
        /// @param ipAddress Source IP address
        /// @param port Source port number
        /// @returns True if the receiving was successful; otherwise false
        template <std::size_t N>
        bool TryReceive(
            std::array<uint8_t, N> &buffer,
            std::string ipAddress,
            uint16_t port) const noexcept;
    };
}

#endif