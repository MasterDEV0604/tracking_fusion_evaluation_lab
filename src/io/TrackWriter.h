#pragma once
#include "core/Types.h"
#include <string>
#include <vector>

namespace tfel {

class TrackWriter {
public:
    void writeCsv(const std::string& path, const std::vector<std::pair<int, TrackState>>& history) const;
    void writeSummary(const std::string& path, const RunMetrics& metrics) const;
};

}
