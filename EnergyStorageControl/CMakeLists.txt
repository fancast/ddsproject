project(OpenDDS_Projects_EnergyStorageModule CXX)
cmake_minimum_required(VERSION 3.8.2)

find_package(OpenDDS REQUIRED)

set(CMAKE_CXX_COMPILER ${OPENDDS_COMPILER})

set(opendds_libs
  OpenDDS::Dcps # Core OpenDDS Library
  OpenDDS::InfoRepoDiscovery OpenDDS::Tcp # For run_test.pl
  OpenDDS::Rtps OpenDDS::Rtps_Udp # For run_test.pl --rtps
)

# Esm Feedback Signals Publisher
add_executable(esm_feedback_publisher
  compiler-gcc.h
  gtfpga_helpers.hpp
  gtfpga.cpp
  EsmFeedbackPublisher.cpp
  #new subscriber
  EsmFeedbackSubscriber.cpp
  EsmFeedbackDataReaderListenerImpl.cpp
)
OPENDDS_TARGET_SOURCES(esm_feedback_publisher EsmFeedbackSignals.idl)
target_link_libraries(esm_feedback_publisher -lpci ${opendds_libs} )

# Esm Feedback Signals Subscriber
add_executable(esm_feedback_subscriber
  EsmFeedbackSubscriber.cpp
  EsmFeedbackDataReaderListenerImpl.cpp
)
OPENDDS_TARGET_SOURCES(esm_feedback_subscriber EsmFeedbackSignals.idl)
target_link_libraries(esm_feedback_subscriber ${opendds_libs})

# Esm Command Signals Publisher
add_executable(esm_command_publisher
  compiler-gcc.h
  gtfpga_helpers.hpp
  gtfpga.cpp
  EsmCommandPublisher.cpp
  #new subscriber
  EsmCommandSubscriber.cpp
  EsmCommandDataReaderListenerImpl.cpp
)
OPENDDS_TARGET_SOURCES(esm_command_publisher EsmCommandSignals.idl)
target_link_libraries(esm_command_publisher -lpci ${opendds_libs} )

# Esm Command Signals Subscriber
add_executable(esm_command_subscriber
  EsmCommandSubscriber.cpp
  EsmCommandDataReaderListenerImpl.cpp
)
OPENDDS_TARGET_SOURCES(esm_command_subscriber EsmCommandSignals.idl)
target_link_libraries(esm_command_subscriber ${opendds_libs})