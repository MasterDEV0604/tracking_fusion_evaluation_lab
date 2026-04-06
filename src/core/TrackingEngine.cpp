#include "core/TrackingEngine.h"
#include "core/TrackManager.h"
#include "reporting/Metrics.h"
#include <fstream>
#include <map>

namespace tfel {

RunResult TrackingEngine::run(const std::vector<FramePacket>& frames, const TrackerConfig& cfg) const {
    TrackManager manager(cfg);
    for (const auto& f : frames) manager.processFrame(f);
    Metrics metrics;
    RunResult result;
    result.history = manager.history();
    result.metrics = metrics.compute(frames, manager.history(), manager.tracksCreated(), manager.deletedTracks());
    return result;
}

void TrackingEngine::writeReplay(const std::vector<std::pair<int, TrackState>>& history, const std::string& path) const {
    std::ofstream out(path);
    std::map<int, std::vector<TrackState>> grouped;
    for (const auto& item : history) grouped[item.first].push_back(item.second);
    for (const auto& kv : grouped) {
        out << "Frame " << kv.first << "\n";
        for (const auto& s : kv.second) {
            out << "  Track " << s.id << " pos=(" << s.x << ", " << s.y << ") vel=(" << s.vx << ", " << s.vy
                << ") hits=" << s.hits << " misses=" << s.misses << " confirmed=" << (s.confirmed ? "yes" : "no")
                << " source=" << s.dominant_source << " truth=" << s.matched_truth_id << "\n";
        }
    }
}

}
