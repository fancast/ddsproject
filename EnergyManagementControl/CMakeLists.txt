project(OpenDDS_Projects_EnergyManagementControl CXX)
cmake_minimum_required(VERSION 3.8.2)

find_package(OpenDDS REQUIRED)

set(CMAKE_CXX_COMPILER ${OPENDDS_COMPILER})

set(opendds_libs
  OpenDDS::Dcps # Core OpenDDS Library
  OpenDDS::InfoRepoDiscovery OpenDDS::Tcp # For run_test.pl
  OpenDDS::Rtps OpenDDS::Rtps_Udp # For run_test.pl --rtps
)

# Emc Feedback Signals Publisher
add_executable(emc_feedback_publisher
  compiler-gcc.h
  gtfpga_helpers.hpp
  gtfpga.cpp
  EmcFeedbackPublisher.cpp
)
OPENDDS_TARGET_SOURCES(emc_feedback_publisher EmcFeedbackSignals.idl)
target_link_libraries(emc_feedback_publisher -lpci ${opendds_libs} )

# Emc Feedback Signals Subscriber
add_executable(emc_feedback_subscriber
  EmcFeedbackSubscriber.cpp
  EmcFeedbackDataReaderListenerImpl.cpp
)
OPENDDS_TARGET_SOURCES(emc_feedback_subscriber EmcFeedbackSignals.idl)
target_link_libraries(emc_feedback_subscriber ${opendds_libs})

# Emc Command Signals Publisher
add_executable(emc_command_publisher
  compiler-gcc.h
  gtfpga_helpers.hpp
  gtfpga.cpp
  EmcCommandPublisher.cpp
)
OPENDDS_TARGET_SOURCES(emc_command_publisher EmcCommandSignals.idl)
target_link_libraries(emc_command_publisher -lpci ${opendds_libs} )

# Emc Command Signals Subscriber
add_executable(emc_command_subscriber
  EmcCommandSubscriber.cpp
  EmcCommandDataReaderListenerImpl.cpp
)
OPENDDS_TARGET_SOURCES(emc_command_subscriber EmcCommandSignals.idl)
target_link_libraries(emc_command_subscriber ${opendds_libs})
