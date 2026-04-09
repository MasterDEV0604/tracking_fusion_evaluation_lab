cmake_minimum_required(VERSION 3.18)
project(tracking_fusion_evaluation_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(tfel_core
    src/core/Types.cpp
    src/core/Track.cpp
    src/core/TrackManager.cpp
    src/core/TrackingEngine.cpp
    src/filter/LinearTracker2D.cpp
    src/association/Gating.cpp
    src/association/NearestNeighborAssociator.cpp
    src/association/GlobalGreedyAssociator.cpp
    src/association/HungarianAssociator.cpp
    src/fusion/SensorNormalizer.cpp
    src/io/CsvDatasetReader.cpp
    src/io/Config.cpp
    src/io/TrackWriter.cpp
    src/reporting/Metrics.cpp
    src/reporting/MarkdownReport.cpp
)

target_include_directories(tfel_core PUBLIC src)

add_executable(tfel_run_tracker src/apps/run_tracker_main.cpp)
target_link_libraries(tfel_run_tracker PRIVATE tfel_core)

add_executable(tfel_benchmark src/apps/benchmark_main.cpp)
target_link_libraries(tfel_benchmark PRIVATE tfel_core)

add_executable(tfel_compare_configs src/apps/compare_configs_main.cpp)
target_link_libraries(tfel_compare_configs PRIVATE tfel_core)

add_executable(tfel_replay_export src/apps/replay_export_main.cpp)
target_link_libraries(tfel_replay_export PRIVATE tfel_core)

add_executable(tfel_scenario_sweep src/apps/scenario_sweep_main.cpp)
target_link_libraries(tfel_scenario_sweep PRIVATE tfel_core)

enable_testing()
add_executable(tfel_smoke tests/smoke_test.cpp)
target_link_libraries(tfel_smoke PRIVATE tfel_core)
add_test(NAME tfel_smoke COMMAND tfel_smoke)
set_tests_properties(tfel_smoke PROPERTIES WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(tfel_assoc_regression tests/association_regression_test.cpp)
target_link_libraries(tfel_assoc_regression PRIVATE tfel_core)
add_test(NAME tfel_assoc_regression COMMAND tfel_assoc_regression)
set_tests_properties(tfel_assoc_regression PROPERTIES WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
