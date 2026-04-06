#include "reporting/Metrics.h"
#include <cmath>
#include <map>

namespace tfel {

RunMetrics Metrics::compute(const std::vector<FramePacket>& frames,
                            const std::vector<std::pair<int, TrackState>>& history,
                            int tracks_created,
                            int deleted_tracks) const {
    RunMetrics m;
    m.frames = static_cast<int>(frames.size());
    m.tracks_created = tracks_created;
    m.deleted_tracks = deleted_tracks;
    std::map<int, int> truth_to_track;
    double error_sum = 0.0;
    int error_count = 0;
    int confirmed = 0;
    int longest_presence = 0;
    std::map<int, int> lifespan;

    for (const auto& frame : frames) m.detections += static_cast<int>(frame.detections.size());
    for (const auto& item : history) {
        const auto& s = item.second;
        lifespan[s.id] += 1;
        if (s.confirmed) confirmed += 1;
        if (s.matched_truth_id >= 0) {
            auto it = truth_to_track.find(s.matched_truth_id);
            if (it == truth_to_track.end()) truth_to_track[s.matched_truth_id] = s.id;
            else if (it->second != s.id) {
                m.id_switches += 1;
                it->second = s.id;
            }
        }
    }
    for (const auto& kv : lifespan) longest_presence += kv.second;

    for (const auto& frame : frames) {
        for (const auto& d : frame.detections) {
            double best = 1e9;
            bool found = false;
            for (const auto& item : history) {
                if (item.first != d.frame) continue;
                const auto& s = item.second;
                if (s.matched_truth_id != d.truth_id) continue;
                const double dx = s.x - d.x;
                const double dy = s.y - d.y;
                const double e = std::sqrt(dx * dx + dy * dy);
                if (e < best) { best = e; found = true; }
            }
            if (found) { error_sum += best; error_count += 1; }
        }
    }

    m.mean_position_error = error_count ? error_sum / error_count : 0.0;
    m.confirmed_tracks = confirmed;
    m.matched_updates = error_count;
    m.unmatched_detections = m.detections - m.matched_updates;
    m.track_continuity = history.empty() ? 0.0 : static_cast<double>(longest_presence) / static_cast<double>(history.size());
    return m;
}

}
