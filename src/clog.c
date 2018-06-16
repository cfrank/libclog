#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "clog.h"

struct logger *create_logger(void)
{
        struct logger *logger = malloc(sizeof(struct logger));

        if (logger == NULL) {
                // TODO: Handle error
                return NULL;
        }

        /* Add some sensible defaults */
        logger->max_level = LEVEL_ERROR;
        logger->error_handler_func = NULL;

        pthread_mutex_t *lock = NULL;
        pthread_mutex_init(lock, NULL);

        logger->lock = lock;
        logger->output_logger_func = NULL;
        logger->quiet = false;

        return logger;
}

void destroy_logger(struct logger *log)
{
        pthread_mutex_destroy(log->lock);

        free(log);
}

void set_logging_max_level(struct logger *log, enum log_level level)
{
        log->max_level = level;
}

void set_error_func(struct logger *log, error_func_t error_handler_func)
{
        log->error_handler_func = error_handler_func;
}

void set_output_func(struct logger *log, output_func_t output_logger_func)
{
        log->output_logger_func = output_logger_func;
}

void set_quiet(struct logger *log, bool quiet)
{
        log->quiet = quiet;
}

void internal_logger(const struct logger *log, enum log_level level,
                     const char *file, uint32_t line, const char *fmt, ...)
{
        if (level < log->max_level) {
                return;
        }

        fprintf(stderr, "%s:%d", file, line);

        va_list args;
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
        fprintf(stderr, "\n");
}

void internal_logger_short(const struct logger *log, enum log_level level,
                           const char *fmt, ...)
{
        if (level < log->max_level) {
                return;
        }

        va_list args;
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
        fprintf(stderr, "\n");
}
