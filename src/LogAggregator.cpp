//
// Created by Dasoju Srkihar Shashi on 02/01/26.
//

#include "LogAggregator.h"

void LogAggregator::addBatch(const std::vector<LogRecord>& batch) {
    m_allRecords.insert(
        m_allRecords.end(),
        batch.begin(),
        batch.end()
    );
}

const std::vector<LogRecord>&
LogAggregator::records() const noexcept {
    return m_allRecords;
}
