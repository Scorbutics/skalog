#pragma once

//Test only
#include <iostream>

#include <windows.h>
#include <csignal>

namespace ska {
    namespace loggerdetail {
		LPTOP_LEVEL_EXCEPTION_FILTER g_previous_unexpected_exception_handler = nullptr;
				
		   // Unhandled exception catching
	    LONG WINAPI DefaultSignalHandler(EXCEPTION_POINTERS *info) {
			SetUnhandledExceptionFilter (g_previous_unexpected_exception_handler);
			
			std::cout << "test handler !!!" << std::endl;
			return EXCEPTION_CONTINUE_SEARCH;
	    }

        void SetupSignalHandlerImpl() {
			g_previous_unexpected_exception_handler = SetUnhandledExceptionFilter(DefaultSignalHandler);
        }
    }
}
