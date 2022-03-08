#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cstring> // memcpy()

#include <iostream>
#include <type_traits>
using namespace std;

#include "compiler-gcc.h"

constexpr size_t NR_INPUT_SIGNALS  = 64;
constexpr size_t NR_OUTPUT_SIGNALS = 64;

class Gtfpga {

private:
    int fd;
    volatile void*  _pcie_base_addr;
    volatile float* rtds_data_ptr;
    //float* to_rtds[NR_OUTPUT_SIGNALS];

    
    Gtfpga operator=(const Gtfpga&) = delete;
    //Gtfpga          (const Gtfpga&) = delete;

public:
    Gtfpga(const off_t PCIE_ADDRESS)
        : fd(open("/dev/mem", O_RDWR|O_SYNC))
    {
        // mmap pcie into virtual address space
        // ====================================
        if (this->fd < 0) {
            cout << "failure opening /dev/mem\n" << endl;
        }

        this->_pcie_base_addr = mmap(
            0, getpagesize(),
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            fd,
            PCIE_ADDRESS
        );
        // todo: verify rtds_data_ptr is valid (i.e., mmap did not fail)

        rtds_data_ptr = static_cast<volatile float*>(this->_pcie_base_addr);
    }

    ~Gtfpga()
    {
        munmap((void *)this->_pcie_base_addr, getpagesize());
    }

    auto exchange(const float* to_rtds)
    {
        auto from_rtds = new float[64];

        // exchange input and output signals with other simulator (e.g., RTDS, OPAL-RT)
        // NOTE: assuming all values are of type float
        for (size_t i=0; i<NR_OUTPUT_SIGNALS; ++i) { from_rtds[i]     = rtds_data_ptr[i]; }
        for (size_t i=0; i<NR_INPUT_SIGNALS ; ++i) { rtds_data_ptr[i] = to_rtds[i];       }

        return from_rtds;
    }

    auto get_Base_Address()
    {
        return this->_pcie_base_addr;
    }

    // get
    auto operator[](int key) const
    {
        return this->rtds_data_ptr[key];
    }

    // set
    volatile float& operator[](int key)
    {
        return this->rtds_data_ptr[key];
    }

};
