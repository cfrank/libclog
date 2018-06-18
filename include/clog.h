/*
 * Copyright (c) 2018 Chris Frank <chris@cfrank.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CLOG_H
#define CLOG_H

#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef void (*error_func_t)(int error_status);

enum log_level {
        LEVEL_TRACE = 312157,
        LEVEL_DEBUG,
        LEVEL_INFO,
        LEVEL_WARNING,
        LEVEL_ERROR,
        LEVEL_CRITICAL
};

static const char *log_level_to_string(enum log_level level);
enum log_level string_to_log_level(const char *level_string);

struct logger {
        const char *name;
        enum log_level max_level;
        error_func_t error_handler_func;
        pthread_mutex_t *lock;
        FILE *stream;
        bool quiet;
};

struct logger *create_logger(const char *name);
void destroy_logger(struct logger *log);
const char *generate_logging_name(const char *name);
void set_logging_max_level(struct logger *log, enum log_level level);
void set_logging_error_func(struct logger *log,
                            error_func_t error_handler_func);
void set_logging_stream(struct logger *log, FILE *stream);
void set_logging_quiet(struct logger *log, bool quiet);
void internal_logger(const struct logger *log, enum log_level level,
                     const char *file, uint32_t line, const char *fmt, ...);
void internal_logger_short(const struct logger *log, enum log_level level,
                           const char *fmt, ...);

#define LOG_TRACE(log, fmt, ...)                                               \
        internal_logger(log, LEVEL_TRACE, __FILE__, __LINE__, fmt, __VA_ARGS__);
#define LOG_TRACE_SHORT(log, fmt, ...)                                         \
        internal_logger_short(log, LEVEL_TRACE, fmt, __VA_ARGS__);
#define LOG_DEBUG(log, fmt, ...)                                               \
        internal_logger(log, LEVEL_DEBUG, __FILE__, __LINE__, fmt, __VA_ARGS__);
#define LOG_DEBUG_SHORT(log, fmt, ...)                                         \
        internal_logger_short(log, LEVEL_DEBUG, fmt, __VA_ARGS__);
#define LOG_INFO(log, fmt, ...)                                                \
        internal_logger(log, LEVEL_INFO, __FILE__, __LINE__, fmt, __VA_ARGS__);
#define LOG_INFO_SHORT(log, fmt, ...)                                          \
        internal_logger(log, LEVEL_INFO, fmt, __VA_ARGS__);
#define LOG_WARNING(log, fmt, ...)                                             \
        internal_logger(                                                       \
                log, LEVEL_WARNING, __FILE__, __LINE__, fmt, __VA_ARGS__);
#define LOG_WARNING_SHORT(log, fmt, ...)                                       \
        internal_logger_short(log, LEVEL_WARNING, fmt, __VA_ARGS__);
#define LOG_ERROR(log, fmt, ...)                                               \
        internal_logger(log, LEVEL_ERROR, __FILE__, __LINE__, fmt, __VA_ARGS__);
#define LOG_ERROR_SHORT(log, fmt, ...)                                         \
        internal_logger_short(log, LEVEL_ERROR, fmt, __VA_ARGS__);
#define LOG_CRITICAL(log, fmt, ...)                                            \
        internal_logger(                                                       \
                log, LOG_CRITICAL, __FILE__, __LINE__, fmt, __VA_ARGS__);
#define LOG_CRITICAL_SHORT(log, fmt, ...)                                      \
        internal_logger_short(log, LEVEL_CRITICAL, fmt, __VA_ARGS__);

#endif /* CLOG_H */
