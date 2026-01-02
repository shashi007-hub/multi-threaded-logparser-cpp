//
// Created by Dasoju Srkihar Shashi on 02/01/26.
//

#include "../include/writeParsedLogs.h"
#include <fstream>
#include <stdexcept>

void writeParsedLogsToFile(const std::string& outputPath,
                           const std::vector<LogRecord>& records) {
    std::ofstream out(outputPath);
    if (!out.is_open()) {
        throw std::runtime_error("Failed to open output file");
    }

    // CSV header
    out << "ip,timestamp,path,status\n";

    for (const auto& record : records) {
        out << record.ip() << ','
            << record.timestamp() << ','
            << record.path() << ','
            << record.status() << '\n';
    }
}
