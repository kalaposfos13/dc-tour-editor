#pragma once

#include <algorithm>
#include "fmt/format.h"

constexpr const char* TrimSourcePath(std::string_view source) {
    const auto rfind = [source](const std::string_view match) {
        return source.rfind(match) == source.npos ? 0 : (source.rfind(match) + match.size());
    };
    auto idx = std::max({rfind("/"), rfind("\\")});
    return source.data() + idx;
}

template <typename... Args>
void PrintLog(const char* log_level, const char* file, unsigned int line_num, const char* function,
              const char* format, const Args&... args) {
    std::string message;
    if constexpr (sizeof...(args) == 0) {
        message = format; // no formatting needed
    } else {
        message = fmt::vformat(format, fmt::make_format_args(args...));
    }

    fmt::println("[Dc.Tour] {}:{} <{}> {}: {}", file, line_num, log_level, function, message);
}

#define LOG_DEBUG(...) PrintLog("Debug", TrimSourcePath(__FILE__), __LINE__, __func__, __VA_ARGS__)
#define LOG_INFO(...) PrintLog("Info", TrimSourcePath(__FILE__), __LINE__, __func__, __VA_ARGS__)
#define LOG_WARNING(...)                                                                           \
    PrintLog("Warning", TrimSourcePath(__FILE__), __LINE__, __func__, __VA_ARGS__)
#define LOG_ERROR(...) PrintLog("Error", TrimSourcePath(__FILE__), __LINE__, __func__, __VA_ARGS__)
#define LOG_CRITICAL(...)                                                                          \
    PrintLog("Critical", TrimSourcePath(__FILE__), __LINE__, __func__, __VA_ARGS__)
