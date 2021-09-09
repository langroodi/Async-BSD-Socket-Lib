#include "./network_socket.h"

namespace AsyncBsdSocketLib
{
    NetworkSocket::NetworkSocket(std::string ipAddress, uint16_t port) : mIpAddress{ipAddress},
                                                                         mPort{port},
                                                                         mDescriptor{-1}
    {
    }

    int NetworkSocket::Descriptor() const noexcept
    {
        return mDescriptor;
    }

    bool NetworkSocket::TrySetNonblock() noexcept
    {
        // Get the current flags
        int _flags = fcntl(mDescriptor, F_GETFL, 0);
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

    bool NetworkSocket::TryClose() noexcept
    {
        int _returnCode = close(mDescriptor);
        bool _result = _returnCode > -1;

        return _result;
    }

    NetworkSocket::~NetworkSocket() noexcept
    {
        TryClose();
    }
}