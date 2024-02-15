#include <iostream>
#include <curl/curl.h>
#include <thread>
#include <future>
#include <vector>
#include <fstream>
#include <GenerateMnemonic.h>
#include <ProcessAddress.h>
#include <json.hpp>

int successCount = 0;
int failCount = 0;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response) {
    size_t totalSize = size * nmemb;
    response->append((char *) contents, totalSize);
    return totalSize;
}

void sendRequest(std::ofstream &file) {
    while (true) {
        try {
            std::string mnemonic = GenerateMnemonic(12);
            std::string address = Tron::generate_keypair_and_get_address_from_mnemonic(mnemonic.c_str());

            CURL *curl;
            CURLcode res;
            std::string response;
            curl = curl_easy_init();
            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL,
                                 ("https://api.trongrid.io/v1/accounts/" + address).c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_PROXY, "http://127.0.0.1:10809");
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
                res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);

                if (res != CURLE_OK) {
                    std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
                } else {
                    //printf("%s", response.c_str());
                    nlohmann::json j = nlohmann::json::parse(response);
                    //std::cout << "Address: " << address << " Balance: " << j["final_balance"] << std::endl;
                    if(j["data"].empty()) {
                        failCount++;
                    }else {
                        int final_balance = j["data"][0]["balance"];
                        if (final_balance > 0) {
                            successCount++;
                            file << mnemonic << std::endl;
                            file << address << " " << final_balance << std::endl;
                        } else if (final_balance == 0) {
                            failCount++;
                        } else {
                            printf("No such address: %s\n", address.c_str());
                        }
                    }
                    printf("\033c");
                    //printf("Address: %s Balance: %d\n", address.c_str(), final_balance);
                    printf("Result: Success✅: %d, Fail❌: %d\n", successCount, failCount);
                }
            }
        } catch (std::exception &e) {
            printf("\033c");
            printf("Shit Free API! Fuck!\n");
        }
    }
}

int main(int argc, char *argv[]) {
    int threadCount;
    std::string key;
    std::cout << "Enter the number of threads: ";
    std::cin >> threadCount;
    std::vector<std::future<void>> futures;
    std::ofstream file("addresses.txt", std::ios::app);
    for (int i = 0; i < threadCount; i++) {
        futures.push_back(std::async(std::launch::async, sendRequest, std::ref(file)));
    }
    for (auto &f: futures) {
        f.get();
    }
    file.close();
    return 0;
}