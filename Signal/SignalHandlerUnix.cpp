#include <sstream>
#include <vector>

#include "SignalHandler.h"
#include "SignalHandlerUnix.h"

namespace ska {
    namespace loggerdetail {
        std::vector<SignalAction> SIGNAL_ACTIONS_CONTAINER;

        void DefaultSignalHandler(int signalCode, siginfo_t*, void*) {
            for(auto& action : SIGNAL_ACTIONS_CONTAINER) {
                action(signalCode);
            }
        }
    }
}

void ska::loggerdetail::SignalHandlerAddAction(SignalAction action) {
    SIGNAL_ACTIONS_CONTAINER.push_back(std::move(action));
}

void ska::loggerdetail::SetupSignalHandler() {
    struct sigaction new_action; 
    sigemptyset(&new_action.sa_mask); 
    
    new_action.sa_sigaction = &DefaultSignalHandler; 
    new_action.sa_flags = SA_SIGINFO;

    for(const auto& signalCode : SignalCodeList) {
        if(sigaction (signalCode, &new_action, NULL) < 0) {
            auto ss = std::stringstream{};
            ss << "Error while setting up signal handler for the signal " << signalCode;
            perror(ss.str().c_str());
        }
    }
}
