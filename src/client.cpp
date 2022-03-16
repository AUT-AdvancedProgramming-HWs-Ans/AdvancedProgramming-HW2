/**
 * @file client.cpp
 * @author Erfan Rasti (erfanrasty@gmail.com)
 * @brief
 * @version 1.0.1
 * @date 2022-03-16
 *
 * @copyright Copyright (c) 2022
 *
 */

// Adding the libraries
#include "client.h"
#include "server.h"

Client::Client(std::string _id, const Server& _server)
    : id { _id }
    , server { &_server }
{
    /**
     * @brief Construct a new Client:: Client object
     *
     * @param _id The id of the client
     * @param _server The server object
     */

    std::cout << "An Object of Client class is created." << std::endl;

    crypto::generate_key(public_key, private_key);

} // end of Client::Client

std::string Client::get_id() const
{
    /**
     * @brief Get the id string
     *
     * @return std::string
     */
    return id;

} // end of Client::get_id

std::string Client::get_publickey() const
{
    /**
     * @brief Get the publickey string
     *
     * @return std::string
     */
    return public_key;

} // end of Client::get_publickey

double Client::get_wallet() const
{
    /**
     * @brief Get the wallet double
     *
     * @return double
     */
    return server->get_wallet(id);

} // end of Client::get_wallet

std::string Client::sign(std::string txt) const
{
    /**
     * @brief Sign the string
     *
     * @param txt The string to sign
     * @return std::string
     */
    return crypto::signMessage(private_key, txt);

} // end of Client::sign

bool Client::transfer_money(std::string receiver, double value)
{
    /**
     * @brief Transfer money to the receiver
     *
     * @param receiver The receiver id
     * @param value The value to transfer
     * @return bool
     */
    std::string trxString { id + '-' + receiver + '-' + std::to_string(value) };
    std::string signature { sign(trxString) };

    return server->add_pending_trx(trxString, signature);

} // end of Client::transfer_money

size_t Client::generate_nonce()
{
    /**
     * @brief Generate a nonce
     *
     * @return size_t
     */
    // True random number generator to obtain a seed (slow)
    std::random_device seeder;

    // Efficient pseudo-random generator
    std::default_random_engine generator { seeder() };
    // std::mt19937 generator { seeder() };

    // Creating a uniform distribution
    std::uniform_real_distribution<double> dist(0, 999999999);

    return static_cast<size_t>(dist(generator));

} // end of Client::generate_nonce
