//
// Created by saumy on 3/22/2025.
//

#ifndef HANDLERS_H
#define HANDLERS_H



#include <vector>
#include <string>

void handleSet(const std::vector<std::string>& args);
void handleGet(const std::vector<std::string>& args);
void handleUpdate(const std::vector<std::string>& args);
void handleDelete(const std::vector<std::string>& args);
void handleClearAll(const std::vector<std::string>& args);
void handleList(const std::vector<std::string>& args);
void handleRename(const std::vector<std::string>& args);
void handleBatch(const std::vector<std::string>& args);
void handleHelp(const std::vector<std::string>& args);
void handleExit(const std::vector<std::string>& args);
void handleVersion(const std::vector<std::string>& args);

void handleBegin(const std::vector<std::string>& args);
void handleCommit(const std::vector<std::string>& args);
void handleRollback(const std::vector<std::string>& args);

void handleCreate(const std::vector<std::string>& args);

#endif //HANDLERS_H
