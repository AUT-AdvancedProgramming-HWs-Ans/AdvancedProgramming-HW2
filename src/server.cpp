#include "server.h"
#include "client.h"

std::shared_ptr<Client> Server::add_client(std::string id)
{
    /**
     * @brief Add a new client to the server
     *
     * @param id The id of the client
     * @return std::shared_ptr<Client>
     */

    // Check if the client already exists
    for (auto clientItr { clients.begin() }; clientItr != clients.end(); ++clientItr) {
        if (clientItr->first->get_id() == id) {

            // Creating a random number engine
            std::random_device rd;

            // Creating a random number generator
            std::mt19937 gen(rd());

            // Creating a uniform distribution
            std::uniform_real_distribution<double> dist(1000, 9999);

            // Adding a 4 digit random number to the id and creating a new client
            std::shared_ptr<Client> newClient {
                std::make_shared<Client>(id + std::to_string(static_cast<int>(dist(gen))),
                    *this)
            };

            // Adding the client to the server
            clients.insert({ newClient, 5 });

            std::cout << newClient->get_id() << std::endl;
            std::cout << newClient << std::endl;

            // Returning the client
            return newClient;
        }
    }

    // Creating a new client that does not exist
    std::shared_ptr<Client> newClient = std::make_shared<Client>(id, *this);

    // Adding the client to the server
    clients.insert({ newClient, 5 });

    std::cout << newClient->get_id() << std::endl;
    std::cout << newClient << std::endl;

    // Returning the client
    return newClient;
}

std::shared_ptr<Client> Server::get_client(std::string id) const
{
    /**
     * @brief Get the client object
     *
     * @param id The id of the client
     * @return std::shared_ptr<Client>
     */

    // Check if the client exists
    for (auto clientItr { clients.begin() }; clientItr != clients.end(); ++clientItr) {
        if (clientItr->first->get_id() == id) {
            return clientItr->first;
        }
    }

    // Return nullptr if the client does not exist
    return nullptr;
}

double Server::get_wallet(std::string id) const
{
    /**
     * @brief Get the wallet double
     *
     * @param id The id of the client
     * @return double
     */

    // Check if the client exists
    for (auto clientItr { clients.begin() }; clientItr != clients.end(); ++clientItr) {
        if (clientItr->first->get_id() == id) {
            return clientItr->second;
        }
    }

    // Return 0 if the client does not exist
    return 0;
}

void show_wallets(const Server& server)
{
    // Interpret casting the server object to a const reference
    auto* serverPtr { reinterpret_cast<const std::map<std::shared_ptr<Client>, double>*>(&server) };

    for (const auto& clientItr : *serverPtr)
        std::cout << clientItr.first->get_id() << " : " << clientItr.second << std::endl;
}
