#pragma once
#include <csignal>

namespace ska {
    namespace loggerdetail {
        void DefaultSignalHandler(int, siginfo_t*, void*) {

        }

        void SetupSignalHandlerImpl() {
            struct sigaction action; 
            sigemptyset(&action.sa_mask); 
            action.sa_sigaction = &DefaultSignalHandler; 
            // callback to crashHandler for fatal signals 
            
            // sigaction to use sa_sigaction file. ref: http://www.linuxprogrammingblog.com/code-examples/sigaction 
            action.sa_flags = SA_SIGINFO; 
        }
    }
}
