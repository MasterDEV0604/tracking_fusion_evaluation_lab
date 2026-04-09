# Benchmark playbook

1. Choose one or more scenario CSV files.
2. Run `tfel_compare_configs` on a single difficult scenario.
3. Run `tfel_scenario_sweep` across the full dataset set.
4. Inspect `scenario_sweep.csv` and `scenario_sweep.md`.
5. Promote the best config into downstream replay generation.
