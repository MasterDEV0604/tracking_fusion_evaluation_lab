#include "association/HungarianAssociator.h"
#include <cassert>
#include <vector>

int main() {
    using namespace tfel;
    TrackState t1; t1.id = 1; t1.x = 0.0; t1.y = 0.0;
    TrackState t2; t2.id = 2; t2.x = 10.0; t2.y = 0.0;
    std::vector<TrackState> tracks{t1, t2};

    Detection a; a.x = 0.5; a.y = 0.0;
    Detection b; b.x = 9.5; b.y = 0.0;
    std::vector<Detection> detections{a, b};

    HungarianAssociator hungarian;
    auto pairs = hungarian.associate(tracks, detections, 5.0);
    assert(pairs.size() == 2);
    bool saw_first = false, saw_second = false;
    for (const auto& p : pairs) {
        if (p.track_index == 0 && p.detection_index == 0) saw_first = true;
        if (p.track_index == 1 && p.detection_index == 1) saw_second = true;
    }
    assert(saw_first && saw_second);
    return 0;
}
