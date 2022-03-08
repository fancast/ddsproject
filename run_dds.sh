#!/bin/sh
./emc_feedback_publisher -DCPSConfigFile ../rtps.ini &
./emc_command_publisher -DCPSConfigFile ../rtps.ini &
./emc_feedback_subscriber -DCPSConfigFile ../rtps.ini &
./emc_command_subscriber -DCPSConfigFile ../rtps.ini &