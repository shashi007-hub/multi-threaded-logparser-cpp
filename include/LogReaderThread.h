//
// Created by Dasoju Srkihar Shashi on 02/01/26.
//

#ifndef MULTITHREADEDPARSER_LOGREADERTHREAD_H
#define MULTITHREADEDPARSER_LOGREADERTHREAD_H
#include <string>
#include <fstream>
#include "SafeQueue.h"



class LogReaderThread {
public:
    LogReaderThread(std::string filePath,
                    SafeQueue<std::string>& queue,
                    size_t bufferSize = 64* 1024);

    void operator()();

private:
    void processBuffer(const std::string& data,std::string& carryOver);
    std::string m_filePath;
    SafeQueue<std::string>& m_queue;
    size_t m_bufferSize;
};


#endif //MULTITHREADEDPARSER_LOGREADERTHREAD_H