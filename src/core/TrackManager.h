#pragma once
#include "core/Track.h"
#include <vector>

namespace tfel {

class TrackManager {
public:
    explicit TrackManager(const TrackerConfig& cfg);
    void processFrame(const FramePacket& frame);
    const std::vector<Track>& activeTracks() const { return tracks_; }
    const std::vector<std::pair<int, TrackState>>& history() const { return history_; }
    int tracksCreated() const { return tracks_created_; }
    int deletedTracks() const { return deleted_tracks_; }
private:
    TrackerConfig cfg_;
    std::vector<Track> tracks_;
    std::vector<std::pair<int, TrackState>> history_;
    int next_id_ = 1;
    int tracks_created_ = 0;
    int deleted_tracks_ = 0;
};

}
