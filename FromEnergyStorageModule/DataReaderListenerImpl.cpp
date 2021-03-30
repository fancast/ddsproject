/*
 *
 *
 * Distributed under the OpenDDS License.
 * See: http://www.opendds.org/license.html
 */

#include <ace/Log_Msg.h>
#include <ace/OS_NS_stdlib.h>

#include "DataReaderListenerImpl.h"
#include "EnergyStorageModuleTypeSupportC.h"
#include "EnergyStorageModuleTypeSupportImpl.h"

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
  EnergyStorageModule::EsmSignalDataReader_var reader_i =
    EnergyStorageModule::EsmSignalDataReader::_narrow(reader);

  if (!reader_i) {
    ACE_ERROR((LM_ERROR,
               ACE_TEXT("ERROR: %N:%l: on_data_available() -")
               ACE_TEXT(" _narrow failed!\n")));
    ACE_OS::exit(1);
  }

  EnergyStorageModule::EsmSignal esm_signal;
  DDS::SampleInfo info;

  DDS::ReturnCode_t error = reader_i->take_next_sample(esm_signal, info);

  if (error == DDS::RETCODE_OK) {
    std::cout << "SampleInfo.sample_rank = " << info.sample_rank << std::endl;
    std::cout << "SampleInfo.instance_state = " << info.instance_state << std::endl;

    if (info.valid_data) {
		std::cout << "         power_interface  = " << esm_signal.power_interface.in() << std::endl
			<< "         control_word     = " << esm_signal.control_word.in() << std::endl
			<< "         status           = " << esm_signal.status.in() << std::endl
			<< "         terminal_voltage = " << esm_signal.terminal_voltage << std::endl
			<< "         voltage_unit     = " << esm_signal.voltage_unit.in() << std::endl
			<< "         terminal_current = " << esm_signal.terminal_current << std::endl
			<< "         current_unit     = " << esm_signal.current_unit.in() << std::endl
			<< "         state_of_charge  = " << esm_signal.state_of_charge << std::endl
			<< "         soc_unit         = " << esm_signal.soc_unit.in() << std::endl;

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