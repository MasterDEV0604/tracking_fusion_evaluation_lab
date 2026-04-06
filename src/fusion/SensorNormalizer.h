#pragma once
#include "core/Types.h"
#include <vector>

namespace tfel {

class SensorNormalizer {
public:
    explicit SensorNormalizer(const TrackerConfig& cfg) : cfg_(cfg) {}
    std::vector<Detection> normalize(const std::vector<Detection>& detections) const;
private:
    TrackerConfig cfg_;
};

}
