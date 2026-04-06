#pragma once
#include "core/Types.h"
#include <vector>

namespace tfel {

class Metrics {
public:
    RunMetrics compute(const std::vector<FramePacket>& frames,
                       const std::vector<std::pair<int, TrackState>>& history,
                       int tracks_created,
                       int deleted_tracks) const;
};

}
