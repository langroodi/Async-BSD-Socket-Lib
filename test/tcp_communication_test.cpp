#include <gtest/gtest.h>
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
}