#include "io/TrackWriter.h"
#include <fstream>
#include <iomanip>

namespace tfel {

void TrackWriter::writeCsv(const std::string& path, const std::vector<std::pair<int, TrackState>>& history) const {
    std::ofstream out(path);
    out << "frame,track_id,x,y,vx,vy,hits,misses,confirmed,source,truth_id\n";
    out << std::fixed << std::setprecision(3);
    for (const auto& item : history) {
        const auto& s = item.second;
        out << item.first << ',' << s.id << ',' << s.x << ',' << s.y << ',' << s.vx << ',' << s.vy
            << ',' << s.hits << ',' << s.misses << ',' << (s.confirmed ? 1 : 0) << ',' << s.dominant_source << ',' << s.matched_truth_id << '\n';
    }
}

void TrackWriter::writeSummary(const std::string& path, const RunMetrics& metrics) const {
    std::ofstream out(path);
    out << "frames=" << metrics.frames << "\n";
    out << "detections=" << metrics.detections << "\n";
    out << "tracks_created=" << metrics.tracks_created << "\n";
    out << "confirmed_tracks=" << metrics.confirmed_tracks << "\n";
    out << "deleted_tracks=" << metrics.deleted_tracks << "\n";
    out << "matched_updates=" << metrics.matched_updates << "\n";
    out << "unmatched_detections=" << metrics.unmatched_detections << "\n";
    out << "id_switches=" << metrics.id_switches << "\n";
    out << "mean_position_error=" << metrics.mean_position_error << "\n";
    out << "track_continuity=" << metrics.track_continuity << "\n";
}

}
