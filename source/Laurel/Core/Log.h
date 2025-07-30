#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Laurel {
class Log {
  public:
    inline static void Init(size_t level = spdlog::level::trace, const std::optional<std::string>& logFile = std::nullopt) {
        std::vector<spdlog::sink_ptr> sinks;

        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_pattern("%^[%Y-%m-%d %T%e] %v%$");
        sinks.push_back(consoleSink);

        if (logFile) {
            auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFile.value(), true);
            fileSink->set_pattern("[%Y-%m-%d %T%e] %v");
            sinks.push_back(fileSink);
        }
 
        s_coreLogger = std::make_shared<spdlog::logger>("CORE", begin(sinks), end(sinks));
        spdlog::register_logger(s_coreLogger);
        s_coreLogger->set_level(static_cast<spdlog::level::level_enum>(level));
        s_coreLogger->flush_on(spdlog::level::trace);

        s_clientLogger = std::make_shared<spdlog::logger>("CLIENT", begin(sinks), end(sinks));
        spdlog::register_logger(s_clientLogger);
        s_clientLogger->set_level(static_cast<spdlog::level::level_enum>(level));
        s_clientLogger->flush_on(spdlog::level::trace);
    }

    inline static void Shutdown() { spdlog::shutdown(); }

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; }

  private:
    inline static std::shared_ptr<spdlog::logger> s_coreLogger;
    inline static std::shared_ptr<spdlog::logger> s_clientLogger;
};

} // namespace Laurel

#define LR_CORE_TRACE(...) SPDLOG_LOGGER_TRACE(::Laurel::Log::GetCoreLogger(), __VA_ARGS__)
#define LR_CORE_INFO(...) SPDLOG_LOGGER_INFO(::Laurel::Log::GetCoreLogger(), __VA_ARGS__)
#define LR_CORE_WARN(...) SPDLOG_LOGGER_WARN(::Laurel::Log::GetCoreLogger(), __VA_ARGS__)
#define LR_CORE_ERROR(...) SPDLOG_LOGGER_ERROR(::Laurel::Log::GetCoreLogger(), __VA_ARGS__)
#define LR_CORE_FATAL(...) SPDLOG_LOGGER_CRITICAL(::Laurel::Log::GetCoreLogger(), __VA_ARGS__)

#define LR_TRACE(...) SPDLOG_LOGGER_TRACE(::Laurel::Log::GetClientLogger(), __VA_ARGS__)
#define LR_INFO(...) SPDLOG_LOGGER_INFO(::Laurel::Log::GetClientLogger(), __VA_ARGS__)
#define LR_WARN(...) SPDLOG_LOGGER_WARN(::Laurel::Log::GetClientLogger(), __VA_ARGS__)
#define LR_ERROR(...) SPDLOG_LOGGER_ERROR(::Laurel::Log::GetClientLogger(), __VA_ARGS__)
#define LR_FATAL(...) SPDLOG_LOGGER_CRITICAL(::Laurel::Log::GetClientLogger(), __VA_ARGS__)
