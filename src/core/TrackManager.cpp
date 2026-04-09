#include "core/TrackManager.h"
#include "association/GlobalGreedyAssociator.h"
#include "association/HungarianAssociator.h"
#include "association/NearestNeighborAssociator.h"
#include "fusion/SensorNormalizer.h"
#include <algorithm>

namespace tfel {

TrackManager::TrackManager(const TrackerConfig& cfg) : cfg_(cfg) {}

void TrackManager::processFrame(const FramePacket& frame) {
    const double dt = 1.0;
    for (auto& t : tracks_) t.predict(dt);

    SensorNormalizer normalizer(cfg_);
    auto detections = normalizer.normalize(frame.detections);

    std::vector<TrackState> states;
    states.reserve(tracks_.size());
    for (const auto& t : tracks_) states.push_back(t.state());

    std::vector<AssociationPair> pairs;
    if (cfg_.association_mode == "nearest") {
        NearestNeighborAssociator assoc;
        pairs = assoc.associate(states, detections, cfg_.gate_radius);
    } else if (cfg_.association_mode == "hungarian") {
        HungarianAssociator assoc;
        pairs = assoc.associate(states, detections, cfg_.gate_radius);
    } else {
        GlobalGreedyAssociator assoc;
        pairs = assoc.associate(states, detections, cfg_.gate_radius);
    }

    std::vector<bool> matched_track(tracks_.size(), false);
    std::vector<bool> matched_detection(detections.size(), false);

    for (const auto& p : pairs) {
        matched_track[p.track_index] = true;
        matched_detection[p.detection_index] = true;
        tracks_[p.track_index].update(detections[p.detection_index]);
    }

    for (size_t i = 0; i < tracks_.size(); ++i) {
        if (!matched_track[i]) tracks_[i].markMiss();
    }

    for (size_t i = 0; i < detections.size(); ++i) {
        if (!matched_detection[i]) {
            tracks_.emplace_back(next_id_++, detections[i], cfg_);
            tracks_created_ += 1;
        }
    }

    const auto before = tracks_.size();
    tracks_.erase(std::remove_if(tracks_.begin(), tracks_.end(), [&](const Track& t) {
        return t.shouldDelete(cfg_.max_misses);
    }), tracks_.end());
    deleted_tracks_ += static_cast<int>(before - tracks_.size());

    for (const auto& t : tracks_) history_.push_back({frame.frame, t.state()});
}

}
