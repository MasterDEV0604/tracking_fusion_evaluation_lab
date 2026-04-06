#include "io/CsvDatasetReader.h"
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>

namespace tfel {

std::vector<FramePacket> CsvDatasetReader::read(const std::string& path) const {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Failed to open dataset: " + path);
    std::string line;
    std::getline(in, line); // header
    std::map<int, FramePacket> frames;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string tok;
        Detection d;
        std::getline(ss, tok, ','); d.frame = std::stoi(tok);
        std::getline(ss, tok, ','); d.time = std::stod(tok);
        std::getline(ss, tok, ','); d.source = tok;
        std::getline(ss, tok, ','); d.x = std::stod(tok);
        std::getline(ss, tok, ','); d.y = std::stod(tok);
        std::getline(ss, tok, ','); d.confidence = std::stod(tok);
        std::getline(ss, tok, ','); d.truth_id = std::stoi(tok);
        auto& packet = frames[d.frame];
        packet.frame = d.frame;
        packet.time = d.time;
        packet.detections.push_back(d);
    }
    std::vector<FramePacket> out;
    for (auto& kv : frames) out.push_back(kv.second);
    return out;
}

}
