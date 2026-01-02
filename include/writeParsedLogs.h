//
// Created by Dasoju Srkihar Shashi on 02/01/26.
//

#ifndef MULTITHREADEDPARSER_WRITEPARSEDLOGS_H
#define MULTITHREADEDPARSER_WRITEPARSEDLOGS_H

#include <string>
#include <vector>
#include "LogRecord.h"

void writeParsedLogsToFile(const std::string& outputPath,
                           const std::vector<LogRecord>& records);




#endif //MULTITHREADEDPARSER_WRITEPARSEDLOGS_H