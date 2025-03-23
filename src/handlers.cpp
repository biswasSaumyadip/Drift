//
// Created by saumy on 3/22/2025.
//

#include "handlers.h"

#include <format>

#include "utils/color_utils.hpp"
#include "config.hpp"
#include "keystore.h"
#include <regex>


void errorKeyDoesNotExist(const std::string &keyName) {
    log(Color::RED, "Error: key '" + keyName + "' does not exists!");
}

bool confirm(const std::string &message) {
    std::cout << message << " (y/n): ";
    std::string response;
    std::getline(std::cin, response);

    if (response == "y" || response == "Y") {
        return true;
    } else if (response == "n" || response == "N") {
        return false;
    } else {
        LOG::error("Invalid input. Please type 'y' or 'n'.");
        return confirm(message); // Recursively ask again
    }
}

void handleSet(const std::vector<std::string> &args) {
    if (args.size() < 2) {
        LOG::error("Error: .set requires <key> and <value>");
    }

    const auto &key = args[0];
    const auto &value = args[1];

    if (kvStore.contains(key)) {
        LOG::error("Error: key '" + key + "' already exists!");
    } else {
        writeToFile(key, value, KSConfig::FILE_NAME);
        LOG::success("Key-Value saved.");
    }
}


void handleGet(const std::vector<std::string> &args) {
    if (args.empty()) {
        LOG::error("Error: .get requires <key>");
        return;
    }

    if (const auto &key = args[0]; kvStore.contains(key)) {
        std::cout << key << " => " << kvStore[key] << std::endl;
    } else {
        errorKeyDoesNotExist(key);
    }
}

void handleUpdate(const std::vector<std::string> &args) {
    if (args.size() < 2) {
        LOG::error("Error: .update requires <key> and <value>");
        return;
    }

    const auto &key = args[0];
    const auto &value = args[1];

    if (!kvStore.contains(key)) {
        errorKeyDoesNotExist(key);
    } else {
        kvStore[key] = value;
        updateFile(KSConfig::FILE_NAME);
        LOG::success("Key '" + key + "' updated.");
    }
}

void handleDelete(const std::vector<std::string> &args) {
    if (args.empty()) {
        LOG::error("Error: .delete requires <key>");
        return;
    }


    if (const auto &key = args[0]; !kvStore.contains(key)) {
        errorKeyDoesNotExist(key);
    } else {
        if (confirm("Are you sure you want to delete key '" + key + "'?")) {
            kvStore.erase(key);
            updateFile(KSConfig::FILE_NAME);
            LOG::success("Key '" + key + "' deleted.");
        } else {
            LOG::info("Deletion canceled.");
        }
    }
}

void handleClearAll(const std::vector<std::string> &args) {
    if (confirm(
        "Are you sure you want to delete ALL keys? This action cannot be undone!")) {
        kvStore.clear();
        updateFile(KSConfig::FILE_NAME);
        LOG::success("All keys have been deleted.");
    } else {
        std::cout << "Clear all canceled." << std::endl;
    }
}

void handleList(const std::vector<std::string> &args) {
    if (kvStore.empty()) {
        std::cout << "No key exist." << std::endl;
    } else {
        LOG::success("Stored key-value pairs:");
        for (const auto &[key, val]: kvStore) {
            LOG::info(std::string("- ").append(key).append(" => ").append(val));
        }
    }
}

void handleRename(const std::vector<std::string> &args) {
    if (args.size() < 2) {
        LOG::warning("Usage: .rename <old_key> <new_key>");
        return;
    }

    const auto &key = args[0];
    const auto &newKey = args[1];

    if (!kvStore.contains(key)) {
        LOG::error("Key '" + key + "' does not exist.");
    } else if (kvStore.contains(newKey)) {
        LOG::error("Key '" + newKey + "' already exists.");
    } else {
        kvStore[newKey] = kvStore[key];
        kvStore.erase(key);
        updateFile(KSConfig::FILE_NAME);
        LOG::success("Renamed '" + key + "' to '" + newKey + "'");
    }
}

void handleBatch(const std::vector<std::string> &args) {
    LOG::info("Batch mode: Enter key-value pairs (type 'done' to finish)");

    const std::regex quotedPattern(R"(^(\S+)\s+\"(.*)\")"); // key "multi word value"

    while (true) {
        std::cout << ">> ";
        std::string inputLine;
        std::getline(std::cin, inputLine);

        if (inputLine == "done") {
            LOG::success("Batch complete.");
            break;
        }

        if (std::smatch match; std::regex_match(inputLine, match, quotedPattern)) {
            //QUOTED value
            std::string key = match[1];
            std::string value = match[2];

            if (kvStore.contains(key)) {
                LOG::error("Key '" + key + "' already exists. Skipping...");
            } else {
                kvStore[key] = value;
                writeToFile(key, value, KSConfig::FILE_NAME);
                LOG::success(
                    std::string("Inserted ").append(key).append("' => '").append(value).append(
                        "'"));
            }
        } else {
            //Unquoted value
            std::istringstream iss(inputLine);
            std::string key, value;
            iss >> key >> value;

            if (key.empty() || value.empty()) {
                LOG::warning("Invalid input. Usage: <key> <value> OR <key> \"multi word value\"");
                continue;
            }

            if (kvStore.contains(key)) {
                LOG::error("Key '" + key + "' already exists. Skipping...");
            } else {
                kvStore[key] = value;
                writeToFile(key, value, KSConfig::FILE_NAME);
                LOG::success(std::format("Inserted '{}' => '{}'", key, value));
            }
        }
    }
}


void handleHelp(const std::vector<std::string> &args) {
    std::cout << "========== Available Commands ==========\n";
    std::cout << ".exit     | .et             : Exit the terminal\n";
    std::cout << ".set      | .st  <key> <value>    : Set a key-value pair\n";
    std::cout << ".get      | .gt  <key>           : Get a value by key\n";
    std::cout << ".update   | .up  <key> <value>   : Update an existing key's value\n";
    std::cout << ".delete   | .del <key>           : Delete a key\n";
    std::cout << ".rename   | .rn  <old_key> <new_key> : Rename an existing key\n";
    std::cout << ".clr_all                     : Clear all key-value pairs\n";
    std::cout << ".list     | .ls              : List all stored key-values\n";
    std::cout << ".version  | .v               : Show current version\n";
    std::cout << ".create <db name>            : Create a database " << std::endl;
    std::cout << ".batch                       : For batch insert\n";
    std::cout << ".begin                       : Begin a transaction" << std::endl;
    std::cout << "========================================\n";
}

void handleExit(const std::vector<std::string> &args) {
    std::exit(0);
}

void handleVersion(const std::vector<std::string> &args) {
    LOG::info(std::string("KS CLI version ").append(KSConfig::VERSION));
}

void handleBegin(const std::vector<std::string> &args) {
}

void handleCommit(const std::vector<std::string> &args);

void handleRollback(const std::vector<std::string> &args);

void handleCreate(const std::vector<std::string> &args) {
}
