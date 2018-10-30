#include <benchmark/benchmark.h>
#include <Logging/MultiLogger.h>

using TestLogger = ska::MultiLogger<ska::Logger<>, ska::Logger<>>;

constexpr auto MAX_ITERATIONS = 50000u;

int main() {

    auto logger = TestLogger{};

    for(auto i = 0u; i < MAX_ITERATIONS; i++) {
        SKA_LOGC_STATIC(logger, ska::LogLevel::Info, TestLogger) << "test";
    }

    return 0;
}
