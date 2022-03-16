/**
 * @file server.h
 * @author Erfan Rasti (erfanrasty@gmail.com)
 * @brief 
 * @version 1.0.1
 * @date 2022-03-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef SERVER_H
#define SERVER_H

// Adding the libraries
#include "client.h"
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <vector>

class Server {
public:
    Server() = default;
    std::shared_ptr<Client> add_client(std::string id);
    std::shared_ptr<Client> get_client(std::string id) const;
    double get_wallet(std::string id) const;
    static bool parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value);
    bool add_pending_trx(std::string trx, std::string signature) const;
    size_t mine();

private:
    std::map<std::shared_ptr<Client>, double> clients;
};

void show_wallets(const Server& server);

inline std::vector<std::string> pending_trxs;

#endif // SERVER_H