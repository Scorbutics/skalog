#pragma once
#if defined(unix) || defined(__unix) || defined(__unix__)

#include <csignal>
#include "SignalHandler.h"

namespace ska {
    namespace process {
        namespace detail {
            const int SignalCodeList[] = {
                SIGINT,
                SIGTERM,
                SIGABRT,
                SIGSEGV,
                SIGFPE
            };
    
            void SignalHandlerAddActionImpl(SignalAction action);
        }
    }
}
#endif
