#pragma once
#include <mutex>
#include "SignalHandler.h"

namespace ska {
	namespace process {
		class SignalInstaller {
		public:
			SignalInstaller();
		private:
			static std::once_flag m_installed;
		};
	}
}
