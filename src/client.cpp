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
}
std::string Client::get_id() const
{
    /**
     * @brief Get the id string
     * @return std::string
     */
    return id;
}
std::string Client::get_publickey() const
{
    /**
     * @brief Get the publickey string
     * @return std::string
     */
    return public_key;
}

double Client::get_wallet() const
{
    /**
     * @brief Get the wallet double
     * @return double
     */
    return server->get_wallet(id);
}

std::string Client::sign(std::string txt) const
{
    /**
     * @brief Sign the string
     * @param txt The string to sign
     * @return std::string
     */
    return crypto::signMessage(private_key, txt);
}