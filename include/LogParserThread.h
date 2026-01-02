//
// Created by Dasoju Srkihar Shashi on 02/01/26.
//

#ifndef MULTITHREADEDPARSER_LOGPARSER_H
#define MULTITHREADEDPARSER_LOGPARSER_H

#include <string>
#include <vector>
#include "SafeQueue.h"
#include "LogRecord.h"

class LogParserThread {
public:
    explicit LogParserThread(SafeQueue<std::string>& queue);

    void operator()();

    const std::vector<LogRecord>& records() const noexcept;

private:
    bool parseLine(const std::string& line, LogRecord& record);

    SafeQueue<std::string>& m_queue;
    std::vector<LogRecord> m_records;
};




#endif //MULTITHREADEDPARSER_LOGPARSER_H