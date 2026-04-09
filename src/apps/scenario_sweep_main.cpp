#include "core/TrackingEngine.h"
#include "io/Config.h"
#include "io/CsvDatasetReader.h"
#include "reporting/MarkdownReport.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cerr << "Usage: tfel_scenario_sweep <dataset_dir> <config_dir> <output_dir>\n";
        return 1;
    }
    try {
        namespace fs = std::filesystem;
        const std::string dataset_dir = argv[1], config_dir = argv[2], output_dir = argv[3];
        fs::create_directories(output_dir);
        tfel::CsvDatasetReader reader;
        tfel::Config loader;
        tfel::TrackingEngine engine;
        tfel::MarkdownReport report;
        std::vector<tfel::BenchmarkRow> rows;
        for (const auto& dataset_entry : fs::directory_iterator(dataset_dir)) {
            if (dataset_entry.path().extension() != ".csv") continue;
            auto frames = reader.read(dataset_entry.path().string());
            for (const auto& cfg_entry : fs::directory_iterator(config_dir)) {
                if (cfg_entry.path().extension() != ".cfg") continue;
                auto cfg = loader.load(cfg_entry.path().string());
                auto result = engine.run(frames, cfg);
                rows.push_back({dataset_entry.path().filename().string(), cfg_entry.path().filename().string(), result.metrics});
            }
        }
        report.write(output_dir + "/scenario_sweep.md", rows);
        std::ofstream csv(output_dir + "/scenario_sweep.csv");
        csv << "dataset,config,mean_error,id_switches,missed_truth,false_tracks,confirmed,confirm_latency\n";
        for (const auto& row : rows) {
            csv << row.dataset << ',' << row.config_name << ',' << row.metrics.mean_position_error << ','
                << row.metrics.id_switches << ',' << row.metrics.missed_truth_updates << ','
                << row.metrics.false_track_updates << ',' << row.metrics.confirmed_tracks << ','
                << row.metrics.mean_confirm_latency_frames << '\n';
        }
        std::cout << "Scenario sweep written to " << output_dir << "\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
