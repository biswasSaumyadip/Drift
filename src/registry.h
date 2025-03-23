//
// Created by saumy on 3/22/2025.
//

#ifndef REGISTRY_H
#define REGISTRY_H

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>


class CommandRegistry {
public:
    using CommandHandler = std::function<void(const std::vector<std::string> &)>;
    // like in TS we declare fn: (num: number) => void

    void registerCommand(const std::string &name, const CommandHandler &handler);

    void registerAlias(const std::string &alias, const std::string &target);

    void execute(const std::string &inputLine) const;

private:
    std::unordered_map<std::string, CommandHandler> handlers_;
    std::unordered_map<std::string, std::string> aliasMap_;
};


#endif //REGISTRY_H
