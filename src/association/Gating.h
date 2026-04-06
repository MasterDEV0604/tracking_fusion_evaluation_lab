#pragma once
#include "core/Types.h"

namespace tfel {

double gatedDistance(const TrackState& track, const Detection& detection, double gate_radius);

}
