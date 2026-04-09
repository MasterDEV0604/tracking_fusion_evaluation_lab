#pragma once
#include "core/Types.h"
#include <vector>

namespace tfel {

class HungarianAssociator {
public:
    std::vector<AssociationPair> associate(const std::vector<TrackState>& tracks,
                                           const std::vector<Detection>& detections,
                                           double gate_radius) const;
};

}
