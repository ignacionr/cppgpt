#include <iostream>
#include <cstdlib> // for getenv
#include "../include/cppgpt.hpp"
#include "../include/cppollama.hpp"

int main()
{
    #ifdef CHATGPT
    // Read API key from environment variable
    const char *env_api_key = std::getenv("OPENAI_KEY");
    if (env_api_key == nullptr)
    {
        std::cerr << "Error: OPENAI_KEY environment variable not set." << std::endl;
        return 1;
    }
    std::string api_key = env_api_key;
    // Initialize cppgpt with the API key from the environment variable
    ignacionr::cppgpt ai(api_key);
    #else
    // Initialize cppgpt with the local Ollama instance URL
    ignacionr::cppollama ai("http://host.docker.internal:11434");
    #endif

    // ignacionr::cppgpt myGpt(api_key, ignacionr::cppgpt::open_ai_base);

    // Send a message and receive a reply
    auto response = ai.sendMessage("Hello, how are you?", "user");

    try
    {
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
