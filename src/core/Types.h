#pragma once
#include <string>
#include <vector>

namespace tfel {

struct Detection {
    int frame = 0;
    double time = 0.0;
    double x = 0.0;
    double y = 0.0;
    double confidence = 1.0;
    std::string source = "radar";
    int truth_id = -1;
};

struct FramePacket {
    int frame = 0;
    double time = 0.0;
    std::vector<Detection> detections;
};

struct TrackState {
    int id = 0;
    double x = 0.0;
    double y = 0.0;
    double vx = 0.0;
    double vy = 0.0;
    int hits = 0;
    int misses = 0;
    int age = 0;
    bool confirmed = false;
    std::string dominant_source = "radar";
    int matched_truth_id = -1;
};

struct AssociationPair {
    int track_index = -1;
    int detection_index = -1;
    double distance = 0.0;
};

struct TrackerConfig {
    std::string association_mode = "global_greedy";
    std::string motion_model = "constant_velocity";
    double gate_radius = 8.0;
    double process_noise = 1.0;
    double measurement_noise = 1.0;
    int confirm_hits = 3;
    int max_misses = 4;
    double camera_confidence_scale = 0.85;
    double radar_confidence_scale = 1.0;
};

struct RunMetrics {
    int frames = 0;
    int detections = 0;
    int tracks_created = 0;
    int confirmed_tracks = 0;
    int deleted_tracks = 0;
    int matched_updates = 0;
    int unmatched_detections = 0;
    int id_switches = 0;
    double mean_position_error = 0.0;
    double track_continuity = 0.0;
};

} // namespace tfel
