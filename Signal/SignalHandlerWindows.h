#pragma once

#ifdef _WIN32
#include <windows.h>
#include <csignal>

#include "SignalHandler.h"

namespace ska {
    namespace process {
        namespace detail {
            std::vector<SignalAction> SIGNAL_ACTIONS_CONTAINER;
            LPTOP_LEVEL_EXCEPTION_FILTER UNHANDLED_EXCEPTION_HANDLER = nullptr;
                    
            LONG WINAPI DefaultSignalHandler(EXCEPTION_POINTERS *info) {
                SetUnhandledExceptionFilter (UNHANDLED_EXCEPTION_HANDLER);
                for (auto& action : SIGNAL_ACTIONS_CONTAINER) {
                    action(0);
                }
                return EXCEPTION_CONTINUE_SEARCH;
            }

            void SignalHandlerAddActionImpl(SignalAction action) {
                SIGNAL_ACTIONS_CONTAINER.push_back(std::move(action));
            }
        }

        void SetupSignalHandler() {
            detail::UNHANDLED_EXCEPTION_HANDLER = SetUnhandledExceptionFilter(detail::DefaultSignalHandler);
        }

		
    }
}
#endif
