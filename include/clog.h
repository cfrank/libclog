#ifndef CLOG_H
#define CLOG_H

#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>

typedef void(*output_logger_func_t)(const char *message);
typedef void(*error_handler_func_t)(int error_status);

enum log_level {
        LEVEL_TRACE = 312157,
        LEVEL_DEBUG,
        LEVEL_INFO,
        LEVEL_WARNING,
        LEVEL_ERROR,
        LEVEL_CRITICAL
};

struct logger {
        enum log_level display_level;
        error_handler_func_t error_handler;
        pthread_mutex_t *lock;
        output_logger_func_t output_logger;
        bool quiet;
};

struct logger *create_logger(void);
void destroy_logger(struct logger *log);
void set_logging_display_level(struct logger *log, enum log_level level);
void set_error_handler_func(struct logger *log, error_handler_func_t error_handler);
void set_output_logger_func(struct logger *log, output_logger_func_t output_logger);
void set_quiet(bool quiet);
void internal_logger(struct logger *log, enum log_level level, const char *file,
        uint32_t line, const char *fmt, ...);
void internal_logger_short(struct logger *log, enum log_level level, const char* fmt, ...);

#define LOG_TRACE(log, fmt, ...) \
        internal_logger(log, LEVEL_TRACE, __FILE__, __LINE__, fmt, __VA_ARGS__);
#define LOG_TRACE_SHORT(log, fmt, ...) \
        internal_logger_short(log, LEVEL_TRACE, fmt, __VA_ARGS__);
#define LOG_DEBUG(log, fmt, ...) \
        internal_logger(log, LEVEL_DEBUG, __FILE__, __LINE__, fmt, __VA_ARGS__);
#define LOG_DEBUG_SHORT(log, fmt, ...) \
        internal_logger_short(log, LEVEL_DEBUG, fmt, __VA_ARGS__);
#define LOG_INFO(log, fmt, ...) \
        internal_logger(log, LEVEL_INFO, __FILE__, __LINE__, fmt, __VA_ARGS__);
#define LOG_INFO_SHORT(log, fmt, ...) \
        internal_logger(log, LEVEL_INFO, fmt, __VA_ARGS__);
#define LOG_WARNING(log, fmt, ...) \
        internal_logger(log, LEVEL_WARNING, __FILE__, __LINE__, fmt, __VA_ARGS__);
#define LOG_WARNING_SHORT(log, fmt, ...) \
        internal_logger_short(log, LEVEL_WARNING, fmt, __VA_ARGS__);
#define LOG_ERROR(log, fmt, ...) \
        internal_logger(log, LEVEL_ERROR, __FILE__, __LINE__, fmt, __VA_ARGS__);
#define LOG_ERROR_SHORT(log, fmt, ...) \
        internal_logger_short(log, LEVEL_ERROR, fmt, __VA_ARGS__);
#define LOG_CRITICAL(log, fmt, ...) \
        internal_logger(log, LOG_CRITICAL, __FILE__, __LINE__, fmt, __VA_ARGS__);
#define LOG_CRITICAL_SHORT(log, fmt, ...) \
        internal_logger_short(log, LEVEL_CRITICAL, fmt, __VA_ARGS__);

#endif /* CLOG_H */
