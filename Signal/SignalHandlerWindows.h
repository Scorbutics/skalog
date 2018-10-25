#pragma once

#ifdef _WIN32
#include <windows.h>
#include <csignal>

#include "SignalHandler.h"

namespace ska {
    namespace process {
        namespace detail {
			const int SignalCodeList[] = {
                SIGILL,
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
