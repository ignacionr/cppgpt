#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using namespace std::string_literals;

using json = nlohmann::json;

namespace ignacionr
{
    class cppollama
    {
    private:
        std::string base_url;           // Base URL for the local Ollama instance
        std::vector<json> conversation; // To keep track of the conversation history

    public:
        // Initialize with the local Ollama instance URL, e.g., http://localhost:11434
        cppollama(const std::string &base_url) : base_url(base_url) {}

        // Function to send a message to Ollama and receive the reply
        json sendMessage(std::string_view message, std::string_view role, std::string_view model = "codellama", float temperature = 0.25)
        {
            // Append the new message to the conversation history
            conversation.push_back({{"role", role}, {"content", message}});

            // Prepare the API request payload for Ollama. Adjust fields as necessary based on Ollama API.
            json payload = {
                {"model", model},
                {"messages", json::array({{{"role", role},
                                           {"content", message}}})}};

            // The endpoint and payload structure might need adjustments to fit Ollama's API.
            auto r = cpr::Post(
                cpr::Url{base_url + "/api/chat"},
                cpr::Header{{"Content-Type", "application/json"}},
                cpr::Body{payload.dump()});

            // check for network errors
            if (r.error)
            {
                std::cerr << "Error: " << r.error.message << std::endl;
                // handle the error, e.g., by retrying the request, logging the error, etc.
            }
            else if (r.status_code != 200)
            {
                throw std::runtime_error("Error: "s + r.text + " (status code "s + std::to_string(r.status_code) + ")"s);
            }

            // Parse the API response. Adjust according to Ollama's response structure.
            std::cout << "Response: " << r.text << std::endl;
            auto response = json::parse(r.text);
            auto gpt_reply = response["choices"][0]["message"]["content"]; // This path may need adjustments.

            // Append the assistant's reply to the conversation history
            conversation.push_back({{"role", "assistant"}, {"content", gpt_reply}});

            return response;
        }
    };
}
