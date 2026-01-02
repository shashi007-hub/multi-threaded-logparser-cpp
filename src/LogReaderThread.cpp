//
// Created by Dasoju Srkihar Shashi on 02/01/26.
//

#include "LogReaderThread.h"
#include "LogReaderThread.h"
#include <vector>
#include <stdexcept>

LogReaderThread::LogReaderThread(std::string filePath,
                                 SafeQueue<std::string>& queue,
                                 size_t bufferSize)
    : m_filePath(std::move(filePath)),
      m_queue(queue),
      m_bufferSize(bufferSize)
{
}

void LogReaderThread::operator()() {
    std::ifstream file(m_filePath, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open log file: " + m_filePath);
    }

    std::vector<char> buffer(m_bufferSize);
    std::string carryOver;

    while (file) {
        file.read(buffer.data(), buffer.size());
        std::streamsize bytesRead = file.gcount();

        if (bytesRead <= 0) {
            break;
        }

        std::string chunk(buffer.data(), static_cast<size_t>(bytesRead));
        processBuffer(chunk, carryOver);
    }

    // Push any remaining partial line as final line
    if (!carryOver.empty()) {
        m_queue.push(carryOver);
    }

    //There will only be a single reader thread
    // and when it ends it must close the queue
    m_queue.close();
}

void LogReaderThread::processBuffer(const std::string& data,
                                    std::string& carryOver) {
    size_t start = 0;

    while (true) {
        size_t newlinePos = data.find('\n', start);
        if (newlinePos == std::string::npos) {
            break;
        }

        std::string line =
            carryOver +
            data.substr(start, newlinePos - start);

        carryOver.clear();
        m_queue.push(std::move(line));

        start = newlinePos + 1;
    }

    // Remaining partial line
    carryOver += data.substr(start);
}
