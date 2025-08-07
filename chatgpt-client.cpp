#include <iostream>
#include <string>
#include <sstream>
#include <curl/curl.h>

// Callback to handle the response data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    const std::string api_key = "sk-REPLACE_WITH_YOUR_KEY";
    const std::string url = "https://api.openai.com/v1/chat/completions";

    std::string postData = R"({
        "model": "gpt-4",
        "messages": [
            {"role": "system", "content": "You are a helpful assistant."},
            {"role": "user", "content": "What is the capital of France?"}
        ]
    })";

    CURL* curl = curl_easy_init();
    if (curl) {
        std::string readBuffer;
        struct curl_slist* headers = nullptr;

        headers = curl_slist_append(headers, ("Authorization: Bearer " + api_key).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        else
            std::cout << "Response:\n" << readBuffer << std::endl;

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    } else {
        std::cerr << "Failed to initialize curl." << std::endl;
    }

    return 0;
}
