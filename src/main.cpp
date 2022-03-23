/**
 * @file main.cpp
 * @author Erfan Rasti (erfanrasty@gmail.com)
 * @brief
 * @version 1.0.2
 * @date 2022-03-24
 *
 * @copyright Copyright (c) 2022
 *
 */

// Adding the libraries
#include "client.h"
#include "server.h"
#include <gtest/gtest.h>
#include <iostream>

void show_pending_transactions()
{
    std::cout << std::string(20, '*') << std::endl;
    for (const auto& trx : pending_trxs)
        std::cout << trx << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}

int main(int argc, char** argv)
{
    if (false) // make false to run unit-tests
    {
        // Server server;
        // auto bryan1 { server.add_client("bryan") };
        // auto bryan2 { server.add_client("bryan") };
        // auto bryan3 { server.add_client("bryan") };

        // show_wallets(server);
        // std::cout<<"bryan1->get_id(): "<<bryan1->get_id()<<std::endl;

        // Server server {};
        // pending_trxs.clear();
        // auto bryan { server.add_client("bryan") };
        // auto clint { server.add_client("clint") };
        // auto sarah { server.add_client("sarah") };
        // EXPECT_TRUE(bryan->transfer_money("clint", 1));
        // EXPECT_TRUE(clint->transfer_money("sarah", 2.5));
        // EXPECT_TRUE(sarah->transfer_money("bryan", 0.5));
        // show_pending_transactions();

        // std::string sender {}, receiver {};
        // double value;
        // Server::parse_trx("sarah-clay--0.2", sender, receiver, value);

        // std::cout << "sender: " << sender << std::endl;
        // std::cout << "receiver: " << receiver << std::endl;
        // std::cout << "value: " << value << std::endl;

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