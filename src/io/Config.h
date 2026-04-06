#pragma once
#include "core/Types.h"
#include <string>

namespace tfel {

class Config {
public:
    TrackerConfig load(const std::string& path) const;
};

}
