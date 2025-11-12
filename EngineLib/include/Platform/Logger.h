
#pragma once

#include <filesystem>
#include <stdarg.h>
#include <chrono>
#include <iomanip>
#include <mutex>

enum class LogLevel { Info, Warning, Error };

struct LogEntry {
    LogLevel level;
    std::string type;
    std::string message;
};

class Debug {
public:
    Debug() {
        try { std::filesystem::create_directory("Log"); }
        catch (const std::filesystem::filesystem_error& e)  {
            std::cerr << "Failed to create Log directory: " << e.what() << std::endl;
        }

        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm tm_data;
        localtime_s(&tm_data, &now_time);

        std::ostringstream oss;
        oss << "Log/session_" << std::put_time(&tm_data, "%Y%m%d_%H%M%S") << ".txt";

        try {
            _file.open(oss.str(), std::ios::app);
            if (!_file.is_open())
                std::cerr << "Failed to open log file: " << oss.str() << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Exception opening log file: " << e.what() << std::endl;
        }

    }

    ~Debug() {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_file.is_open()) _file.close();
    }

    void logError(const char* type, const char* format, ...) {
        va_list args;
        va_start(args, format);
        logCentral("ERROR", type, format, args);
        va_end(args);
    }

    void logInfo(const char* type, const char* format, ...) {
        va_list args;
        va_start(args, format);
        logCentral("INFO", type, format, args);
        va_end(args);
    }

    void logWarning(const char* type, const char* format, ...) {
        va_list args;
        va_start(args, format);
        logCentral("WARN", type, format, args);
        va_end(args);
    }

private:
    std::mutex _mutex;
    std::ofstream _file;

    void logCentral(const char* level, const char* type, const char* format, va_list args) {
        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer), format, args);

        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm tm_data;
        localtime_s(&tm_data, &now_time);

        std::ostringstream oss;
        oss << "[" << std::put_time(&tm_data, "%Y-%m-%d %H:%M:%S") << "] "
              << "[" << level << " / " << type << "]: "
              << buffer;


        std::string logLine = oss.str(); // construct outside lock
        {
            std::lock_guard<std::mutex> lock(_mutex);
            if (_file.is_open()) { _file << oss.str() << std::endl; }
            std::cout << oss.str() << std::endl;
        }
    }
};
