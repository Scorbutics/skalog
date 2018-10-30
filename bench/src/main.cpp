#include <benchmark/benchmark.h>
#include <Logging/MultiLogger.h>

using TestLogger = ska::MultiLogger<ska::Logger<>, ska::Logger<>>;

constexpr auto MAX_ITERATIONS = 50000u;

static void BM_StringCreation(benchmark::State& state) {
      for (auto _ : state)
              std::string empty_string;
}
// Register the function as a benchmark
 BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
   std::string x = "hello";
   for (auto _ : state)
        std::string copy(x);
}
 
BENCHMARK(BM_StringCopy);

 static void BM_LogInfoTest(benchmark::State& state) {
     auto logger = TestLogger{};

     for(auto i = 0u; i < MAX_ITERATIONS; i++) {
          SKA_LOGC_STATIC(logger, ska::LogLevel::Info, TestLogger) << "test";
       }
 }

BENCHMARK_MAIN();

