#include "fusion/SensorNormalizer.h"

namespace tfel {

std::vector<Detection> SensorNormalizer::normalize(const std::vector<Detection>& detections) const {
    std::vector<Detection> out = detections;
    for (auto& d : out) {
        if (d.source == "camera") d.confidence *= cfg_.camera_confidence_scale;
        else if (d.source == "radar") d.confidence *= cfg_.radar_confidence_scale;
        if (d.confidence < 0.1) d.confidence = 0.1;
        if (d.confidence > 1.5) d.confidence = 1.5;
    }
    return out;
}

}
