#include "client.h"

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
// double Client::get_wallet()
// {
//     /**
//      * @brief Get the wallet double
//      * @return double
//      */
// }
