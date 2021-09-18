#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "./tcp_listener.h"

namespace AsyncBsdSocketLib
{
    TcpListener::TcpListener(uint16_t port) : NetworkSocket("0.0.0.0", port),
                                              mConnection{-1}
    {
    }

    TcpListener::TcpListener(
        std::string ipAddress, uint16_t port) : NetworkSocket(ipAddress, port),
                                                mConnection{-1}
    {
    }

    int TcpListener::Connection() const noexcept
    {
        return mConnection;
    }

    bool TcpListener::TrySetup() noexcept
    {
        //! \remark Creating socket file descriptor
        mDescriptor = socket(AF_INET, SOCK_STREAM, 0);

        bool _result = (mDescriptor >= 0);

        if (_result)
        {
            // Option value
            int _opt = 1;
            // Configuring socket option for reusing the port
            _result =
                (setsockopt(
                     mDescriptor,
                     SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                     &_opt,
                     sizeof(_opt)) == 0);

            if (_result)
            {
                mAddress.sin_addr.s_addr = inet_addr(mIpAddress.c_str());
                mAddress.sin_family = AF_INET;
                mAddress.sin_port = htons(mPort);

                //! \remark Binding the socket to the port
                _result =
                    (bind(
                         mDescriptor,
                         (struct sockaddr *)&mAddress,
                         sizeof(mAddress)) == 0);

                if (_result)
                {
                    _result = (listen(mDescriptor, cBacklog) == 0);
                }
            }
        }

        return _result;
    }

    bool TcpListener::TryAccept() noexcept
    {
        int _addressLength = sizeof(mAddress);

        mConnection =
            accept(
                mDescriptor,
                (struct sockaddr *)&mAddress,
                (socklen_t *)&_addressLength);

        bool _result = (mConnection >= 0);

        return _result;
    }

    template <std::size_t N>
    ssize_t TcpListener::Send(const std::array<uint8_t, N> &buffer) const noexcept
    {
        bool _result =
            send(
                mConnection,
                buffer.data,
                N,
                MSG_NOSIGNAL);

        return _result;
    }

    template <std::size_t N>
    ssize_t TcpListener::Receive(std::array<uint8_t, N> &buffer) const noexcept
    {
        ssize_t _result = recv(mConnection, buffer.data, N, 0);

        return _result;
    }

    bool TcpListener::TryMakeConnectionNonblock() noexcept
    {
        // Check the connection validity
        if (mConnection == -1)
        {
            return false;
        }

        // Get the current flags
        int _flags = fcntl(mConnection, F_GETFL, 0);
        if (_flags == -1)
        {
            return false;
        }

        // Add the non-blocking flag
        _flags |= O_NONBLOCK;

        // Set back the flags
        int _returnCode = fcntl(mDescriptor, F_SETFL, _flags);
        bool _result = (_returnCode != -1);

        return _result;
    }
}