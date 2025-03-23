#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include "config.hpp"
#include "handlers.h"
#include "keystore.h"
#include "registry.h"
#include "utils/color_utils.hpp"
#include "databaseManager.h"

void printPrompt() {
    std::cout << "Welcome to KS!" << std::endl;
}

void printBanner() {
    std::cout << color(Color::CYAN);
    std::cout << "==========================\n";
    std::cout << "       " << KSConfig::APP_NAME << "\n";
    std::cout << "==========================\n";
    std::cout << color(Color::RESET);
}


[[noreturn]] int main() {
    enableANSIColors();
    CommandRegistry registry;

    DatabaseManager databaseManager;
    databaseManager.init();

    databaseManager.createDB("world.csv");


    registry.registerCommand("set", handleSet);
    registry.registerCommand("get", handleGet);
    registry.registerCommand("update", handleUpdate);
    registry.registerCommand("delete", handleDelete);
    registry.registerCommand("rename", handleRename);
    registry.registerCommand("list", handleList);
    registry.registerCommand("clr_all", handleClearAll);
    registry.registerCommand("rename", handleRename);
    registry.registerCommand("batch", handleBatch);
    registry.registerCommand("help", handleHelp);
    registry.registerCommand("exit", handleExit);
    registry.registerCommand("version", handleVersion);


    for (auto alias : KSConfig::CommandAliases::SET) registry.registerAlias(std::string(alias), "set");
    for (auto alias : KSConfig::CommandAliases::GET) registry.registerAlias(std::string(alias), "get");
    for (auto alias : KSConfig::CommandAliases::UPDATE) registry.registerAlias(std::string(alias), "update");
    for (auto alias : KSConfig::CommandAliases::DELETE_KEY) registry.registerAlias(std::string(alias), "delete");
    for (auto alias : KSConfig::CommandAliases::LIST) registry.registerAlias(std::string(alias), "list");
    for (auto alias : KSConfig::CommandAliases::RENAME) registry.registerAlias(std::string(alias), "rename");
    for (auto alias : KSConfig::CommandAliases::EXIT) registry.registerAlias(std::string(alias), "exit");
    for (auto alias : KSConfig::CommandAliases::VERSION) registry.registerAlias(std::string(alias), "version");
    for (auto alias : KSConfig::CommandAliases::HELP) registry.registerAlias(std::string(alias), "help");
    for (auto alias : KSConfig::CommandAliases::CLEAR) registry.registerAlias(std::string(alias), "clear");
    for (auto alias : KSConfig::CommandAliases::BATCH) registry.registerAlias(std::string(alias), "batch");

    //TODO: User should select DB before using it when user hits 'use db' command then it should load the db into memory other db should be ignored.
    //TODO: if use creates a db it should create but should not load the db into memory.
    //TODO: On create db program should check if the db already exist in the disk or not.
    //TODO: program should not prompt user to use db but if user does any action related to db
    // then it should throw exception for 'use db'
    //
    loadFromFile(KSConfig::FILE_NAME);
    printPrompt();
    printBanner();

    while (true) {
        std::cout << ">> ";
        std::string inputLine;
        std::getline(std::cin, inputLine);
        registry.execute(inputLine);
    }
}
