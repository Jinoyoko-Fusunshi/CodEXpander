#pragma once

#include <string>
#include <vector>

namespace CodEXpander::Core {
    class Argument final {
    private:
        std::string name;
        std::string value;

    public:
        Argument() = default;
        explicit Argument(std::string name, std::string value = "");
        ~Argument() = default;

        const std::string& GetName();
        const std::string& GetValue();
        bool HasValue();
    };

    std::vector<Argument> ParseArguments(const int argument_count, const std::vector<std::string> &arguments);
    bool TryParseArgument(const std::string &argumentString, Argument &argument);
    bool TryGetArgumentWithValue(const std::vector<Argument> &arguments, const std::string &name, Argument &foundArgument);
    bool TryGetArgument(const std::vector<Argument> &arguments, const std::string &name, Argument &foundArgument);
}