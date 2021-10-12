project(OpenDDS_Projects_EnergyManagementControl CXX)
cmake_minimum_required(VERSION 3.8.2)

find_package(OpenDDS REQUIRED)

set(CMAKE_CXX_COMPILER ${OPENDDS_COMPILER})

set(opendds_libs
  OpenDDS::Dcps # Core OpenDDS Library
  OpenDDS::InfoRepoDiscovery OpenDDS::Tcp # For run_test.pl
  OpenDDS::Rtps OpenDDS::Rtps_Udp # For run_test.pl --rtps
)

# Publisher
add_executable(feedback_publisher
  compiler-gcc.h
  gtfpga_helpers.hpp
  gtfpga.cpp
  Publisher.cpp
)
OPENDDS_TARGET_SOURCES(feedback_publisher EmcFeedbackSignals.idl)
target_link_libraries(feedback_publisher -lpci ${opendds_libs} )

# Subscriber
add_executable(feedback_subscriber
  Subscriber.cpp
  DataReaderListenerImpl.cpp
)
OPENDDS_TARGET_SOURCES(feedback_subscriber EmcFeedbackSignals.idl)
target_link_libraries(feedback_subscriber ${opendds_libs})
