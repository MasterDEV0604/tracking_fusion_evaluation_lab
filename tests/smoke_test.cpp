#include "core/TrackingEngine.h"
#include "io/Config.h"
#include "io/CsvDatasetReader.h"
#include <iostream>

int main() {
    tfel::CsvDatasetReader reader;
    tfel::Config loader;
    tfel::TrackingEngine engine;
    auto frames = reader.read("assets/datasets/harbor_patrol.csv");
    auto cfg = loader.load("config/balanced.cfg");
    auto result = engine.run(frames, cfg);
    if (result.metrics.frames <= 0) return 1;
    if (result.metrics.tracks_created <= 0) return 2;
    if (result.history.empty()) return 3;
    std::cout << "smoke ok\n";
    return 0;
}
