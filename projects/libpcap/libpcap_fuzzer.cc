#include <stdint.h>
#include <fstream>
#include <iostream>

#include <pcap/pcap.h>


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    static const std::string filename = "temp.pcap";
    std::ofstream file(filename,
                       std::ios::binary | std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        return 0;
    }
    file.write(reinterpret_cast<const char *>(data), size);
    file.close();

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *p = pcap_open_offline(filename.c_str(), errbuf);
    if (p) {
        struct pcap_pkthdr *header;
        const u_char *pkt_data;
        while (pcap_next_ex(p, &header, &pkt_data) == 1) {}

        pcap_close(p);
    }
    return 0;
}
