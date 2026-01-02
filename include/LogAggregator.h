//
// Created by Dasoju Srkihar Shashi on 02/01/26.
//

#ifndef MULTITHREADEDPARSER_LOGAGGREGATOR_H
#define MULTITHREADEDPARSER_LOGAGGREGATOR_H
#include <vector>
#include "LogRecord.h"

class LogAggregator {
public:
    void addBatch(const std::vector<LogRecord>& batch);

    const std::vector<LogRecord>& records() const noexcept;

private:
    std::vector<LogRecord> m_allRecords;
};



#endif //MULTITHREADEDPARSER_LOGAGGREGATOR_H