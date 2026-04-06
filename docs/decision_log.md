# Decision log

## ADR-001: Keep the core dependency-light
Reason: easier to build, easier to review, and more credible as a self-owned portfolio project.

## ADR-002: Include multiple apps instead of a single monolithic binary
Reason: mirrors internal tooling where batch evaluation, replay, and one-off analysis are separate workflows.

## ADR-003: Prefer readable metrics over mathematically exhaustive evaluation
Reason: the repo is intended for recruiter and interview review, so clarity and reproducibility matter most.
