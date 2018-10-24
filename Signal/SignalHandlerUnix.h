#pragma once
#include <csignal>
#include "SignalHandler.h"

namespace ska {
    namespace loggerdetail {

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
