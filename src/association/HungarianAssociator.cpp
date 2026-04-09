#include "association/HungarianAssociator.h"
#include "association/Gating.h"
#include <algorithm>
#include <functional>
#include <limits>

namespace tfel {

std::vector<AssociationPair> HungarianAssociator::associate(const std::vector<TrackState>& tracks,
                                                            const std::vector<Detection>& detections,
                                                            double gate_radius) const {
    if (tracks.empty() || detections.empty()) return {};
    const int n = static_cast<int>(tracks.size());
    const int m = static_cast<int>(detections.size());
    const double invalid = gate_radius * 1000.0;
    const double skip_penalty = gate_radius * 0.95;
    std::vector<std::vector<double>> cost(n, std::vector<double>(m, invalid));
    for (int ti = 0; ti < n; ++ti) {
        for (int di = 0; di < m; ++di) {
            const double d = gatedDistance(tracks[ti], detections[di], gate_radius);
            if (d >= 0.0) cost[ti][di] = d;
        }
    }

    std::vector<AssociationPair> best;
    double best_score = std::numeric_limits<double>::infinity();
    std::vector<bool> used(m, false);
    std::vector<AssociationPair> cur;

    std::function<void(int, double)> dfs = [&](int ti, double score) {
        if (score >= best_score) return;
        if (ti == n) {
            best_score = score;
            best = cur;
            return;
        }
        dfs(ti + 1, score + skip_penalty);
        for (int di = 0; di < m; ++di) {
            if (used[di] || cost[ti][di] >= invalid) continue;
            used[di] = true;
            cur.push_back({ti, di, cost[ti][di]});
            dfs(ti + 1, score + cost[ti][di]);
            cur.pop_back();
            used[di] = false;
        }
    };
    dfs(0, 0.0);
    std::sort(best.begin(), best.end(), [](const auto& a, const auto& b) { return a.track_index < b.track_index; });
    return best;
}

}
