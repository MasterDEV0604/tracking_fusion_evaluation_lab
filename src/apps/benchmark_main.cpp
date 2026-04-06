#include "core/TrackingEngine.h"
#include "io/Config.h"
#include "io/CsvDatasetReader.h"
#include "reporting/MarkdownReport.h"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <vector>

static std::vector<std::string> listFiles(const std::string& dir, const std::string& ext) {
    std::vector<std::string> out;
    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.path().extension() == ext) out.push_back(entry.path().string());
    }
    std::sort(out.begin(), out.end());
    return out;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: tfel_benchmark <dataset_dir> <output_dir>\n";
        return 1;
    }
    try {
        const std::string dataset_dir = argv[1], output_dir = argv[2];
        std::filesystem::create_directories(output_dir);
        tfel::CsvDatasetReader reader;
        tfel::Config loader;
        tfel::TrackingEngine engine;
        tfel::MarkdownReport report;
        std::vector<tfel::BenchmarkRow> rows;
        const auto datasets = listFiles(dataset_dir, ".csv");
        const auto configs = listFiles("config", ".cfg");
        for (const auto& dataset : datasets) {
            auto frames = reader.read(dataset);
            for (const auto& cfg_path : configs) {
                auto cfg = loader.load(cfg_path);
                auto result = engine.run(frames, cfg);
                rows.push_back({std::filesystem::path(dataset).filename().string(), std::filesystem::path(cfg_path).filename().string(), result.metrics});
            }
        }
        report.write(output_dir + "/benchmark_summary.md", rows);
        std::cout << "Benchmark report written to " << output_dir << "/benchmark_summary.md\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 2;
    }
}
