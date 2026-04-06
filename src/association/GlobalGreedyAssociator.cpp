#include "association/GlobalGreedyAssociator.h"
#include "association/Gating.h"
#include <algorithm>

namespace tfel {

std::vector<AssociationPair> GlobalGreedyAssociator::associate(const std::vector<TrackState>& tracks, const std::vector<Detection>& detections, double gate_radius) const {
    std::vector<AssociationPair> candidates;
    for (int ti = 0; ti < static_cast<int>(tracks.size()); ++ti) {
        for (int di = 0; di < static_cast<int>(detections.size()); ++di) {
            const double d = gatedDistance(tracks[ti], detections[di], gate_radius);
            if (d >= 0.0) candidates.push_back({ti, di, d});
        }
    }
    std::sort(candidates.begin(), candidates.end(), [](const auto& a, const auto& b) { return a.distance < b.distance; });
    std::vector<bool> track_used(tracks.size(), false), det_used(detections.size(), false);
    std::vector<AssociationPair> out;
    for (const auto& c : candidates) {
        if (!track_used[c.track_index] && !det_used[c.detection_index]) {
            track_used[c.track_index] = true;
            det_used[c.detection_index] = true;
            out.push_back(c);
        }
    }
    return out;
}

}
