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

enum log_level {
        LEVEL_TRACE = 312157,
        LEVEL_DEBUG,
        LEVEL_INFO,
        LEVEL_WARNING,
        LEVEL_ERROR,
        LEVEL_CRITICAL
};
typedef void (*error_func_t)(enum log_level level);

struct logger {
        error_func_t error_handler_func;
        enum log_level min_level;
        const char *name;
        FILE *stream;
        bool quiet;
};

/* Logging creation/destruction functions */
struct logger *create_logger(const char *name);
void destroy_logger(struct logger *log);

/* Public setters */
void set_logging_name(struct logger *log, const char *name);
void set_logging_min_level(struct logger *log, enum log_level level);
void set_logging_error_func(struct logger *log,
                            error_func_t error_handler_func);
void set_logging_stream(struct logger *log, FILE *stream);
void set_logging_quiet(struct logger *log, bool quiet);

/* Internal functions */
void internal_logger(const struct logger *log, enum log_level level,
                     const char *fmt, ...);
void internal_logger_long(const struct logger *log, enum log_level level,
                          const char *file, size_t line, const char *fmt, ...);

#define LOG_TRACE(log, ...) internal_logger(log, LEVEL_TRACE, __VA_ARGS__);
#define LOG_TRACE_LONG(log, ...)                                               \
        internal_logger_long(log, LEVEL_TRACE, __FILE__, __LINE__, __VA_ARGS__);
#define LOG_DEBUG(log, ...) internal_logger(log, LEVEL_DEBUG, fmt, __VA_ARGS__);
#define LOG_DEBUG_LONG(log, ...)                                               \
        internal_logger_long(log, LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__);
#define LOG_INFO(log, ...) internal_logger(log, LEVEL_INFO, __VA_ARGS__);
#define LOG_INFO_LONG(log, ...)                                                \
        internal_logger_long(log, LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__);
#define LOG_WARNING(log, ...) internal_logger(log, LEVEL_WARNING, __VA_ARGS__);
#define LOG_WARNING_LONG(log, ...)                                             \
        internal_logger_long(                                                  \
                log, LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__);
#define LOG_ERROR(log, ...) internal_logger(log, LEVEL_ERROR, __VA_ARGS__);
#define LOG_ERROR_LONG(log, ...)                                               \
        internal_logger_long(log, LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__);
#define LOG_CRITICAL(log, ...)                                                 \
        internal_logger(log, LEVEL_CRITICAL, __VA_ARGS__);
#define LOG_CRITICAL_LONG(log, ...)                                            \
        internal_logger_long(                                                  \
                log, LEVEL_CRITICAL, __FILE__, __LINE__, __VA_ARGS__);

#endif /* CLOG_H */
