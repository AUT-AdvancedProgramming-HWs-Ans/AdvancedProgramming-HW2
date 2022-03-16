// Adding the libraries
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
    if (get_client(id) != nullptr) {

        // True random number generator to obtain a seed (slow)
        std::random_device seeder;

        // Efficient pseudo-random generator
        std::default_random_engine generator { seeder() };
        // std::mt19937 generator { seeder() };

        // Creating a uniform distribution
        std::uniform_real_distribution<double> dist(1000, 9999);

        // Adding a 4 digit random number to the id and creating a new client
        std::shared_ptr<Client> newClient {
            std::make_shared<Client>(id + std::to_string(static_cast<size_t>(dist(generator))),
                *this)
        };

        // Adding the client to the server
        clients.insert({ newClient, 5 });

        std::cout << newClient->get_id() << std::endl;
        std::cout << newClient << std::endl;

        // Returning the client
        return newClient;
    }

    // Creating a new client that does not exist
    std::shared_ptr<Client> newClient = std::make_shared<Client>(id, *this);

    // Adding the client to the server
    clients.insert({ newClient, 5 });

    std::cout << newClient->get_id() << std::endl;
    std::cout << newClient << std::endl;

    // Returning the client
    return newClient;

} // end of Server::add_client

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

} // end of Server::get_client

double Server::get_wallet(std::string id) const
{
    /**
     * @brief Get the wallet double
     *
     * @param id The id of the client
     * @return double
     */

    std::shared_ptr<Client> client { get_client(id) };

    // Check if the client exists
    if (client == nullptr) {
        // Return 0 if the client does not exist
        return 0;
    }
    // Return the wallet of the client
    return clients.find(client)->second;

} // end of Server::get_wallet

void show_wallets(const Server& server)
{
    /**
     * @brief Show the wallets of all the clients
     *
     * @param server The server object
     */

    // Reinnterpret casting the server object to a const reference
    auto* serverPtr { reinterpret_cast<const std::map<std::shared_ptr<Client>, double>*>(&server) };

    for (const auto& clientItr : *serverPtr)
        std::cout << clientItr.first->get_id() << " : " << clientItr.second << std::endl;

} // end of show_wallets

bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value)
{

    /**
     * @brief Parse the transaction
     *
     * @param trx The transaction
     * @param sender The sender of the transaction
     * @param receiver The receiver of the transaction
     * @param value The value of the transaction
     * @return bool
     */

    std::stringstream trxStringStreamed(trx);
    std::string trxElements[3] {};

    // Splitting the transaction into 3 elements
    for (size_t i {}; std::getline(trxStringStreamed, trxElements[i], '-'); ++i) { }

    // Check if the transaction string is valid
    if (trxElements[0] == "" || trxElements[1] == "" || trxElements[2] == "") {
        throw std::runtime_error("trx string is not in the correct format");
    }

    // size_t i {};
    // for (i; std::getline(trxStringStreamed, trxElements[i], '-')&&i<3; ++i) { }
    // // Check if the transaction string is valid
    // if (i != 3) {
    //     throw std::runtime_error("trx string is not in the correct format");
    // }
    // if(stod(trxElements[2]) <= 0) {
    //     throw std::runtime_error("trx value is not valid");
    // }

    sender = trxElements[0];
    receiver = trxElements[1];
    value = std::stod(trxElements[2]);

    return true;

} // end of Server::parse_trx

bool Server::add_pending_trx(std::string trx, std::string signature) const
{
    /**
     * @brief Add a pending transaction
     *
     * @param trx The transaction
     * @param signature The signature of the transaction
     * @return bool
     */

    std::string sender {}, receiver {};
    double value {};

    // Check if the transaction is valid
    if (parse_trx(trx, sender, receiver, value)) {

        // Check if the sender exists
        if (get_client(sender) == nullptr) {
            std::cout << "sender does not exist" << std::endl;
            return false;
        }

        // Check if the receiver exists
        if (get_client(receiver) == nullptr) {
            std::cout << "receiver does not exist" << std::endl;
            return false;
        }

        // Check if the sender has enough money
        if (get_wallet(sender) < value) {
            std::cout << "sender does not have enough money" << std::endl;
            return false;
        }

        // Check if the signature is valid
        if (crypto::verifySignature(
                get_client(sender)->get_publickey(),
                trx,
                signature)) {

            // Add the transaction to the pending transactions
            pending_trxs.push_back(trx);

            return true;
        } else {
            std::cout << "signature is not valid" << std::endl;
            return false;
        }

        return false;
    }

    return false;

} // end of Server::add_pending_trx

size_t Server::mine()
{
    /**
     * @brief Mine the pending transactions
     *
     * @return size_t
     */

    std::string mempool {};

    // Get the mempool
    for (const auto& trxItr : pending_trxs) {
        mempool += trxItr;
    }

    // Get the hash of the mempool
    while (true) {

        for (auto clientItr { clients.begin() }; clientItr != clients.end(); ++clientItr) {

            size_t nonce { clientItr->first->generate_nonce() };

            size_t isFound { ((crypto::sha256(mempool + std::to_string(nonce))).substr(0, 10)).find("000") };

            if (isFound != std::string::npos) {
                clients[clientItr->first] += 6.25;

                std::cout << "Mined a block" << std::endl;
                std::cout << "Miner:" << clientItr->first->get_id() << std::endl;
                std::cout << "Nonce:" << nonce << std::endl;
                std::cout << "Block:" << mempool << std::endl;

                for (const auto& trxItr : pending_trxs) {

                    std::string sender {}, receiver {};
                    double value {};

                    parse_trx(trxItr, sender, receiver, value);

                    clients[get_client(sender)] -= value;
                    clients[get_client(receiver)] += value;
                }

                pending_trxs.clear();
                return nonce;
            }
        }
    }
}
