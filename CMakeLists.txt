cmake_minimum_required(VERSION 3.20)
project(<project_name> LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(APPLE AND EXISTS "/opt/homebrew")
    list(PREPEND CMAKE_PREFIX_PATH "/opt/homebrew")
endif()

option(ENABLE_TESTS "Build unit tests" ON)
option(ENABLE_APP "Build app (production CLI)" ON)
option(ENABLE_DEV_MAIN "Build dev_main executable (experiments)" ON)

add_library(core_lib STATIC
        src/core_lib.cpp
        src/graph.cpp
        src/display_box/pretty_display.cpp

        src/shortest_path/dijkstra.cpp
        src/shortest_path/city_with_fewest_neighbors_within_distance_limit.cpp
        src/shortest_path/network_delay_time.cpp
        src/shortest_path/minimum_cost_to_buy_apples.cpp


        src/traversal/dfs.cpp
        src/traversal/bfs.cpp
        src/mst/prim.cpp


        src/traversal/grid_traversal/is_within_bounds.cpp
        src/traversal/grid_traversal/nb_of_islands.cpp
        src/traversal/grid_traversal/fastest_route_to_food.cpp
        src/traversal/grid_traversal/river_sizes.cpp
        src/traversal/grid_traversal/largest_contiguous_land.cpp
        src/traversal/count_city_clusters.cpp
        src/find_center_of_star_graph.cpp
        src/properties/is_bipartite.cpp
        src/properties/optimal_city_pair_road_rank.cpp

        src/builders/build_from_adjecency_list.cpp
        src/builders/build_from_edge_list.cpp
        src/all_paths_from_source_to_target.cpp
        src/ordering/topological_sort_kahn.cpp



        # add more .cpp here as project grows
)

target_include_directories(core_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/header
)

file(GLOB_RECURSE CORE_HEADERS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/header/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/header/*.h"
)
target_sources(core_lib PRIVATE ${CORE_HEADERS})

# --- Production CLI app ---
if(ENABLE_APP AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/app/main.cpp")
    add_executable(app app/main.cpp)
    target_link_libraries(app PRIVATE core_lib)
endif()

# --- Dev / scratch main ---
if(ENABLE_DEV_MAIN AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/app/dev_main.cpp")
    add_executable(dev_main app/dev_main.cpp)
    target_link_libraries(dev_main PRIVATE core_lib)
    target_compile_definitions(dev_main PRIVATE DEV_MAIN_BUILD=1)
endif()

# --- Unit tests ---
if(ENABLE_TESTS AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/unit_tests/CMakeLists.txt")
    enable_testing()
    add_subdirectory(unit_tests)
endif()