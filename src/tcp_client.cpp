#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./tcp_client.h"

namespace AsyncBsdSocketLib
{
    TcpClient::TcpClient(
        std::string ipAddress, uint16_t port) : NetworkSocket(ipAddress, port),
                                                mIsConnected{false}
    {
    }

    int TcpClient::Connection() const noexcept
    {
        return mDescriptor;
    }

    bool TcpClient::IsConnected() const noexcept
    {
        return mIsConnected;
    }

    bool TcpClient::TrySetup() noexcept
    {
        mDescriptor = socket(AF_INET, SOCK_STREAM, 0);

        bool _result = (mDescriptor >= 0);

        if (_result)
        {
            mAddress.sin_addr.s_addr = inet_addr(mIpAddress.c_str());
            mAddress.sin_family = AF_INET;
            mAddress.sin_port = htons(mPort);
        }

        return _result;
    }

    bool TcpClient::TryConnect() noexcept
    {
        mIsConnected = (connect(
                            mDescriptor,
                            (struct sockaddr *)&mAddress,
                            sizeof(mAddress)) == 0);

        return mIsConnected;
    }

    template <std::size_t N>
    ssize_t TcpClient::Send(const std::array<uint8_t, N> &buffer) const noexcept
    {
        bool _result =
            send(
                mDescriptor,
                buffer.data,
                N,
                MSG_NOSIGNAL);

        return _result;
    }

    template <std::size_t N>
    ssize_t TcpClient::Receive(std::array<uint8_t, N> &buffer) const noexcept
    {
        std::string _result;
        ssize_t _result = recv(mDescriptor, buffer.data, N, 0);

        return _result;
    }
}