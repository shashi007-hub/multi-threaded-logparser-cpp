//
// Created by Dasoju Srkihar Shashi on 02/01/26.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(int numThreads) {
    m_stop = false;
    for (int i = 0; i < numThreads; i++) {
        m_workers.emplace_back(&ThreadPool::workerLoop,this);
    }
}

ThreadPool::~ThreadPool() {
    shutdown();
}

void ThreadPool::submit(std::function<void()> task) {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_stop) {
        throw std::runtime_error("Called Submit on Stopped ThreaPool");
    }

    m_tasks.push(std::move(task));

    m_cv.notify_one();
}

void ThreadPool::shutdown() {
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_stop = true;
    }

    m_cv.notify_all();

    for (std::thread& worker : m_workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }

    m_workers.clear();
}

void ThreadPool::workerLoop() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(m_mutex);

            m_cv.wait(lock,[&] {
                return m_stop || !m_tasks.empty();
            });

            if (m_stop && m_tasks.empty()) {
                return;
                ///graceful exit
            }

            task = std::move(m_tasks.front());
            m_tasks.pop();
        }
        task();
    }
}



