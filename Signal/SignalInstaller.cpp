#include "SignalInstaller.h"

std::once_flag ska::loggerdetail::m_installed;

ska::loggerdetail::SignalInstaller::SignalInstaller() {
	std::call_once(m_installed, [] {
		SetupSignalHandler();
	});
}