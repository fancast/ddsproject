// DESCRIPTION:
//      Co-simulation interface through PCIe memory-mapped I/O.
//
// VERSION: 0.1
// Mark Stanovich, FSU-CAPS
// 
// compile command
// ====================================
//      mex -v CXXFLAGS='-fexceptions -fPIC -fno-omit-frame-pointer -pthread -std=c++17' minimal.cpp
//
// Requirements
// ============
//      - Linux
//      - C++17 compiler (support C++ 2017); gcc with version >= 9.0 works.
//      - FPGA inserted in pcie slot
//      - pre-configured (usually by BIOS) memory mapped region on pcie at PCIE_ADDRESS
//
// Overview
// ========
//      Establishes a memory-mapped interface to a fpga connected to the pcie
//      bus. The memory mapping is realized through the "/dev/mem" file, which
//      is Linux specific.
//      Memory mapping in Windows is possible but is less straightforward.

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cstring> // memcpy()
#include <type_traits>
#include <iostream>
using namespace std;

#include "compiler-gcc.h"

#include "gtfpga_helpers.hpp"
#include "gtfpga.cpp"

const off_t PCIE_ADDRESS = get_pci_base_addr();

int main()
{
    auto gtfpga = Gtfpga(PCIE_ADDRESS);
    for (int i=0; i<64; ++i) {
        cout << gtfpga[i] << "\n";
        gtfpga[i] = static_cast<float>(i);
    }
    return 0;
}
