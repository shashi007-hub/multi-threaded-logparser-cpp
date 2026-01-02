//
// Created by Dasoju Srkihar Shashi on 02/01/26.
//

#ifndef MULTITHREADEDPARSER_THREADPOOL_H
#define MULTITHREADEDPARSER_THREADPOOL_H
#include <functional>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    explicit ThreadPool(int numThreads);
    virtual ~ThreadPool();
    void submit(std::function<void()> task);
    void shutdown();


private:
    void workerLoop();

    std::vector<std::thread> m_workers;
    std::queue<std::function<void()>> m_tasks;

    std::mutex m_mutex;
    std::condition_variable m_cv;

    bool m_stop;

};


#endif //MULTITHREADEDPARSER_THREADPOOL_H