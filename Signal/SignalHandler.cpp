#include "SignalHandler.h"
#include "SignalInstaller.h"

#ifdef _WIN32
#include "SignalHandlerWindows.h"
#elif defined(unix) || defined(__unix) || defined(__unix__)
#include "SignalHandlerUnix.h"
#else
#include <iostream>
//Unknown platform, do nothing but log the problem
void SetupSignalHandlerImpl() {
    std::cout << "Warning : no crash handler installed because the platform is unknown." << std::endl;
}
#endif

void ska::loggerdetail::SignalHandlerAddAction(SignalAction action) {
    static SignalInstaller SIGNAL_HANDLER_INSTALLER;
    SignalHandlerAddActionImpl(std::move(action));      
}

