//
// Created by saumy on 3/22/2025.
//

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <string>
#include <unordered_map>
#include <utility>


struct Database {
    std::unordered_map<std::string, std::string> kvStore;
    std::string dbFilePath;

    Database(std::string dbFilePath,
             const std::unordered_map<std::string, std::string> &
             kvStoreFilePath): kvStore(kvStoreFilePath), dbFilePath(std::move(dbFilePath)) {
    }
};

class DatabaseManager {
    std::unordered_map<std::string, Database> allDatabases;
    std::string currentDB;

    void loadDatabases();

public:
    std::string getCurrentDBName();

    void init();

    void setCurrentDB(std::string db);

    Database *getDatabase(const std::string& db);

    void createDB(const std::string &dbName);
};


#endif //DATABASEMANAGER_H
