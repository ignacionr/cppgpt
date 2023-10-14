# ignacionr's C++ GPT Wrapper (cppgpt)

## Overview

This C++ class provides a convenient way to interact with the OpenAI GPT (Generative Pre-trained Transformer) models, such as GPT-4. It uses the OpenAI API and manages conversations in a seamless manner.

## Dependencies

The class depends on the following libraries:

1. **CPR (C++ Requests)** - For sending HTTP POST requests.
   - GitHub: [libcpr/cpr](https://github.com/libcpr/cpr)
2. **nlohmann_json** - For handling JSON data.
   - GitHub: [nlohmann/json](https://github.com/nlohmann/json)

## Fetching Dependencies with CMake

The dependencies can be fetched and made available automatically using CMake's `FetchContent` module. Here is a snippet from the `CMakeLists.txt`:

```cmake
# Add cpr and nlohmann_json as dependencies
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)
```

## Usage

1. **Initialization**: Initialize the `cppgpt` class with your OpenAI API key.
    ```cpp
    ignacionr::cppgpt myGpt("your-openai-api-key");
    ```

2. **Sending Messages**: Use the `sendMessage` method to send messages to the GPT model and get a response.
    ```cpp
    auto response = myGpt.sendMessage("Hello, how are you?", "user");
    ```

3. **Extracting the Response**: You can then extract the GPT model's response from the returned JSON object.
    ```cpp
    std::string gpt_reply = response["choices"][0]["message"]["content"];
    ```

For more details, refer to the code comments in the header file.
