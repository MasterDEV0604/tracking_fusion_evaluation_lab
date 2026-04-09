# Tracking Fusion Evaluation Lab — Fantastic Edition

Tracking Fusion Evaluation Lab is a **C++17 tracking and fusion evaluation framework** designed to feel like a real internal autonomy R&D tool rather than a small demo.

It answers a practical engineering question:

> Which association, motion-model, and confidence-scaling choices produce the most stable tracks under clutter, crossing targets, and mixed sensor quality?

## What makes this version stronger

- three association strategies: nearest, global-greedy, and hungarian-style assignment
- multiple runnable tools for tracking, benchmarking, replay export, and scenario sweeps
- config-driven experiments with mixed sensor reliability tuning
- richer metrics: mean error, ID switches, missed truth updates, false-track updates, confirm latency
- example datasets, reports, and outputs already included
- docs that explain architecture, evaluation method, and design decisions
- tests and CI for a believable engineering workflow

## Applications

| App | Purpose |
|---|---|
| `tfel_run_tracker` | Run one tracker config on one dataset and export tracks + summary |
| `tfel_benchmark` | Benchmark every dataset against every config and emit markdown summary |
| `tfel_compare_configs` | Compare a set of configs on one scenario |
| `tfel_replay_export` | Produce frame-by-frame replay text for mission/debrief consumption |
| `tfel_scenario_sweep` | Run config sweeps over all scenarios and write leaderboard artifacts |

## Repo story

This project is the **technical engine** in a larger autonomy-software portfolio:
- a perception lab generates candidate detections
- this repo normalizes, associates, and tracks them
- a mission-control workstation can consume replay and report outputs

## Build

```bash
cmake -S . -B build
cmake --build build -j
ctest --test-dir build --output-on-failure
```

## Quick start

```bash
./build/tfel_run_tracker assets/datasets/harbor_patrol.csv config/fusion_balanced.cfg outputs/example_run
./build/tfel_benchmark assets/datasets outputs/benchmark_report
./build/tfel_compare_configs assets/datasets/intersection_conflict.csv config/aggressive.cfg config/fusion_balanced.cfg config/crowded_scene.cfg
./build/tfel_replay_export assets/datasets/urban_convoy.csv config/fusion_balanced.cfg outputs/urban_replay.txt
./build/tfel_scenario_sweep assets/datasets config outputs/scenario_sweep
```

## Fantastic upgrade ideas already reflected here

- experiment-style dataset folders and scenario naming
- a third assignment mode for crowded scenes
- stronger benchmark and comparison artifacts for README screenshots
- latency and false-track metrics that better match real tracker tuning work
- outputs meant to feed a GUI mission workstation later

## Good GitHub screenshots to add later

- benchmark summary table
- comparison CSV plotted as a bar chart
- replay excerpt next to a scenario explanation
- track lifetime chart and false-track count by config

## Suggested interview pitch

> I built a configurable C++ tracking/fusion evaluation framework that lets me compare association strategies, motion assumptions, and sensor confidence scaling across multiple scenarios. I used it to study tradeoffs like ID stability versus false-track growth and to generate artifacts that can feed a mission-control GUI.
