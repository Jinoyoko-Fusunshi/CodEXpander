#pragma once

#include <string>

enum class SoftwareType {
    CPP = 20,
    C = 11
};

struct Software {
    std::string name;
    SoftwareType type;
};