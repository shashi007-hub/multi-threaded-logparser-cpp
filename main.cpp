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
    constexpr size_t NUM_PARSERS = 8;

    //Step 1 --> Create Safe Queue
    SafeQueue<std::string> queue(QUEUE_CAPACITY);

    //Step 2 --> Create Thread Pool
    ThreadPool pool(NUM_PARSERS + 1);

    //Step 3 --> Start Parser Threads
    std::vector<std::unique_ptr<LogParserThread>> parsers;
    parsers.reserve(NUM_PARSERS);

    for (size_t i = 0; i < NUM_PARSERS; ++i) {
        parsers.emplace_back(
            std::make_unique<LogParserThread>(queue)
        );
        pool.submit(std::ref(*parsers.back()));
    }

    //Step 4 --> Start Single Reade Thread
    pool.submit(LogReaderThread("/Users/shashi/CLionProjects/multithreadedparser/logfiles.log", queue));

    std::cout << "Before shutdown\n";
    //Step 5  --> Wait for readers to finish --> Join all threads to main thread and wait for exit
    pool.shutdown();
    std::cout << "After shutdown\n";


    //Step 6 --> Aggregate all the LogRecords from all shared pointers
    LogAggregator aggregator;
    for (const auto& parser : parsers) {
        aggregator.addBatch(parser->records());
    }

    //Step 7 --> Write Parsed Logs to a file
    writeParsedLogsToFile(
        "parsed_logs.csv",
        aggregator.records()
    );

    std::cout << "Parsed records written to parsed_logs.csv\n";


    return 0;
}
