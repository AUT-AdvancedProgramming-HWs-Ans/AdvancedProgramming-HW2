
#include <gtest/gtest.h>
#include <iostream>
// #include "client.h"
#include "server.h"

int main(int argc, char** argv)
{
    if (false) // make false to run unit-tests
    {
        Server server;
        auto bryan1 { server.add_client("bryan") };
        auto bryan2 { server.add_client("bryan") };
        auto bryan3 { server.add_client("bryan") };

        show_wallets(server);
        // std::cout<<"bryan1->get_id(): "<<bryan1->get_id()<<std::endl;

    } else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret { RUN_ALL_TESTS() };
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}