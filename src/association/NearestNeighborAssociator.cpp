#include "association/NearestNeighborAssociator.h"
#include "association/Gating.h"
#include <limits>

namespace tfel {

std::vector<AssociationPair> NearestNeighborAssociator::associate(const std::vector<TrackState>& tracks, const std::vector<Detection>& detections, double gate_radius) const {
    std::vector<AssociationPair> out;
    std::vector<bool> detection_used(detections.size(), false);
    for (int ti = 0; ti < static_cast<int>(tracks.size()); ++ti) {
        double best = std::numeric_limits<double>::max();
        int best_di = -1;
        for (int di = 0; di < static_cast<int>(detections.size()); ++di) {
            if (detection_used[di]) continue;
            const double d = gatedDistance(tracks[ti], detections[di], gate_radius);
            if (d >= 0.0 && d < best) {
                best = d;
                best_di = di;
            }
        }
        if (best_di >= 0) {
            detection_used[best_di] = true;
            out.push_back({ti, best_di, best});
        }
    }
    return out;
}

}
