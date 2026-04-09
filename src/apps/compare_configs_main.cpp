#include "core/TrackingEngine.h"
#include "io/Config.h"
#include "io/CsvDatasetReader.h"
#include <filesystem>
#include <iomanip>
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cerr << "Usage: tfel_compare_configs <dataset.csv> <config1.cfg> <config2.cfg> [config3.cfg ...]\n";
        return 1;
    }
    try {
        tfel::CsvDatasetReader reader;
        tfel::Config loader;
        tfel::TrackingEngine engine;
        auto frames = reader.read(argv[1]);
        std::cout << "dataset,config,mean_error,id_switches,missed_truth,false_tracks,confirmed,confirm_latency\n";
        for (int i = 2; i < argc; ++i) {
            const std::string cfg_path = argv[i];
            auto cfg = loader.load(cfg_path);
            auto result = engine.run(frames, cfg);
            std::cout << std::filesystem::path(argv[1]).filename().string() << ','
                      << std::filesystem::path(cfg_path).filename().string() << ','
                      << std::fixed << std::setprecision(3)
                      << result.metrics.mean_position_error << ','
                      << result.metrics.id_switches << ','
                      << result.metrics.missed_truth_updates << ','
                      << result.metrics.false_track_updates << ','
                      << result.metrics.confirmed_tracks << ','
                      << result.metrics.mean_confirm_latency_frames << '\n';
        }
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 2;
    }
}
