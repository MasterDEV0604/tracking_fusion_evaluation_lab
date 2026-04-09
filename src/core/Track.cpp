#include "core/Track.h"

namespace tfel {

Track::Track(int id, const Detection& seed, const TrackerConfig& cfg) : id_(id), cfg_(cfg) {
    filter_.initialize(seed.x, seed.y);
    filter_.setModel(cfg.motion_model, cfg.process_noise, cfg.measurement_noise);
    state_ = filter_.estimate();
    state_.id = id_;
    state_.hits = 1;
    state_.age = 1;
    state_.first_frame = seed.frame;
    state_.dominant_source = seed.source;
    state_.matched_truth_id = seed.truth_id;
    state_.confirmed = (state_.hits >= cfg.confirm_hits);
}

void Track::predict(double dt) {
    filter_.predict(dt);
    auto est = filter_.estimate();
    state_.x = est.x; state_.y = est.y; state_.vx = est.vx; state_.vy = est.vy;
    state_.age += 1;
}

void Track::update(const Detection& detection) {
    filter_.update(detection.x, detection.y, detection.confidence);
    auto est = filter_.estimate();
    state_.x = est.x; state_.y = est.y; state_.vx = est.vx; state_.vy = est.vy;
    state_.hits += 1;
    state_.misses = 0;
    state_.dominant_source = detection.source;
    state_.matched_truth_id = detection.truth_id;
    if (!state_.confirmed && state_.hits >= cfg_.confirm_hits) state_.confirmed = true;
}

void Track::markMiss() {
    state_.misses += 1;
}

bool Track::shouldDelete(int max_misses) const {
    return state_.misses > max_misses;
}

TrackState Track::state() const {
    return state_;
}

}
