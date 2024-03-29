/* Publisher */

#include <ace/Log_Msg.h>

#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>

#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/WaitSet.h>

#include <dds/DCPS/StaticIncludes.h>
#ifdef ACE_AS_STATIC_LIBS
#  include <dds/DCPS/RTPS/RtpsDiscovery.h>
#  include <dds/DCPS/transport/rtps_udp/RtpsUdp.h>
#endif

#include "EmcFeedbackSignalsTypeSupportImpl.h"
#include <iostream>
// include for writing files
#include <fstream>

// included for fpga interface
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cstring> // memcpy()
#include <type_traits>

//include for clock
#include <chrono>

#include "compiler-gcc.h"
#include "gtfpga_helpers.hpp"
#include "gtfpga.cpp"

const off_t PCIE_ADDRESS = get_pci_base_addr();

int
ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
  try {
    // Initialize DomainParticipantFactory
    DDS::DomainParticipantFactory_var dpf =
      TheParticipantFactoryWithArgs(argc, argv);

    // Create DomainParticipant
    DDS::DomainParticipant_var participant =
      dpf->create_participant(42,
                              PARTICIPANT_QOS_DEFAULT,
                              0,
                              OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    if (!participant) {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("ERROR: %N:%l: main() -")
                        ACE_TEXT(" create_participant failed!\n")),
                       1);
    }

    // Register TypeSupport (EnergyManagementControl::FeedbackSignals)
    EnergyManagementControl::FeedbackSignalsTypeSupport_var ts =
      new EnergyManagementControl::FeedbackSignalsTypeSupportImpl;

    if (ts->register_type(participant, "") != DDS::RETCODE_OK) {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("ERROR: %N:%l: main() -")
                        ACE_TEXT(" register_type failed!\n")),
                       1);
    }

    // Create Topic (Energy Management Control Signals)
    CORBA::String_var type_name = ts->get_type_name();
    DDS::Topic_var topic =
      participant->create_topic("Energy Management Control Feedback Signals",
                                type_name,
                                TOPIC_QOS_DEFAULT,
                                0,
                                OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    if (!topic) {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("ERROR: %N:%l: main() -")
                        ACE_TEXT(" create_topic failed!\n")),
                       1);
    }

    // Create Publisher
    DDS::Publisher_var publisher =
      participant->create_publisher(PUBLISHER_QOS_DEFAULT,
                                    0,
                                    OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    if (!publisher) {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("ERROR: %N:%l: main() -")
                        ACE_TEXT(" create_publisher failed!\n")),
                       1);
    }

    // Create DataWriter
    DDS::DataWriterQos writer_qos;
    publisher->get_default_datawriter_qos(writer_qos);
    writer_qos.reliability.kind = DDS::RELIABLE_RELIABILITY_QOS;
    writer_qos.resource_limits.max_samples_per_instance = 1;

    DDS::DataWriter_var writer =
      publisher->create_datawriter(topic,
                                   writer_qos,
                                   0,
                                   OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    if (!writer) {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("ERROR: %N:%l: main() -")
                        ACE_TEXT(" create_datawriter failed!\n")),
                       1);
    }

    EnergyManagementControl::FeedbackSignalsDataWriter_var feedback_signals_writer =
        EnergyManagementControl::FeedbackSignalsDataWriter::_narrow(writer);

    if (!feedback_signals_writer) {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("ERROR: %N:%l: main() -")
                        ACE_TEXT(" _narrow failed!\n")),
                       1);
    }

    // Block until Subscriber is available
    DDS::StatusCondition_var condition = writer->get_statuscondition();
    condition->set_enabled_statuses(DDS::PUBLICATION_MATCHED_STATUS);

    DDS::WaitSet_var ws = new DDS::WaitSet;
    ws->attach_condition(condition);

    while (true) {
      DDS::PublicationMatchedStatus matches;
      if (writer->get_publication_matched_status(matches) != ::DDS::RETCODE_OK) {
        ACE_ERROR_RETURN((LM_ERROR,
                          ACE_TEXT("ERROR: %N:%l: main() -")
                          ACE_TEXT(" get_publication_matched_status failed!\n")),
                         1);
      }

      if (matches.current_count >= 1) {
        break;
      }

      DDS::ConditionSeq conditions;
      DDS::Duration_t timeout = { DDS::DURATION_INFINITE_SEC, DDS::DURATION_INFINITE_NSEC };
      if (ws->wait(conditions, timeout) != DDS::RETCODE_OK) {
        ACE_ERROR_RETURN((LM_ERROR,
                          ACE_TEXT("ERROR: %N:%l: main() -")
                          ACE_TEXT(" wait failed!\n")),
                         1);
      }
    }

    ws->detach_condition(condition);

    // Write samples
    EnergyManagementControl::FeedbackSignals feedback_signals;
	auto gtfpga = Gtfpga(PCIE_ADDRESS);
    //auto t_start = std::chrono::high_resolution_clock::now();
    ofstream rtt;
    rtt.open("rtt_feedback.txt");
	feedback_signals.name = "P1";
	feedback_signals.signal_1 = 1.0001;
    feedback_signals.signal_2 = 2.0002;
    gtfpga[0] = static_cast<float>(feedback_signals.signal_1);
    gtfpga[1] = static_cast<float>(feedback_signals.signal_2);
    //auto t_end = std::chrono::high_resolution_clock::now();
    //double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();

    while (true) {
      //t_start = std::chrono::high_resolution_clock::now();
      //clock_time = std::chrono::system_clock::now();
      DDS::ReturnCode_t error = feedback_signals_writer->write(feedback_signals, DDS::HANDLE_NIL);
      feedback_signals.signal_1 = feedback_signals.signal_1 + 0.0001;
      feedback_signals.signal_2 = feedback_signals.signal_2 + 0.0001;
      gtfpga[0] = static_cast<float>(feedback_signals.signal_1);
      gtfpga[1] = static_cast<float>(feedback_signals.signal_2);

      if (error != DDS::RETCODE_OK) {
        ACE_ERROR((LM_ERROR,
                   ACE_TEXT("ERROR: %N:%l: main() -")
                   ACE_TEXT(" write returned %d!\n"), error));
      }
      //t_end = std::chrono::high_resolution_clock::now();
      //elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
      rtt << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count() << "\n";
      //std::cout << "    Signal Round Trip Time (ms)    = " << elapsed_time_ms << std::endl;
    }
    rtt.close();

    // Wait for samples to be acknowledged
    DDS::Duration_t timeout = { DDS::DURATION_INFINITE_SEC, DDS::DURATION_INFINITE_NSEC };
    if (feedback_signals_writer->wait_for_acknowledgments(timeout) != DDS::RETCODE_OK) {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("ERROR: %N:%l: main() -")
                        ACE_TEXT(" wait_for_acknowledgments failed!\n")),
                       1);
    }

    // Clean-up!
    participant->delete_contained_entities();
    dpf->delete_participant(participant);

    TheServiceParticipant->shutdown();

  } catch (const CORBA::Exception& e) {
    e._tao_print_exception("Exception caught in main():");
    return 1;
  }

  return 0;
}
