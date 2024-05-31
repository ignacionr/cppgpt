#include <iostream>
#include <cstdlib> // for getenv
#include "../include/cppgpt.hpp"

int main()
{
    // Read API key from environment variable
    const char *env_api_key = std::getenv("GROQ_API_KEY");
    if (env_api_key == nullptr)
    {
        std::cerr << "Error: GROQ_API_KEY environment variable not set." << std::endl;
        return 1;
    }
    std::string api_key = env_api_key;
    nlohmann::json response;
    try
    {

        // Initialize cppgpt with the API key from the environment variable
        ignacionr::cppgpt myGpt(api_key, ignacionr::cppgpt::groq_base);

        // Send a message and receive a reply
        response = myGpt.sendMessage("Hello, how are you?", "user", "llama3-70b-8192");

        // Access and print GPT's reply
        std::string gpt_reply = response["choices"][0]["message"]["content"];
        std::cout << "GPT replied: " << gpt_reply << std::endl;
    }
    catch(std::exception & ex)
    {

        std::cerr << "Problem using the response " << response.dump() << " - " << ex.what() << std::endl;
    }
    return 0;
}
