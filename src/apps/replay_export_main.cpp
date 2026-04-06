#include "core/TrackingEngine.h"
#include "io/Config.h"
#include "io/CsvDatasetReader.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cerr << "Usage: tfel_replay_export <dataset.csv> <config.cfg> <replay.txt>\n";
        return 1;
    }
    try {
        tfel::CsvDatasetReader reader;
        tfel::Config loader;
        tfel::TrackingEngine engine;
        auto frames = reader.read(argv[1]);
        auto cfg = loader.load(argv[2]);
        auto result = engine.run(frames, cfg);
        engine.writeReplay(result.history, argv[3]);
        std::cout << "Replay written to " << argv[3] << "\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 2;
    }
}
