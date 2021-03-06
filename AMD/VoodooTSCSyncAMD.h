/**
 * Modified VoodooTSCSync for AMD by fumoboy007
 *
 * This is a version of VoodooTSCSync modified to intermittently sync.
 */

#include <IOKit/IOService.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOTimerEventSource.h>
#include <i386/proc_reg.h>

#define MSR_TSC 0x00000010 // Reg define
#define SYNC_INTERVAL 10000 // In milliseconds

// External function defined in mp.c from xnu
extern "C" void mp_rendezvous_no_intrs(void (*action_func)(void *), void *arg);
// Needs to be in the same scope as mp_rendezvous_no_intrs
extern "C" void stamp_tsc(void *tscp);

class org_voodoo_driver_VoodooTSCSyncAMD : public IOService
{
    OSDeclareDefaultStructors(org_voodoo_driver_VoodooTSCSyncAMD)
private:
    IOWorkLoop* myWorkLoop;
    IOTimerEventSource* myTimer;
    
    void syncTSC();
    
public:
    virtual bool start(IOService *provider);
    virtual void stop(IOService *provider);
};
