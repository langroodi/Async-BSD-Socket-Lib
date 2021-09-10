#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <array>
#include <stdexcept>
#include "./network_socket.h"

namespace AsyncBsdSocketLib
{
    /// @brief TCP client to connect to a TcpListener
    /// @see TcpListener
    class TcpClient : public NetworkSocket
    {
    private:
        bool mIsConnected;
    
    public:
        TcpClient() = delete;

        /// @brief Constructor
        /// @param ipAddress Server IP address
        /// @param port Server port number
        TcpClient(std::string ipAddress, uint16_t port);

        bool TrySetup() noexcept override;

        /// @brief Inidicates whether the client is connected or not
        /// @returns True if the client is connected; otherwise false
        bool IsConnected() const noexcept;

        /// @brief Try to connect to the server
        /// @returns True if the client is successfully connected; otherwise false
        bool TryConnect() noexcept;

        /// @brief Try to send a byte array to the server
        /// @tparam N Send buffer size
        /// @param buffer Send buffer byte array
        /// @returns True if the sending was successful; otherwise false
        template <std::size_t N>
        bool TrySend(const std::array<uint8_t, N> &buffer) const noexcept;

        /// @brief Try to receive a byte array from the server
        /// @tparam N Receive buffer size
        /// @param buffer Receive buffer byte array
        /// @returns True if the receiving was successful; otherwise false
        template <std::size_t N>
        bool TryReceive(std::array<uint8_t, N> &buffer) const noexcept;
    };
}

#endif