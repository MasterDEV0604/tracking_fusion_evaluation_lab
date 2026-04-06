#include "reporting/MarkdownReport.h"
#include <fstream>
#include <iomanip>

namespace tfel {

void MarkdownReport::write(const std::string& path, const std::vector<BenchmarkRow>& rows) const {
    std::ofstream out(path);
    out << "# Benchmark Summary\n\n";
    out << "| Dataset | Config | Mean error | ID switches | Tracks created | Unmatched detections | Continuity |\n";
    out << "|---|---:|---:|---:|---:|---:|---:|\n";
    out << std::fixed << std::setprecision(3);
    for (const auto& row : rows) {
        out << '|' << row.dataset << '|' << row.config << '|' << row.metrics.mean_position_error << '|' << row.metrics.id_switches
            << '|' << row.metrics.tracks_created << '|' << row.metrics.unmatched_detections << '|' << row.metrics.track_continuity << "|\n";
    }
}

}
