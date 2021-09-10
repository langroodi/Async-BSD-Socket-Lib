#ifndef TCP_LISTENER_H
#define TCP_LISTENER_H

#include <array>
#include "./network_socket.h"

namespace AsyncBsdSocketLib
{
    /// @brief TCP listener (server) to accept a TcpClient
    /// @see TcpClient
    class TcpListener : public NetworkSocket
    {
    private:
        int mConnection;
    
    public:
        TcpListener() = delete;

        /// @brief Constructor to listen on any IP address
        /// @param port Listen port number
        TcpListener(uint16_t port);

        /// @brief Constructor
        /// @param ipAddress Listen IP address
        /// @param port Listen port number
        TcpListener(std::string ipAddress, uint16_t port);

        bool TrySetup() noexcept override;

        /// @brief Connection descriptor
        /// @returns A non-negative value if there is a valid connection; otherwise -1
        int Connection() const noexcept;

        /// @brief Try to accept a client to form a connection
        /// @returns True if the client is successfully accepted; otherwise false
        bool TryAccept() noexcept;

        /// @brief Try to send a byte array to the connected client
        /// @tparam N Send buffer size
        /// @param buffer Send buffer byte array
        /// @returns True if the sending was successful; otherwise false
        template <std::size_t N>
        bool TrySend(const std::array<uint8_t, N> &buffer) const noexcept;

        /// @brief Try to receive a byte array from the connected client
        /// @tparam N Receive buffer size
        /// @param buffer Receive buffer byte array
        /// @returns True if the receiving was successful; otherwise false
        template <std::size_t N>
        bool TryReceive(std::array<uint8_t, N> &buffer) const noexcept;
    };
}

#endif