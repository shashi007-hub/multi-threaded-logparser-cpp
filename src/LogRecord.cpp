//
// Created by Dasoju Srkihar Shashi on 02/01/26.
//

#include "LogRecord.h"

#include "LogRecord.h"

LogRecord::LogRecord(std::string ip,
                     std::string timestamp,
                     std::string path,
                     int status)
    : m_ip(std::move(ip)),
      m_timestamp(std::move(timestamp)),
      m_path(std::move(path)),
      m_status(status)
{
}

const std::string& LogRecord::ip() const noexcept {
    return m_ip;
}

const std::string& LogRecord::timestamp() const noexcept {
    return m_timestamp;
}

const std::string& LogRecord::path() const noexcept {
    return m_path;
}

int LogRecord::status() const noexcept {
    return m_status;
}
