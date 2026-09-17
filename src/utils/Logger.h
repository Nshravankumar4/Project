#pragma once
#include <QString>
#include <QDebug>
#include <mutex>

// DESIGN PATTERN: Singleton
class Logger {
public:
    static Logger& getInstance() {
        static Logger instance; // Thread-safe in C++11 and later
        return instance;
    }

    // Delete copy constructor and assignment operator to enforce Singleton
    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;

    void log(const QString& message) {
        std::lock_guard<std::mutex> lock(m_mutex); // Thread-safe logging
        qDebug() << "[ClusterLog]" << message;
    }

private:
    Logger() {} // Private constructor
    ~Logger() {}
    std::mutex m_mutex;
};

