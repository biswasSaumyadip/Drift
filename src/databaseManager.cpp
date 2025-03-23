//
// Created by saumy on 3/22/2025.
//

#include "databaseManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "utils/color_utils.hpp"
#include "keystore.h"

namespace fs = std::filesystem;

static std::string dbPath = "databases";

Database *DatabaseManager::getDatabase(const std::string& db) {
    if (allDatabases.contains(db)) { return &allDatabases.at(db); }
    return nullptr;
}

void DatabaseManager::createDB(const std::string &dbName) {
    if (getDatabase(dbName) == nullptr) {
        std::ofstream file(dbPath.append("/").append(dbName));
        file.close();
        log(Color::GREEN, "Creating database " + dbName + "...");
        loadDatabases();
    } else {
        log(Color::RED, "Database already exists");
    }
}

void DatabaseManager::init() {
    if (!fs::exists(dbPath)) {
        fs::create_directory(dbPath);
    }

    loadDatabases();
}


void DatabaseManager::loadDatabases() {
    for (const auto &entry: fs::directory_iterator(dbPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".csv") {
            std::string dbName = entry.path().stem().string();
            std::string dbPath = entry.path().string();
            //TODO: load only current selected DB other should be null, or memory will be full
            const Database database(dbPath,loadKeyValueStore(dbPath));
            allDatabases[dbName] = database;
        }
    }
}
