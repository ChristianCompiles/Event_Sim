cmake_minimum_required(VERSION 3.22)
project(Sim)
add_executable(sim_exe)

target_sources(sim_exe
  PRIVATE
    src/main.cpp
    src/buffer.cpp
    src/discrete_event_sim.cpp
    src/machine.cpp
)