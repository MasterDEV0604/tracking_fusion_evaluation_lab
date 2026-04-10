# Tracking Fusion Evaluation Lab

Tracking Fusion Evaluation Lab is a **C++17 framework for multi-target tracking, association strategy comparison, and sensor-fusion evaluation**.

It is built for engineers who need to run repeatable experiments on how different assignment methods, motion assumptions, and confidence settings behave under clutter, crossing targets, missed detections, and mixed sensor quality.

## Highlights

- **Config-driven experiments** for repeatable tracker runs
- **Multiple association strategies** including nearest, global-greedy, and hungarian-style assignment
- **Benchmark and comparison tooling** for evaluating tracker behavior across datasets and configurations
- **Replay export pipeline** for inspection or downstream visualization
- **Scenario sweep support** for leaderboard-style experiment batches
- **Structured outputs** including reports, summaries, metrics, and replay artifacts
- **Tested C++ core** designed for extension into richer fusion pipelines

## Core capabilities

### Tracking and association
- normalize incoming detections from different sensor sources
- maintain track state over time
- associate detections to tracks using multiple strategies
- tune behavior through configuration files

### Benchmarking and comparison
- run a single tracker configuration on one dataset
- compare multiple configurations on a selected scenario
- execute broad scenario sweeps across available datasets
- generate reports suitable for engineering review

### Reporting and downstream use
- export track summaries and run metrics
- generate replay artifacts for visualization or playback tooling
- compare results across configurations and scenarios

## Applications

| Application | Description |
|---|---|
| `tfel_run_tracker` | Runs one configuration against one dataset and writes tracking outputs |
| `tfel_benchmark` | Benchmarks datasets and configurations and produces summary artifacts |
| `tfel_compare_configs` | Compares multiple tracker configurations on the same scenario |
| `tfel_replay_export` | Exports frame-level replay data for visualization or review |
| `tfel_scenario_sweep` | Executes scenario/config sweeps and generates leaderboard-style output |

## Repository layout

```text
src/
  core/                   Tracking, association, filtering, normalization
  io/                     Dataset loading and report writing
  apps/                   CLI entry points
config/                   Tracker configurations
assets/datasets/          Example tracking scenarios
outputs/                  Example benchmark and replay artifacts
docs/                     Architecture, methodology, playbooks, ADRs
tests/                    Unit and smoke tests
scripts/                  Helper scripts for reproducible runs
```

## Build

### Requirements
- CMake 3.20 or newer
- C++17 compiler

### Configure, build, and test
```bash
cmake -S . -B build
cmake --build build -j
ctest --test-dir build --output-on-failure
```

## Quick start

Run a single configuration:

```bash
./build/tfel_run_tracker assets/datasets/harbor_patrol.csv config/fusion_balanced.cfg outputs/example_run
```

Benchmark a set of scenarios:

```bash
./build/tfel_benchmark assets/datasets outputs/benchmark_report
```

Compare configurations on one scenario:

```bash
./build/tfel_compare_configs \
  assets/datasets/intersection_conflict.csv \
  config/aggressive.cfg \
  config/fusion_balanced.cfg \
  config/crowded_scene.cfg
```

Export replay data:

```bash
./build/tfel_replay_export \
  assets/datasets/urban_convoy.csv \
  config/fusion_balanced.cfg \
  outputs/urban_replay.txt
```

Run a sweep across scenarios and configurations:

```bash
./build/tfel_scenario_sweep assets/datasets config outputs/scenario_sweep
```

## Metrics and artifacts

Typical generated outputs include:

- track summaries
- benchmark markdown reports
- comparison tables
- replay exports
- leaderboard-style scenario sweep results
- metrics such as mean error, ID switches, missed truth updates, false-track updates, and confirmation latency

## Engineering goals

Tracking Fusion Evaluation Lab is intended to support:

- tracker tuning and regression checking
- comparison of assignment strategies
- evaluation under dense or ambiguous target motion
- experimentation with confidence scaling and motion assumptions
- integration with higher-level mission visualization or analytics systems

## Documentation

Additional documentation is available in:

- `docs/architecture.md`
- `docs/evaluation_methodology.md`
- `docs/benchmark_playbook.md`
- `docs/adr/`

## Roadmap

Planned areas of expansion include:

- richer motion-model selection
- probabilistic data association variants
- additional sensor adapters and fusion experiments
- timing/performance dashboards
- visual replay front ends and chart generation

## Notes

Bundled datasets are synthetic evaluation scenarios intended for development, benchmarking, and reproducible testing.
