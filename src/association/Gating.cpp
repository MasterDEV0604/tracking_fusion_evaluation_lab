#include "association/Gating.h"
#include <cmath>

namespace tfel {

double gatedDistance(const TrackState& track, const Detection& detection, double gate_radius) {
    const double dx = track.x - detection.x;
    const double dy = track.y - detection.y;
    const double d = std::sqrt(dx * dx + dy * dy);
    return (d <= gate_radius) ? d : -1.0;
}

}
