#include "SignalHandler.h"

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

