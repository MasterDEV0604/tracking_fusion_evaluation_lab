#include "io/Config.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace tfel {

TrackerConfig Config::load(const std::string& path) const {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Failed to open config: " + path);
    TrackerConfig cfg;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        const auto pos = line.find('=');
        if (pos == std::string::npos) continue;
        auto key = line.substr(0, pos);
        auto val = line.substr(pos + 1);
        if (key == "association_mode") cfg.association_mode = val;
        else if (key == "motion_model") cfg.motion_model = val;
        else if (key == "gate_radius") cfg.gate_radius = std::stod(val);
        else if (key == "process_noise") cfg.process_noise = std::stod(val);
        else if (key == "measurement_noise") cfg.measurement_noise = std::stod(val);
        else if (key == "confirm_hits") cfg.confirm_hits = std::stoi(val);
        else if (key == "max_misses") cfg.max_misses = std::stoi(val);
        else if (key == "camera_confidence_scale") cfg.camera_confidence_scale = std::stod(val);
        else if (key == "radar_confidence_scale") cfg.radar_confidence_scale = std::stod(val);
        else if (key == "lidar_confidence_scale") cfg.lidar_confidence_scale = std::stod(val);
    }
    return cfg;
}

}
