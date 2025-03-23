# Drift Terminal KV Store

A modular, command-line based **Key-Value Store (KV Store)** built in modern C++ with multi-database support, transactional commands, and batch operations.

---

## Features

### ✅ Core KV Operations
- `.set <key> <value>` — Insert a new key-value pair
- `.get <key>` — Retrieve a value by key
- `.update <key> <value>` — Update existing key's value
- `.delete <key>` — Remove a key-value pair
- `.rename <old_key> <new_key>` — Rename a key
- `.list` — List all keys in current DB
- `.clr_all` — Clear all data in current DB

### ✅ Batch Operations
- `.batch` — Insert multiple key-value pairs interactively
- `.batch_update` — Update multiple keys interactively

### ✅ Transaction Support
- `.begin` — Start a transaction
- `.commit` — Commit staged changes
- `.rollback` — Discard staged changes

### ✅ Multi-Database Management
- `.create <db>` — Create a new database
- `.use <db>` — Switch to a specific database
- `.list_dbs` / `.show_dbs` — Show available databases
- `.current` — Show current active database
- Each DB is a separate CSV stored in the `/world.csv` or `/databases/` directory.

### ✅ CLI UX
- Command aliases supported (e.g., `.st` for `.set`)
- Color-coded logs using `color_utils.hpp`
- Modular command routing via `registry.cpp`

---

## Project Structure
```plaintext
/src/
├── main.cpp                  # CLI entry point
├── registry.cpp
├── registry.h
├── databaseManager.cpp
├── databaseManager.h
├── handlers.cpp
├── handlers.h
├── keystore.cpp
├── keystore.h
└── utils/
    ├── color_utils.hpp       # Color helper functions
    └── config.hpp            # Aliases & configuration

/world.csv                    # Example DB file
CMakeLists.txt
```

## Tech Stack

- **C++17**
---

## Planned Improvements

- TTL support (auto-expire keys)
- WAL (Write-Ahead Logging)
- Configurable prompt
- DB namespace isolation
- Background thread for auto-saving
- LRU cache integration
- Multi-threading for concurrent clients (future)

---

## Compile & Run

### Compile
```bash
g++ -std=c++17 -o ks_cli src/*.cpp src/utils/*.cpp