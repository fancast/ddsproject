# Minimal Energy Storage Module Example

A minimal OpenDDS version implementing the Energy Storage Module from the 
Notional Four Zone MVDC Shipboard Power System Model in the MDD.

The MDD can be found at:
https://www.esrdc.com/library/notional-four-zone-mvdc-shipboard-power-system-model/

## CMake

There is an example `CMakeLists.txt` provided, but it can conflict with the
default MPC-based build system. If you want to build this example with CMake,
these are the recommend steps:

 - Make sure your environment is set correctly.
 - Clean all the existing build files out of this directory. If this is a git
   repository you can use `git clean -dfX .` in this directory to do this.
   Otherwise at least remove all the `EnergyStorageModule*.h` files, because these will
   conflict even if you do an "out-of-source" build with CMake.
 - Next make a `build` directory in this directory and `cd` to it to do an
   "out-of-source" build.
 - Run `cmake ..` to generate the build and `cmake --build .` to build.
 - To run the example you can run `./publisher -DCPSConfigFile ../rtps.ini` and 
   `./subscriber -DCPSConfigFile ../rtps.ini` at the same time.
