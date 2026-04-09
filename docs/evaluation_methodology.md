# Evaluation methodology

This repo treats tracker quality as an engineering tradeoff, not a single scalar score.

## Core metrics
- Mean position error
- ID switches
- Missed truth updates
- False-track updates
- Mean confirmation latency

## Why these metrics matter
Low mean error can still hide brittle identity maintenance. Likewise, aggressive association may reduce misses but inflate false-track behavior. The benchmark tools in this repo are intended to surface those tradeoffs clearly enough for tuning and review.
