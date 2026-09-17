# src/utils/Logger.h - Explanation Guide

**Purpose:** Implements the **Singleton Design Pattern** in C++. This is a critical interview topic. It proves you understand how to restrict class instantiation to a single global object, and how to make it thread-safe for multi-threaded applications.

### Complete Code & Line-by-Line Explanation

```cpp
#pragma once
#include <QString>
#include <QDebug>
#include <mutex>

// DESIGN PATTERN: Singleton
class Logger {
public:
    // 1. The Global Access Point
    // Returning a reference ensures no copies are made.
    // Static local variables are guaranteed to be thread-safe in C++11 and later.
    static Logger& getInstance() {
        static Logger instance; 
        return instance;
    }

    // 2. Rule of Three/Five Protection
    // We explicitly delete the copy constructor and assignment operator.
    // This prevents anyone from doing `Logger logger2 = Logger::getInstance();`
    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;

    // 3. The Thread-Safe Business Logic
    void log(const QString& message) {
        // std::lock_guard automatically locks the mutex when created, 
        // and safely unlocks it when it goes out of scope (RAII).
        std::lock_guard<std::mutex> lock(m_mutex); 
        qDebug() << "[ClusterLog]" << message;
    }

private:
    // 4. Private Constructor
    // The constructor is private so NO ONE can call `new Logger()` 
    // or `Logger myLogger;` from outside the class.
    Logger() {} 
    ~Logger() {}
    
    // 5. Mutex for Multithreading protection
    std::mutex m_mutex;
};
```

### Interview Talking Points for this file:
*   *"I used a Singleton for the logging system because I only ever want one log file stream to be written to at a time."*
*   *"I used `std::lock_guard` to achieve RAII-style thread safety. This prevents race conditions if multiple threads try to log at the exact same millisecond."*
*   *"I explicitly `= delete`'d the copy constructor to enforce strict Singleton rules."*
