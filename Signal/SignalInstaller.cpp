#include "SignalInstaller.h"

//Test only
#include <iostream>

std::once_flag ska::loggerdetail::SignalInstaller::m_installed;

ska::loggerdetail::SignalInstaller::SignalInstaller() {
	std::call_once(m_installed, [] {
            std::cout << "\t\t installing signal handler" << std::endl << std::endl;
        SetupSignalHandler();
	});
}
