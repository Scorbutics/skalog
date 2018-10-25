#ifdef _WIN32
#include <memory>
#include "SignalHandlerWindows.h"

namespace ska {
	namespace process {
		namespace detail {
			std::unique_ptr<std::vector<SignalAction>> SIGNAL_ACTIONS_CONTAINER;
		}
	}
}

extern "C" void SkaProcessDetailDefaultSignalHandler(int signalCode) {
    for(const auto& action : (*ska::process::detail::SIGNAL_ACTIONS_CONTAINER)) {
        action(signalCode);
    }
}

void ska::process::detail::SignalHandlerAddActionImpl(SignalAction action) {
	SIGNAL_ACTIONS_CONTAINER->push_back(std::move(action));
}

void ska::process::SetupSignalHandler() {
	detail::SIGNAL_ACTIONS_CONTAINER = std::make_unique<std::vector<SignalAction>>();
	for(const auto& signalCode : detail::SignalCodeList) {
		if(signal (signalCode, SkaProcessDetailDefaultSignalHandler) == SIG_ERR) {
			std::cerr << "Error while setting up signal handler for the signal " << signalCode << std::endl;
		}
	}
}
#endif
