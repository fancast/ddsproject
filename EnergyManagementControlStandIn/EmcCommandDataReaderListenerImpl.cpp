/* Data Reader */

#include <ace/Log_Msg.h>
#include <ace/OS_NS_stdlib.h>

#include "EmcCommandDataReaderListenerImpl.h"
#include "EmcCommandSignalsTypeSupportC.h"
#include "EmcCommandSignalsTypeSupportImpl.h"

#include <iostream>

void
DataReaderListenerImpl::on_requested_deadline_missed(
  DDS::DataReader_ptr /*reader*/,
  const DDS::RequestedDeadlineMissedStatus& /*status*/)
{
}

void
DataReaderListenerImpl::on_requested_incompatible_qos(
  DDS::DataReader_ptr /*reader*/,
  const DDS::RequestedIncompatibleQosStatus& /*status*/)
{
}

void
DataReaderListenerImpl::on_sample_rejected(
  DDS::DataReader_ptr /*reader*/,
  const DDS::SampleRejectedStatus& /*status*/)
{
}

void
DataReaderListenerImpl::on_liveliness_changed(
  DDS::DataReader_ptr /*reader*/,
  const DDS::LivelinessChangedStatus& /*status*/)
{
}

void
DataReaderListenerImpl::on_data_available(DDS::DataReader_ptr reader)
{
  EnergyManagementControl::CommandSignalsDataReader_var reader_i =
      EnergyManagementControl::CommandSignalsDataReader::_narrow(reader);

  if (!reader_i) {
    ACE_ERROR((LM_ERROR,
               ACE_TEXT("ERROR: %N:%l: on_data_available() -")
               ACE_TEXT(" _narrow failed!\n")));
    ACE_OS::exit(1);
  }

  EnergyManagementControl::CommandSignals command_signals;
  DDS::SampleInfo info;

  DDS::ReturnCode_t error = reader_i->take_next_sample(command_signals, info);

  if (error == DDS::RETCODE_OK) {
    std::cout << "SampleInfo.sample_rank = " << info.sample_rank << std::endl;
    std::cout << "SampleInfo.instance_state = " << info.instance_state << std::endl;

    if (info.valid_data) {
            std::cout << "         command_signals.name         = " << command_signals.name.in() << std::endl
            << "         command_signals.signal_1     = " << command_signals.signal_1 << std::endl
            << "         command_signals.signal_2     = " << command_signals.signal_2 << std::endl
            << "         command_signals.signal_3     = " << command_signals.signal_3 << std::endl
            << "         command_signals.signal_4     = " << command_signals.signal_4 << std::endl
            << "         command_signals.signal_5     = " << command_signals.signal_5 << std::endl
            << "         command_signals.signal_6     = " << command_signals.signal_6 << std::endl
            << "         command_signals.signal_7     = " << command_signals.signal_7 << std::endl
            << "         command_signals.signal_8     = " << command_signals.signal_8 << std::endl
            << "         command_signals.signal_9     = " << command_signals.signal_9 << std::endl
            << "         command_signals.signal_10    = " << command_signals.signal_10 << std::endl;
    }

  } else {
    ACE_ERROR((LM_ERROR,
               ACE_TEXT("ERROR: %N:%l: on_data_available() -")
               ACE_TEXT(" take_next_sample failed!\n")));
  }
}

void
DataReaderListenerImpl::on_subscription_matched(
  DDS::DataReader_ptr /*reader*/,
  const DDS::SubscriptionMatchedStatus& /*status*/)
{
}

void
DataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr /*reader*/,
  const DDS::SampleLostStatus& /*status*/)
{
}
