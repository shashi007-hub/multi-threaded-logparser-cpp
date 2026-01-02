#include <iostream>
#include <memory>
#include "SafeQueue.h"
#include "ThreadPool.h"
#include "LogReaderThread.h"
#include "LogParserThread.h"
#include "LogAggregator.h"
#include "writeParsedLogs.h"

int main() {
    constexpr size_t QUEUE_CAPACITY = 1000000;
    constexpr size_t NUM_PARSERS = 1;

    // Step 1 --> Create Safe Queue
    SafeQueue<std::string> queue(QUEUE_CAPACITY);

    // Step 2 --> Create Thread Pool
    ThreadPool pool(NUM_PARSERS + 1);

    // ⏱ Start timing
    auto startTime = std::chrono::steady_clock::now();

    // Step 3 --> Start Parser Threads
    std::vector<std::unique_ptr<LogParserThread>> parsers;
    parsers.reserve(NUM_PARSERS);

    for (size_t i = 0; i < NUM_PARSERS; ++i) {
        parsers.emplace_back(
            std::make_unique<LogParserThread>(queue)
        );
        pool.submit(std::ref(*parsers.back()));
    }

    // Step 4 --> Start Single Reader Thread
    pool.submit(LogReaderThread(
        "/Users/shashi/CLionProjects/multithreadedparser/logfiles_1000000.log",
        queue
    ));

    // Step 5 --> Wait for all threads to finish
    pool.shutdown();

    // ⏱ End timing
    auto endTime = std::chrono::steady_clock::now();
    auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(
        endTime - startTime
    ).count();

    // Step 6 --> Aggregate all the LogRecords
    LogAggregator aggregator;
    size_t totalRecords = 0;

    for (const auto& parser : parsers) {
        totalRecords += parser->records().size();
        aggregator.addBatch(parser->records());
    }

    // Step 7 --> Write Parsed Logs to a file
    writeParsedLogsToFile(
        "parsed_logs.csv",
        aggregator.records()
    );

    // ⏱ Final output
    std::cout << "Parsed " << totalRecords << " records in "
              << durationMs << " ms \n" << "Used "<< NUM_PARSERS << " threads " " \n";

    std::cout << "Parsed records written to parsed_logs.csv\n";

    return 0;
}
