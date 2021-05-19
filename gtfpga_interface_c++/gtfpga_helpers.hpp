#if 1

extern "C" {
    #include <pci/pci.h>
}

auto get_pci_base_addr()
{
    struct pci_access* pciaccess = pci_alloc();

    pci_init(pciaccess);
    pci_scan_bus(pciaccess);

    off_t rtn = 0;
    for(struct pci_dev* dev=pciaccess->devices; dev; dev=dev->next) {
        pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);

        #if 0
            char namebuf[1024];

            pci_lookup_name(pciaccess, namebuf, sizeof(namebuf), PCI_LOOKUP_VENDOR, dev->vendor_id, dev->device_id);
            // "Xilinx Corporation"
            string vendor = namebuf;
            cout << "vendor: " << vendor << endl;

            pci_lookup_name(pciaccess, namebuf, sizeof(namebuf), PCI_LOOKUP_DEVICE, dev->vendor_id, dev->device_id);
            string name = namebuf;
        #endif

        #if 0
            cout << hex << dev->vendor_id << ":" << dev->device_id << endl;
            cout << hex << dev->device_class << endl;
        #endif

        if (dev->vendor_id != 0x10ee || dev->device_id != 0x6011) {
            continue;
        }

        rtn = dev->base_addr[0];
        break;
    }

    pci_cleanup(pciaccess);

    return rtn;
}

#else

// OPTION: obtain PCIE_ADDRESS using the following:
// ================================================
//      - lscpi -v
//      - lspci -v -d 10ee:6011 # to get the specific device
//
//      Example output from 'lscpi -v':
//      ...
//      Memory at 92d00000 (64-bit, non-prefetchable) [size=64K]
//
//      02:00.0 RAM memory: Xilinx Corporation Device 6011
//	        Subsystem: Xilinx Corporation Device 0007
//	        Flags: bus master, fast devsel, latency 0, IRQ 6
//	        Memory at 92b01000 (32-bit, non-prefetchable) [size=512]
//	        Memory at 92b00000 (32-bit, non-prefetchable) [size=512]
//	        Capabilities: <access denied>
auto get_pci_base_addr()
{
    //return static_cast<off_t>(0x91a01000);
    return static_cast<off_t>(0x92b01000);
}

#endif
