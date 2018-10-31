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
    std::cout << ss.str().substr(0, 10);
}

using TestLogger = 
        ska::Logger<ska::LogLevel::Info, ska::LogLevel::Error, ska::LogSync>;
   


TestLogger MakeTestLogger(std::stringstream& ss) {
    auto logger = TestLogger{};
        logger.addOutputTarget(ss);
        logger.setPattern(ska::LogLevel::Info, "%v");
    return logger;
}
        
 static void BM_LogInfoTest(benchmark::State& state) {
     std::stringstream ss;
    auto logger = MakeTestLogger(ss);

    for(auto _ : state) {
          SKA_LOGC_STATIC(logger, ska::LogLevel::Info, TestLogger) << "test";
       }
    std::cout << ss.str().substr(0, 10);
 }

static void BM_MultiLoggerInfoTest(benchmark::State& state) {
    using TestMultiLogger = ska::MultiLogger<
        ska::Logger<ska::LogLevel::Warn, ska::LogLevel::Error, ska::LogSync>, 
        ska::Logger<ska::LogLevel::Info, ska::LogLevel::Error, ska::LogSync>
    >;
    
    auto logger2 = TestMultiLogger{};
    std::stringstream ss;
    logger2.get<0>().addOutputTarget(ss);
    logger2.get<1>().addOutputTarget(ss);
    
    logger2.get<1>().setPattern(ska::LogLevel::Info, "%v");
    
    for(auto _ : state) {
          SKA_LOGC_STATIC(logger2, ska::LogLevel::Info, TestMultiLogger) << "test";
       }
    std::cout << ss.str().substr(0, 10);
 }

static void BM_LoggerErrorTest(benchmark::State& state) {
    using TestLoggerError = ska::Logger<ska::LogLevel::Error, ska::LogLevel::Error, ska::LogSync>;
    
    auto logger2 = TestLoggerError{};
    std::stringstream ss;
    logger2.addOutputTarget(ss);
    logger2.setPattern(ska::LogLevel::Info, "%v");
    
    for(auto _ : state) {
          SKA_LOGC_STATIC(logger2, ska::LogLevel::Warn, TestLoggerError) << "test";
       }
    std::cout << ss.str().substr(0, 10);
 }

BENCHMARK(BM_LoggerErrorTest);
BENCHMARK(BM_MultiLoggerInfoTest);
BENCHMARK(BM_LogInfoTest);
BENCHMARK(BM_OutputCoutTest);
BENCHMARK_MAIN();

