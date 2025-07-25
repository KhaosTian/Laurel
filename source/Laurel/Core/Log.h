#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Laurel {
class Log {
  public:
    inline static void init(size_t level = spdlog::level::trace, const std::optional<std::string>& log_file = std::nullopt) {
        std::vector<spdlog::sink_ptr> sinks;

        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern("%^[%Y-%m-%d %T%e] [%n] [%l] [%s:%#] %v%$");
        sinks.push_back(console_sink);

        if (log_file) {
            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_file.value(), true);
            file_sink->set_pattern("[%Y-%m-%d %T%e] [%n] [%l] [%s:%#] %v");
            sinks.push_back(file_sink);
        }

        s_core_logger = std::make_shared<spdlog::logger>("CORE", begin(sinks), end(sinks));
        spdlog::register_logger(s_core_logger);
        s_core_logger->set_level(static_cast<spdlog::level::level_enum>(level));
        s_core_logger->flush_on(spdlog::level::trace);

        s_client_logger = std::make_shared<spdlog::logger>("CLIENT", begin(sinks), end(sinks));
        spdlog::register_logger(s_client_logger);
        s_client_logger->set_level(static_cast<spdlog::level::level_enum>(level));
        s_client_logger->flush_on(spdlog::level::trace);
    }

    inline static void shutdown() { spdlog::shutdown(); }

    inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_core_logger; }
    inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_client_logger; }

  private:
    inline static std::shared_ptr<spdlog::logger> s_core_logger;
    inline static std::shared_ptr<spdlog::logger> s_client_logger;
};

} // namespace Laurel

#define LR_CORE_TRACE(...) SPDLOG_LOGGER_TRACE(::Laurel::Log::getCoreLogger(), __VA_ARGS__)
#define LR_CORE_INFO(...) SPDLOG_LOGGER_INFO(::Laurel::Log::getCoreLogger(), __VA_ARGS__)
#define LR_CORE_WARN(...) SPDLOG_LOGGER_WARN(::Laurel::Log::getCoreLogger(), __VA_ARGS__)
#define LR_CORE_ERROR(...) SPDLOG_LOGGER_ERROR(::Laurel::Log::getCoreLogger(), __VA_ARGS__)
#define LR_CORE_FATAL(...) SPDLOG_LOGGER_CRITICAL(::Laurel::Log::getCoreLogger(), __VA_ARGS__)

#define LR_TRACE(...) SPDLOG_LOGGER_TRACE(::Laurel::Log::getClientLogger(), __VA_ARGS__)
#define LR_INFO(...) SPDLOG_LOGGER_INFO(::Laurel::Log::getClientLogger(), __VA_ARGS__)
#define LR_WARN(...) SPDLOG_LOGGER_WARN(::Laurel::Log::getClientLogger(), __VA_ARGS__)
#define LR_ERROR(...) SPDLOG_LOGGER_ERROR(::Laurel::Log::getClientLogger(), __VA_ARGS__)
#define LR_FATAL(...) SPDLOG_LOGGER_CRITICAL(::Laurel::Log::getClientLogger(), __VA_ARGS__)
