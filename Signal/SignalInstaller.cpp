#include "SignalInstaller.h"

std::once_flag ska::process::SignalInstaller::m_installed;

ska::process::SignalInstaller::SignalInstaller() {
	std::call_once(m_installed, [] {
        SetupSignalHandler();
	});
}
