#include "reporting/MarkdownReport.h"
#include <fstream>
#include <iomanip>

namespace tfel {

void MarkdownReport::write(const std::string& path, const std::vector<BenchmarkRow>& rows) const {
    std::ofstream out(path);
    out << "# Tracking Fusion Benchmark Summary\n\n";
    out << "| Dataset | Config | Mean Error | ID Switches | Missed Truth Updates | False Track Updates | Confirmed Tracks | Confirm Latency |\n";
    out << "|---|---|---:|---:|---:|---:|---:|---:|\n";
    out << std::fixed << std::setprecision(2);
    for (const auto& row : rows) {
        out << "| " << row.dataset << " | " << row.config_name << " | "
            << row.metrics.mean_position_error << " | "
            << row.metrics.id_switches << " | "
            << row.metrics.missed_truth_updates << " | "
            << row.metrics.false_track_updates << " | "
            << row.metrics.confirmed_tracks << " | "
            << row.metrics.mean_confirm_latency_frames << " |\n";
    }
}

}
