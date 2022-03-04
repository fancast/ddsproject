# Minimal Energy Management Control

This repository contains the minimal working example of an energy management control
that receives command signals and sends feedback signals. There are two feedback signals
that are added together to produce the command signal.

## CMake
There is an example `CMakeLists.txt` provided, but it can conflict with the
default MPC-based build system. If you want to build this example with CMake,
these are the recommend steps:

 - Make sure your environment is set correctly.
 - Clean all the existing build files out of this directory. If this is a git
   repository you can use `git clean -dfX .` in this directory to do this.
 - Next make a `build` directory in this directory and `cd` to it to do an
   "out-of-source" build. This is accomplished by executing the commands
   on linux: 'mkdir build' and 'cd build'
 - Run `cmake ../` to generate the build and `cmake --build .` to build.
   `make` can also be used instead of `cmake --build .`
 - To run the example you can run `./emc_feedback_publisher -DCPSConfigFile ../rtps.ini`, `./emc_feedback_subscriber
   -DCPSConfigFile ../rtps.ini`, `./emc_command_publisher -DCPSConfigFile ../rtps.ini`, and `./emc_command_subscriber
   -DCPSConfigFile ../rtps.ini` at the same time.
