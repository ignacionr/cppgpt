#pragma once
#include <string>
#include <vector>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace ignacionr
{
    class cppgpt
    {
    public:
        cppgpt(const std::string &api_key, const std::string &base_url = "https://api.openai.com/v1/") : api_key_(api_key), base_url_{base_url} {}

        void add_instructions(std::string_view instructions, std::string_view role = "system")
        {
            conversation.push_back({{"role", role}, {"content", instructions}});
        }

        // Function to send a message to GPT and receive the reply
        json sendMessage(std::string_view message, std::string_view role = "user", std::string_view model = "gpt-3.5-turbo", float temperature = 0.25)
        {
            std::cerr << "sendMessage: " << message << " with model " << model << std::endl;
            // Append the new message to the conversation history
            conversation.push_back({{"role", role}, {"content", message}});

            // Prepare the API request payload
            json payload = {
                {"model", model},
                {"messages", conversation},
                {"temperature", temperature}};

            // Send the API request
            auto url = cpr::Url{base_url_ + "/chat/completions"};
            std::cerr << "The URL is " << url << std::endl;
            auto r = cpr::Post(
                url,
                cpr::Header{{"Authorization", "Bearer " + api_key_}, {"Content-Type", "application/json"}},
                cpr::Body{payload.dump()});

            if (r.status_code != 200)
                throw std::runtime_error("Error: " + r.text + " (" + std::to_string(r.status_code) + ")");

            // Parse the API response
            std::cerr << "The response is " << r.text << " (" << r.text.size() << " bytes)" << std::endl;
            auto response = json::parse(r.text);
            auto gpt_reply = response["choices"][0]["message"]["content"];

            // Append GPT's reply to the conversation history
            conversation.push_back({{"role", "assistant"}, {"content", gpt_reply}});

            return response;
        }

        void clear()
        {
            conversation.clear();
        }

    private:
        std::string api_key_;            // Your OpenAI API key
        std::vector<json> conversation; // To keep track of the conversation history
        std::string const base_url_;
    };
}
