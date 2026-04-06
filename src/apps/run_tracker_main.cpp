#include "core/TrackingEngine.h"
#include "io/Config.h"
#include "io/CsvDatasetReader.h"
#include "io/TrackWriter.h"
#include <filesystem>
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cerr << "Usage: tfel_run_tracker <dataset.csv> <config.cfg> <output_dir>\n";
        return 1;
    }
    try {
        const std::string dataset = argv[1], cfg_path = argv[2], out_dir = argv[3];
        std::filesystem::create_directories(out_dir);
        tfel::CsvDatasetReader reader;
        tfel::Config loader;
        tfel::TrackingEngine engine;
        tfel::TrackWriter writer;
        auto frames = reader.read(dataset);
        auto cfg = loader.load(cfg_path);
        auto result = engine.run(frames, cfg);
        writer.writeCsv(out_dir + "/tracks.csv", result.history);
        writer.writeSummary(out_dir + "/summary.txt", result.metrics);
        engine.writeReplay(result.history, out_dir + "/replay.txt");
        std::cout << "Wrote outputs to " << out_dir << "\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 2;
    }
}
