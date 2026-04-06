#!/usr/bin/env bash
set -euo pipefail
cmake -S . -B build
cmake --build build -j
./build/tfel_run_tracker assets/datasets/harbor_patrol.csv config/balanced.cfg outputs/example_run
./build/tfel_benchmark assets/datasets outputs/benchmark_report
