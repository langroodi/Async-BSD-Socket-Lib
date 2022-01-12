#include <fcntl.h>
#include "../include/asyncbsdsocket/fifo_receiver.h"

namespace AsyncBsdSocketLib
{

    FifoReceiver::FifoReceiver(std::string pathname) : mPathname{pathname}
    {
    }

    int FifoReceiver::Connection() const noexcept
    {
        return FileDescriptor;
    }

    bool FifoReceiver::TrySetup() noexcept
    {
        // rw- rw- rw-
        const mode_t cMode = 0666;
        bool _result = mkfifo(mPathname.c_str(), cMode);

        // If got 'bad file description' error for the first time, try once.
        if (errno == EBADF)
        {
            _result = mkfifo(mPathname.c_str(), cMode);
        }

        if (_result)
        {
            FileDescriptor = open(mPathname.c_str(), O_RDONLY | O_NONBLOCK);
            _result = (FileDescriptor >= 0);
        }

        return _result;
    }
}