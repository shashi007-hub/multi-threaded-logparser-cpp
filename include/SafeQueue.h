//
// Created by Dasoju Srkihar Shashi on 02/01/26.
//

#ifndef MULTITHREADEDPARSER_SAFEQUEUE_H
#define MULTITHREADEDPARSER_SAFEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <stdexcept>

template <typename T>
class SafeQueue {
public:
    explicit  SafeQueue(size_t capacity) :
        m_capacity(capacity), m_closed(false) {}

    void push(T item) {
        std::unique_lock<std::mutex> lock(m_mutex);

        m_notFull.wait(lock, [this] {
            return m_queue.size() < m_capacity || m_closed;
        });

        if (m_closed) {
            throw std::runtime_error("Safe queue is closed");
        }

        m_queue.push(item);

        m_notEmpty.notify_one();
    }

    bool pop(T& item) {
        std::unique_lock<std::mutex> lock(m_mutex);

        m_notEmpty.wait(lock, [this] {
            return !m_queue.empty() || m_closed;
        });

        if (m_closed && m_queue.empty()) {
            return false;
        }

        item = std::move(m_queue.front());
        m_queue.pop();

        m_notFull.notify_one();

        return true;
    }

    void close() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_closed = true;

        //wake everyone up
        m_notEmpty.notify_all();
        m_notFull.notify_all();
    }

    bool isClosed() const {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_closed;
    }

private:
    size_t m_capacity;
    bool m_closed;

    std::queue<T> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_notEmpty;
    std::condition_variable m_notFull;


};


#endif //MULTITHREADEDPARSER_SAFEQUEUE_H