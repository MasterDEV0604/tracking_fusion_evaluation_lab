# Tracking Fusion Evaluation Lab

Tracking Fusion Evaluation Lab is a **C++17** flagship portfolio project for multi-target tracking, sensor normalization, data association, filtering, replay export, and benchmark-style evaluation.

It is designed as the **technical engine** companion to a mission-control GUI project: detections come in from radar/camera-like sources, are normalized and associated into tracks, and are exported for replay, reporting, and parameter comparison.

## Why this repo is stronger than a demo

This repository is structured like an internal engineering tool rather than a single algorithm exercise:
- multiple command-line applications
- reusable core library
- scenario configs and benchmark runs
- reproducible output artifacts
- metrics and comparison reports
- architecture and decision docs
- tests and CI

## Main capabilities

- CSV dataset ingestion with mixed sensor sources
- configurable gating and promotion/deletion thresholds
- nearest-neighbor and global-greedy association modes
- constant-velocity and damped-velocity prediction choices
- simple sensor normalization for radar/camera confidence weighting
- confirmed/tentative track lifecycle handling
- benchmark batch runner with metrics and markdown summaries
- replay export for operator-style review

## Applications

| App | Purpose |
|---|---|
| `tfel_run_tracker` | Run one config on one dataset and export tracks and summary files |
| `tfel_benchmark` | Run all datasets/configs and produce leaderboard-style metrics |
| `tfel_compare_configs` | Compare multiple configs on a single dataset |
| `tfel_replay_export` | Export frame-by-frame replay text for debrief review |

## Build

```bash
cmake -S . -B build
cmake --build build -j
ctest --test-dir build --output-on-failure
```

## Quick start

```bash
./build/tfel_run_tracker assets/datasets/harbor_patrol.csv config/balanced.cfg outputs/example_run
./build/tfel_benchmark assets/datasets outputs/benchmark_report
./build/tfel_compare_configs assets/datasets/intersection_conflict.csv config/aggressive.cfg config/balanced.cfg config/conservative.cfg
./build/tfel_replay_export assets/datasets/harbor_patrol.csv config/balanced.cfg outputs/example_run/replay.txt
```

## Portfolio story

This repo helps you explain:
- how detections from different sources are normalized
- why association strategy matters during crossing targets
- how tuning affects false tracks versus missed tracks
- how you evaluate tracker behavior instead of only “running the filter”
- how this technical engine can feed a larger mission or autonomy workstation

## Recommended screenshots / future add-ons

- benchmark result chart
- replay snapshot viewer
- per-track lifetime plot
- confusion summary between configs
- optional Qt/ImGui visualizer as a separate frontend
