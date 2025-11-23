module;
#include <string>
#include <string_view>
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <optional>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <vector>

export module logger;

export enum class LogLevel : uint8_t
{
    Debug,
    Info,
    Warn,
    Error
};

export struct LogAllPolicy
{
    static constexpr bool enabled(LogLevel) noexcept
    { 
        return true; 
    }
};

export struct DefaultFormatPolicy
{
    static std::string format(LogLevel lvl, std::string_view msg)
    {
        std::string prefix;

        switch (lvl)
        {
            case LogLevel::Debug: prefix = "[DEBUG] "; break;
            case LogLevel::Info:  prefix = "[INFO ] "; break;
            case LogLevel::Warn:  prefix = "[WARN ] "; break;
            case LogLevel::Error: prefix = "[ERROR] "; break;
        }

        return "[" + human_time() + "] " + prefix + std::string(msg);
    }

private:
    static std::string human_time()
    {
        auto now = std::chrono::system_clock::now();
        auto time   = std::chrono::system_clock::to_time_t(now);
        std::string time_stamp = std::string(std::ctime(&time));
        time_stamp.pop_back(); // remove newline
        return time_stamp;
    }
};

export struct ConsoleSink
{
    static void write(std::string_view msg)
    {
        std::cout << msg << '\n';
    }
};

export struct FileSink
{
    inline static std::ofstream file;

    static void init(std::string_view path)
    {
        file.open(std::string(path), std::ios::app);
    }

    static void write(std::string_view msg)
    {
        if (file.is_open())
        {
            file << msg << '\n';
            file.flush();  
        }
    }
};

struct LogMessage
{
    LogLevel level;
    std::string text;
};

template<typename FormatPolicy, typename FilterPolicy, typename... Sinks>
class Logger
{
    inline static std::mutex mtx;
    inline static std::condition_variable cv;
    inline static std::queue<LogMessage> queue;
    inline static std::jthread worker;

    static void worker_thread(std::stop_token st)
    {
        while (!st.stop_requested() || !queue.empty())
        {
            std::unique_lock lock(mtx);
            cv.wait(lock, [&]{
                return !queue.empty() || st.stop_requested();
            });

            while (!queue.empty())
            {
                auto msg = std::move(queue.front());
                queue.pop();
                lock.unlock();

                auto formatted = FormatPolicy::format(msg.level, msg.text);
                (Sinks::write(formatted), ...);

                lock.lock();
            }
        }
    }

public:
    static void start()
    {
        worker = std::jthread(worker_thread);
    }

    static void stop()
    {
        cv.notify_all();
        worker.request_stop();
    }

    static void push(LogLevel lvl, std::string_view txt)
    {
        if (!FilterPolicy::enabled(lvl))
            return;

        {
            std::lock_guard lock(mtx);
            queue.push(LogMessage{lvl, std::string(txt)});
        }
        cv.notify_one();
    }

    static void debug(std::string_view msg) { push(LogLevel::Debug, msg); }
    static void info (std::string_view msg) { push(LogLevel::Info , msg); }
    static void warn (std::string_view msg) { push(LogLevel::Warn , msg); }
    static void error(std::string_view msg) { push(LogLevel::Error, msg); }
};

export using AppLogger = Logger<DefaultFormatPolicy, LogAllPolicy, ConsoleSink, FileSink>;
