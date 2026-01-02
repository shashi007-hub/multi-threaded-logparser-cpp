//
// Created by Dasoju Srkihar Shashi on 02/01/26.
//

#ifndef MULTITHREADEDPARSER_LOGRECORD_H
#define MULTITHREADEDPARSER_LOGRECORD_H
#include <string>

class LogRecord {
public:
    LogRecord(std::string ip,
              std::string timestamp,
              std::string path,
              int status);

    const std::string& ip() const noexcept;
    const std::string& timestamp() const noexcept;
    const std::string& path() const noexcept;
    int status() const noexcept;

private:
    std::string m_ip;
    std::string m_timestamp;
    std::string m_path;
    int m_status;
};


#endif //MULTITHREADEDPARSER_LOGRECORD_H