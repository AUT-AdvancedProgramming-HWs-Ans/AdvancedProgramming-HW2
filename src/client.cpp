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
     * @return std::string
     */
    return id;
} // end of Client::get_id

std::string Client::get_publickey() const
{
    /**
     * @brief Get the publickey string
     * @return std::string
     */
    return public_key;
} // end of Client::get_publickey

double Client::get_wallet() const
{
    /**
     * @brief Get the wallet double
     * @return double
     */
    return server->get_wallet(id);
} // end of Client::get_wallet

std::string Client::sign(std::string txt) const
{
    /**
     * @brief Sign the string
     * @param txt The string to sign
     * @return std::string
     */
    return crypto::signMessage(private_key, txt);
} // end of Client::sign