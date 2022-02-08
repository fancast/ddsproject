/* Data Reader */

#include <ace/Log_Msg.h>
#include <ace/OS_NS_stdlib.h>

#include "EmcFeedbackDataReaderListenerImpl.h"
#include "EmcFeedbackSignalsTypeSupportC.h"
#include "EmcFeedbackSignalsTypeSupportImpl.h"

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
  EnergyManagementControl::FeedbackSignalsDataReader_var reader_i =
      EnergyManagementControl::FeedbackSignalsDataReader::_narrow(reader);

  if (!reader_i) {
    ACE_ERROR((LM_ERROR,
               ACE_TEXT("ERROR: %N:%l: on_data_available() -")
               ACE_TEXT(" _narrow failed!\n")));
    ACE_OS::exit(1);
  }

  EnergyManagementControl::FeedbackSignals feedback_signals;
  DDS::SampleInfo info;

  DDS::ReturnCode_t error = reader_i->take_next_sample(feedback_signals, info);

  if (error == DDS::RETCODE_OK) {
    //std::cout << "SampleInfo.sample_rank = " << info.sample_rank << std::endl;
    //std::cout << "SampleInfo.instance_state = " << info.instance_state << std::endl;

    if (info.valid_data) {
            //std::cout << "         feedback_signals.name        = " << feedback_signals.name.in() << std::endl
            //<< "         feedback_signals.signal_1    = " << feedback_signals.signal_1 << std::endl
            //<< "         feedback_signals.signal_2    = " << feedback_signals.signal_2 << std::endl;
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
