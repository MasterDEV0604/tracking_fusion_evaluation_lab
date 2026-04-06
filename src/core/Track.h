#pragma once
#include "core/Types.h"
#include "filter/LinearTracker2D.h"

namespace tfel {

class Track {
public:
    Track(int id, const Detection& seed, const TrackerConfig& cfg);
    void predict(double dt);
    void update(const Detection& detection);
    void markMiss();
    bool shouldDelete(int max_misses) const;
    TrackState state() const;
    int id() const { return id_; }
private:
    int id_ = 0;
    TrackerConfig cfg_;
    LinearTracker2D filter_;
    TrackState state_;
};

}
