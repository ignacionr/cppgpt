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
    private:
        std::string api_key;            // Your OpenAI API key
        std::vector<json> conversation; // To keep track of the conversation history

    public:
        cppgpt(const std::string &api_key) : api_key(api_key) {}

        // Function to send a message to GPT and receive the reply
        json sendMessage(std::string_view message, std::string_view role, float temperature = 0.25)
        {
            // Append the new message to the conversation history
            conversation.push_back({{"role", role}, {"content", message}});

            // Prepare the API request payload
            json payload = {
                {"model", "gpt-4"},
                {"messages", conversation},
                {"temperature", temperature}};

            // Send the API request
            auto r = cpr::Post(
                cpr::Url{"https://api.openai.com/v1/chat/completions"},
                cpr::Header{{"Authorization", "Bearer " + api_key}, {"Content-Type", "application/json"}},
                cpr::Body{payload.dump()});

            // Parse the API response
            auto response = json::parse(r.text);
            auto gpt_reply = response["choices"][0]["message"]["content"];

            // Append GPT's reply to the conversation history
            conversation.push_back({{"role", "assistant"}, {"content", gpt_reply}});

            return response;
        }
    };
}
