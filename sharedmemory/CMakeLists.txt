project(OpenDDS_Projects_EnergyManagementControl CXX)
cmake_minimum_required(VERSION 3.8.2)

find_package(OpenDDS REQUIRED)

set(CMAKE_CXX_COMPILER ${OPENDDS_COMPILER})

# Publisher
add_executable(smio
  sharedmemory.cpp
  #rts.cpp
  #emc.cpp
  main.cpp
)
target_link_libraries(smio -lpci)