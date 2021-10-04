/* Data Reader derived from the EsmFeedbackSignals IDL example */

#include <ace/Log_Msg.h>
#include <ace/OS_NS_stdlib.h>

#include "DataReaderListenerImpl.h"
#include "EsmFeedbackSignalsTypeSupportC.h"
#include "EsmFeedbackSignalsTypeSupportImpl.h"

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
  EnergyStorageModule::FeedbackSignalsDataReader_var reader_i =
    EnergyStorageModule::FeedbackSignalsDataReader::_narrow(reader);

  if (!reader_i) {
    ACE_ERROR((LM_ERROR,
               ACE_TEXT("ERROR: %N:%l: on_data_available() -")
               ACE_TEXT(" _narrow failed!\n")));
    ACE_OS::exit(1);
  }

  EnergyStorageModule::FeedbackSignals feedback_signals;
  DDS::SampleInfo info;

  DDS::ReturnCode_t error = reader_i->take_next_sample(feedback_signals, info);

  if (error == DDS::RETCODE_OK) {
    std::cout << "SampleInfo.sample_rank = " << info.sample_rank << std::endl;
    std::cout << "SampleInfo.instance_state = " << info.instance_state << std::endl;

    if (info.valid_data) {
            std::cout << "         feedback_signals.name                = " << feedback_signals.name.in() << std::endl
            << "         feedback_signals.isolation_status    = " << feedback_signals.isolation_status << std::endl
            << "         feedback_signals.terminal_voltage_kV = " << feedback_signals.terminal_voltage_kV << std::endl
            << "         feedback_signals.terminal_current_kA = " << feedback_signals.terminal_current_kA << std::endl
            << "         feedback_signals.state_of_charge_pu  = " << feedback_signals.state_of_charge_pu << std::endl;
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
