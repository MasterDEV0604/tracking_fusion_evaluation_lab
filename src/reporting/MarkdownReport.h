#pragma once
#include "core/Types.h"
#include <string>
#include <vector>

namespace tfel {

struct BenchmarkRow {
    std::string dataset;
    std::string config_name;
    RunMetrics metrics;
};

class MarkdownReport {
public:
    void write(const std::string& path, const std::vector<BenchmarkRow>& rows) const;
};

}
