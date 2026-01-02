//
// Created by Dasoju Srkihar Shashi on 02/01/26.
//

#include "LogParserThread.h"
#include <cctype>

LogParserThread::LogParserThread(SafeQueue<std::string>& queue)
    : m_queue(queue)
{
    // Reserve some space to reduce reallocations
    m_records.reserve(1024);
}

void LogParserThread::operator()() {
    std::string line;

    while (m_queue.pop(line)) {
        LogRecord record("", "", "", 0);

        if (parseLine(line, record)) {
            m_records.emplace_back(std::move(record));
        }
        // Malformed lines are ignored
    }
}

const std::vector<LogRecord>& LogParserThread::records() const noexcept {
    return m_records;
}

bool LogParserThread::parseLine(const std::string& line,
                                LogRecord& record) {
    size_t pos = 0;
    size_t len = line.size();

    // 1) Parse IP address (up to first space)
    size_t spacePos = line.find(' ', pos);
    if (spacePos == std::string::npos) return false;

    std::string ip = line.substr(pos, spacePos - pos);
    pos = spacePos + 1;

    // 2) Parse timestamp [ ... ]
    size_t openBracket = line.find('[', pos);
    size_t closeBracket = line.find(']', openBracket);
    if (openBracket == std::string::npos ||
        closeBracket == std::string::npos) {
        return false;
    }

    std::string timestamp =
        line.substr(openBracket + 1,
                    closeBracket - openBracket - 1);

    pos = closeBracket + 1;

    // 3) Parse request line "METHOD PATH HTTP/x"
    size_t firstQuote = line.find('"', pos);
    size_t secondQuote = line.find('"', firstQuote + 1);
    if (firstQuote == std::string::npos ||
        secondQuote == std::string::npos) {
        return false;
    }

    std::string request =
        line.substr(firstQuote + 1,
                    secondQuote - firstQuote - 1);

    size_t methodEnd = request.find(' ');
    if (methodEnd == std::string::npos) return false;

    size_t pathEnd = request.find(' ', methodEnd + 1);
    if (pathEnd == std::string::npos) return false;

    std::string path =
        request.substr(methodEnd + 1,
                       pathEnd - methodEnd - 1);

    pos = secondQuote + 1;

    // 4) Parse status code (3 digits)
    while (pos < len && line[pos] == ' ') {
        ++pos;
    }

    if (pos + 3 > len) return false;

    int status = 0;
    for (int i = 0; i < 3; ++i) {
        if (!std::isdigit(static_cast<unsigned char>(line[pos + i]))) {
            return false;
        }
        status = status * 10 + (line[pos + i] - '0');
    }

    record = LogRecord(
        std::move(ip),
        std::move(timestamp),
        std::move(path),
        status
    );

    return true;
}
