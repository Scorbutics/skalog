#include <iostream>
#include <sstream>
#include <benchmark/benchmark.h>
#include <Logging/MultiLogger.h>



static void BM_OutputCoutTest(benchmark::State& state) {
    std::stringstream ss;  
    for (auto _ : state) {
          ss << "test" << std::endl;
          //ss << "test" << std::endl;
      }
}

 static void BM_LogInfoTest(benchmark::State& state) {
    using TestLogger = 
        ska::Logger<ska::LogLevel::Info, ska::LogLevel::Error, ska::LogSync>;
    
    auto logger = TestLogger{};
    std::stringstream ss;
    logger.addOutputTarget(ss);
    
    logger.setPattern(ska::LogLevel::Info, "%v");
    
    for(auto _ : state) {
          SKA_LOGC_STATIC(logger, ska::LogLevel::Info, TestLogger) << "test";
       }
 }

static void BM_MultiLoggerInfoTest(benchmark::State& state) {
    using TestLogger = ska::MultiLogger<
        ska::Logger<ska::LogLevel::Warn, ska::LogLevel::Error, ska::LogSync>, 
        ska::Logger<ska::LogLevel::Info, ska::LogLevel::Error, ska::LogSync>
    >;
    
    auto logger = TestLogger{};
    std::stringstream ss;
    logger.get<0>().addOutputTarget(ss);
    logger.get<1>().addOutputTarget(ss);
    
    logger.get<1>().setPattern(ska::LogLevel::Info, "%v");
    
    for(auto _ : state) {
          SKA_LOGC_STATIC(logger, ska::LogLevel::Info, TestLogger) << "test";
       }
 }

BENCHMARK(BM_MultiLoggerInfoTest);
BENCHMARK(BM_LogInfoTest);
BENCHMARK(BM_OutputCoutTest);
BENCHMARK_MAIN();

