#ifdef LOGGER_TEST_MULTI_THREAD
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <mutex>

#include <doctest.h>
#include <Logging/MultiLogger.h>
#include <Logging/LogAsync.h>

TEST_CASE("[MultiLogger] Multi threaded") {
	
	struct MultiLoggerMultiThreadTest;

	using MultiLoggerTest = ska::MultiLogger<
		ska::Logger<ska::LogLevel::Debug, ska::LogLevel::Error, ska::LogAsync>,
		ska::Logger<ska::LogLevel::Debug, ska::LogLevel::Error, ska::LogSync>
	>;

	const auto filename = "toto.txt";
	{
		auto ss = std::ofstream{ filename };

		auto logger = MultiLoggerTest{};
		logger.get<0>().addOutputTarget(ss);
		logger.get<1>().addOutputTarget(ss);

		SKA_LOGC_STATIC(logger, ska::LogLevel::Info, MultiLoggerMultiThreadTest) << "test lolilol " << "tututu " << "turlututu chapeau pointu";
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		logger.terminate();
	}
	{
		auto read = std::ifstream{ filename };
		std::cout << read.rdbuf();
	}

	std::remove(filename);
}
#endif