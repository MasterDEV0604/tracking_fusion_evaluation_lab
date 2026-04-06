#pragma once
#include "core/Types.h"

namespace tfel {

class LinearTracker2D {
public:
    void initialize(double x, double y);
    void setModel(const std::string& motion_model, double process_noise, double measurement_noise);
    void predict(double dt);
    void update(double mx, double my, double confidence);
    TrackState estimate() const;
private:
    double x_ = 0.0, y_ = 0.0, vx_ = 0.0, vy_ = 0.0;
    double process_noise_ = 1.0;
    double measurement_noise_ = 1.0;
    std::string motion_model_ = "constant_velocity";
};

}
