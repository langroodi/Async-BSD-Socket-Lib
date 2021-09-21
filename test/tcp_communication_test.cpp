#include <gtest/gtest.h>
#include <algorithm>
#include <iterator>
#include "../src/tcp_client.h"
#include "../src/tcp_listener.h"

namespace AsyncBsdSocketLib
{
    class TcpCommunicationTest : public testing::Test
    {
    private:
        const std::string cLocalhost = "127.0.0.1";
        const uint16_t cPort = 8080;

    protected:
        TcpListener Server;
        TcpClient Client;

        TcpCommunicationTest() : Server(cLocalhost, cPort),
                                 Client(cLocalhost, cPort)
        {
        }

        void SetUp()
        {
            bool _succeed = Server.TrySetup();

            if (_succeed)
            {
                _succeed = Client.TrySetup();

                if (_succeed)
                {
                    _succeed = Client.TryConnect();

                    if (_succeed)
                    {
                        Server.TryAccept();
                    }
                }
            }
        }

        void TearDown()
        {
            Client.TryClose();
            Server.TryClose();
        }
    };

    TEST_F(TcpCommunicationTest, Connection)
    {
        EXPECT_TRUE(Client.IsConnected());
    }

    TEST_F(TcpCommunicationTest, ServerSendClientReceive)
    {
        const std::size_t cBufferSize = 16;

        const std::array<uint8_t, cBufferSize> _sendBuffer{
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

        bool _sent = Server.Send<cBufferSize>(_sendBuffer) > 0;
        EXPECT_TRUE(_sent);

        std::array<uint8_t, cBufferSize> _receiveBuffer;
        bool _received = Client.Receive<cBufferSize>(_receiveBuffer) > 0;
        EXPECT_TRUE(_received);

        bool _areEqual =
            std::equal(
                std::cbegin(_sendBuffer),
                std::cend(_sendBuffer),
                std::cbegin(_receiveBuffer));
        EXPECT_TRUE(_areEqual);
    }
}