//
// Created by saumy on 3/22/2025.
//

#ifndef KEYSTORE_H
#define KEYSTORE_H


#include <string>
#include <unordered_map>

// Global KV store (extern means it’s defined elsewhere)
extern std::unordered_map<std::string, std::string> kvStore;

void loadFromFile(const std::string& filePath);
std::unordered_map<std::string, std::string> loadKeyValueStore(const std::string& filePath);
void writeToFile(const std::string& key, const std::string& value, const std::string& filePath);
void updateFile(const std::string& filePath);


#endif //KEYSTORE_H
