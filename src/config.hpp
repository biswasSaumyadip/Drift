#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string_view>
#include <array>

namespace KSConfig {
    constexpr const char* FILE_NAME = "random.csv";
    constexpr const char* VERSION = "1.0.0";
    constexpr const char* APP_NAME = "KS TERMINAL";

    namespace CommandAliases {
        constexpr std::array<std::string_view, 2> SET      = { ".set", ".st" };
        constexpr std::array<std::string_view, 2> GET      = { ".get", ".gt" };
        constexpr std::array<std::string_view, 2> UPDATE   = { ".update", ".upd" };
        constexpr std::array<std::string_view, 2> DELETE_KEY   = { ".delete", ".del" };
        constexpr std::array<std::string_view, 2> LIST     = { ".list", ".ls" };
        constexpr std::array<std::string_view, 2> RENAME   = { ".rename", ".rn" };
        constexpr std::array<std::string_view, 2> EXIT     = { ".exit", ".et" };
        constexpr std::array<std::string_view, 2> VERSION  = { ".version", ".v" };
        constexpr std::array<std::string_view, 1> HELP     = { "help" };
        constexpr std::array<std::string_view, 1> CLEAR    = { ".clr_all" };
        constexpr std::array<std::string_view, 1> BATCH    = { ".batch" };

        constexpr std::array<std::string_view, 1> BEGIN    = { ".begin" };
        constexpr std::array<std::string_view, 1> COMMIT    = { ".commit" };
        constexpr std::array<std::string_view, 1> ROLLBACK    = { ".rollback" };
    }
}

#endif // CONFIG_HPP