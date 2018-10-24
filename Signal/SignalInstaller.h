#pragma once
#include <mutex>
#include "SignalHandler.h"

namespace ska {
	namespace loggerdetail {
		class SignalInstaller {
		public:
			SignalInstaller();
		private:
			static std::once_flag m_installed;
		};
	}
}
