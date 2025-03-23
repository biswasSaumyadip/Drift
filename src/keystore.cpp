//
// Created by saumy on 3/22/2025.
//

#include "keystore.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::unordered_map<std::string, std::string> kvStore;

void loadFromFile(const std::string &filePath) {
    kvStore.clear();
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string value;
        if (std::string key; std::getline(iss, key, ',') && std::getline(iss, value)) {
            kvStore[key] = value;
        }
    }

    file.close();
}

std::unordered_map<std::string, std::string> loadKeyValueStore(const std::string& filePath) {

    std::unordered_map<std::string, std::string> temporaryKVStore;

    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string value;
        if (std::string key; std::getline(iss, key, ',') && std::getline(iss, value)) {
            temporaryKVStore[key] = value;
        }
    }

    file.close();

    return temporaryKVStore;
}

void writeToFile(const std::string &key, const std::string &value, const std::string &filePath) {
    std::ofstream file;
    file.open(filePath, std::ios::app); // using append mode to prevent overwriting on
    // existing file

    if (!file) {
        std::cerr << "Unable to open file." << std::endl;
        throw std::runtime_error("Unable to open file.");
    }

    file << key << "," << value << std::endl;

    file.close();
    kvStore[key] = value;
}

void updateFile(const std::string &filePath) {
    std::ofstream file;
    file.open(filePath, std::ios::trunc);
    if (!file) {
        std::cerr << "Unable to open file." << std::endl;
        throw std::runtime_error("Unable to open file.");
    }

    for (const auto &[key, val]: kvStore) {
        //write to file
        file << key << "," << val << std::endl;
    }

    file.close();
}
