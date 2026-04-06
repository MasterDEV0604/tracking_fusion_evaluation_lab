#include "filter/LinearTracker2D.h"
#include <algorithm>

namespace tfel {

void LinearTracker2D::initialize(double x, double y) {
    x_ = x; y_ = y; vx_ = 0.0; vy_ = 0.0;
}

void LinearTracker2D::setModel(const std::string& motion_model, double process_noise, double measurement_noise) {
    motion_model_ = motion_model;
    process_noise_ = process_noise;
    measurement_noise_ = measurement_noise;
}

void LinearTracker2D::predict(double dt) {
    x_ += vx_ * dt;
    y_ += vy_ * dt;
    if (motion_model_ == "damped_velocity") {
        const double damping = std::max(0.0, 1.0 - 0.08 * process_noise_ * dt);
        vx_ *= damping;
        vy_ *= damping;
    }
}

void LinearTracker2D::update(double mx, double my, double confidence) {
    const double trust = std::clamp(confidence / (measurement_noise_ + 1e-6), 0.15, 0.95);
    const double new_vx = mx - x_;
    const double new_vy = my - y_;
    x_ = x_ * (1.0 - trust) + mx * trust;
    y_ = y_ * (1.0 - trust) + my * trust;
    vx_ = vx_ * 0.5 + new_vx * 0.5;
    vy_ = vy_ * 0.5 + new_vy * 0.5;
}

TrackState LinearTracker2D::estimate() const {
    TrackState s;
    s.x = x_; s.y = y_; s.vx = vx_; s.vy = vy_;
    return s;
}

}
