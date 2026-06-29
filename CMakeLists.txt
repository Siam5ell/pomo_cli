cmake_minimum_required(VERSION 4.3.2)
set(CMAKE_CXX_STANDARD 20)

project(pomo_cli)
#Main Excutable
add_executable(pomo_cli)
target_sources(pomo_cli
  PRIVATE
  main.cpp
)
target_link_libraries(pomo_cli PRIVATE ncurses)
install(TARGETS pomo_cli
        RUNTIME DESTINATION bin)
#Libraries
# add_library(circuit_network)
# target_sources(circuit_network
#   PRIVATE
#   src/network.cpp
#   PUBLIC
#   FILE_SET basicCircuitHeaders
#   TYPE HEADERS
#   BASE_DIRS
#     include
#   FILES
#     include/network.hpp
# )

#Link libraries
# target_link_libraries(madspice
#   PRIVATE
#   circuit_network
#   solvers
# )


# file (WRITE "${CMAKE_CURRENT_BINARY_DIR}/testfile.cir"
# "This is a test file generated for testing read file functionality."
# )
