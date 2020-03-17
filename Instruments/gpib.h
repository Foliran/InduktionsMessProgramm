#ifndef GPIB_H
#define GPIB_H

#include <string>
#include <map>
#include "Instruments_global.h"

#ifdef __cplusplus
extern "C" {
#endif
#include <windows.h>
#include "C:\Program Files (x86)\National Instruments\Shared\ExternalCompilerSupport\C\include\ni488.h"
#ifdef __cplusplus
}
#endif

class INSTRUMENTS_EXPORT GPIB
{
public:
    GPIB();

    void openDevice(int deviceAddress);
    bool isOpen(int deviceAddress) const;

    void cmd(int deviceAddress, std::string command);
    std::string query(int deviceAddress, std::string queryStr);

private:
    void init();
    int getHandle(int address) const;

private:
    int* ibsta_;
    long* ibcntl_;
    int* iberr_;
    int(__stdcall *ibclr_)(int ud);
    int(__stdcall *ibdev_)(int ud, int pad, int sad, int tmo, int eot, int eos);
    int(__stdcall *ibconfig_)(int ud, int option, int v);
    int(__stdcall *ibrd_)(int ud, PVOID buf, LONG cnt);
    int(__stdcall *ibwrt_)(int ud, PVOID buf, LONG cnt);

    std::map<int, int> deviceHandles_;
    char readBuffer_[512];

    std::string checkStatus(int ibsta);
};

#endif // GPIB_H
