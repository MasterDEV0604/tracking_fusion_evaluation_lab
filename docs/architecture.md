# Architecture

## Repository intent
This repository is split into four layers:

1. **Input layer** – dataset/config ingestion
2. **Fusion + association layer** – normalize detections, gate them, associate them
3. **Tracking layer** – maintain lifecycle, prediction, correction, confirmation/deletion
4. **Reporting layer** – write CSV tracks, replay exports, and benchmark summaries

## Core data flow
`CSV -> frame packet -> normalization -> association -> track update -> metrics/reporting`

## Important design choices
- The filter is intentionally lightweight and readable for interviews.
- Association strategies are swappable through config.
- Metrics are deterministic and dataset-driven so tuning can be discussed concretely.
- Output artifacts are stored as human-readable CSV/Markdown to support recruiter demos.
