//
// Created by saumy on 3/22/2025.
//

#include "registry.h"
#include <sstream>
#include "utils/color_utils.hpp"


void CommandRegistry::registerCommand(const std::string& name, const CommandHandler &handler) {
    handlers_[name] = handler;
}

void CommandRegistry::registerAlias(const std::string& alias, const std::string& target) {
    aliasMap_[alias] = target;
}

void CommandRegistry::execute(const std::string& inputLine) const {
    std::istringstream iss(inputLine);
    std::string cmd;
    std::vector<std::string> args;

    iss >> cmd;
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }

    auto resolvedCmd = cmd;
    if (aliasMap_.contains(cmd)) {
        resolvedCmd = aliasMap_.at(cmd);
    }

    if (handlers_.contains(resolvedCmd)) {
        handlers_.at(resolvedCmd)(args);
    } else {
       log(Color::YELLOW, "Unknown command. Type help to get help");
    }
}