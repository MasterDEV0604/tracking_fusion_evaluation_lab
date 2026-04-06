#pragma once
#include "core/Types.h"
#include <string>
#include <vector>

namespace tfel {

struct RunResult {
    RunMetrics metrics;
    std::vector<std::pair<int, TrackState>> history;
};

class TrackingEngine {
public:
    RunResult run(const std::vector<FramePacket>& frames, const TrackerConfig& cfg) const;
    void writeReplay(const std::vector<std::pair<int, TrackState>>& history, const std::string& path) const;
};

}
