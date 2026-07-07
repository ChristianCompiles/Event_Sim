cmake_minimum_required(VERSION 3.22)
project(Sim)
add_executable(sim)

target_sources(sim
  PRIVATE
    src/main.cpp
    src/buffer.cpp
    src/discrete_event_sim.cpp
    src/machine.cpp
)