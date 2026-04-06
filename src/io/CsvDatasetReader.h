#pragma once
#include "core/Types.h"
#include <string>
#include <vector>

namespace tfel {

class CsvDatasetReader {
public:
    std::vector<FramePacket> read(const std::string& path) const;
};

}
