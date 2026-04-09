#include "reporting/Metrics.h"
#include <cmath>
#include <map>
#include <set>

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
    std::map<int, int> lifespan;
    std::map<int, int> first_frame_by_track;
    std::set<int> confirmed_track_ids;
    std::set<int> truth_updates;
    double error_sum = 0.0;
    int error_count = 0;
    int continuity_numerator = 0;

    for (const auto& frame : frames) {
        m.detections += static_cast<int>(frame.detections.size());
        for (const auto& d : frame.detections) if (d.truth_id >= 0) truth_updates.insert(d.truth_id * 100000 + d.frame);
    }

    for (const auto& item : history) {
        const int frame = item.first;
        const auto& s = item.second;
        lifespan[s.id] += 1;
        continuity_numerator += 1;
        if (!first_frame_by_track.count(s.id)) first_frame_by_track[s.id] = s.first_frame;
        if (s.confirmed) confirmed_track_ids.insert(s.id);
        if (s.matched_truth_id >= 0) {
            auto it = truth_to_track.find(s.matched_truth_id);
            if (it == truth_to_track.end()) truth_to_track[s.matched_truth_id] = s.id;
            else if (it->second != s.id) {
                m.id_switches += 1;
                it->second = s.id;
            }
            truth_updates.erase(s.matched_truth_id * 100000 + frame);
        } else if (s.confirmed) {
            m.false_track_updates += 1;
        }
    }

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

    double confirm_latency_sum = 0.0;
    int confirm_latency_count = 0;
    for (const auto& item : history) {
        const int frame = item.first;
        const auto& s = item.second;
        if (s.confirmed && s.hits == 3) {
            confirm_latency_sum += (frame - s.first_frame);
            confirm_latency_count += 1;
        }
    }

    m.confirmed_tracks = static_cast<int>(confirmed_track_ids.size());
    m.matched_updates = error_count;
    m.unmatched_detections = m.detections - m.matched_updates;
    m.missed_truth_updates = static_cast<int>(truth_updates.size());
    m.mean_position_error = error_count ? error_sum / error_count : 0.0;
    m.track_continuity = history.empty() ? 0.0 : static_cast<double>(continuity_numerator) / static_cast<double>(history.size());
    m.mean_confirm_latency_frames = confirm_latency_count ? confirm_latency_sum / confirm_latency_count : 0.0;
    return m;
}

}
