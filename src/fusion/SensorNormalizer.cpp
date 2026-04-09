#include "fusion/SensorNormalizer.h"

namespace tfel {

std::vector<Detection> SensorNormalizer::normalize(const std::vector<Detection>& detections) const {
    std::vector<Detection> out = detections;
    for (auto& d : out) {
        if (d.source == "camera") d.confidence *= cfg_.camera_confidence_scale;
        else if (d.source == "lidar") d.confidence *= cfg_.lidar_confidence_scale;
        else d.confidence *= cfg_.radar_confidence_scale;
    }
    return out;
}

}
