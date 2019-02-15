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

#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "clog.h"

#if defined __clang__ || defined __GNUC__
#define ATTR_PRINTF(idx) __attribute__((format(printf, idx, 0)))
#else
#define ATTR_PRINTF(idx)
#endif

struct logger *create_logger(const char *name)
{
        struct logger *logger = malloc(sizeof(struct logger));

        if (logger == NULL) {
                fputs("Could not allocate bytes for logger", stderr);
                return NULL;
        }

        logger->name = name;

        /* Add some sensible defaults */
        logger->min_level = LEVEL_ERROR;
        logger->error_handler_func = NULL;
        logger->stream = stderr;
        logger->quiet = false;

        return logger;
}

void destroy_logger(struct logger *log)
{
        free(log);
}

void set_logging_name(struct logger *log, const char *name)
{
        log->name = name;
}

void set_logging_min_level(struct logger *log, enum log_level level)
{
        log->min_level = level;
}

void set_logging_error_func(struct logger *log, error_func_t error_handler_func)
{
        log->error_handler_func = error_handler_func;
}

void set_logging_stream(struct logger *log, FILE *stream)
{
        log->stream = stream;
}

void set_logging_quiet(struct logger *log, bool quiet)
{
        log->quiet = quiet;
}

static const char *log_level_to_string(enum log_level level)
{
        switch (level) {
        case LEVEL_TRACE:
                return "TRACE";
        case LEVEL_DEBUG:
                return "DEBUG";
        case LEVEL_INFO:
                return "INFO";
        case LEVEL_WARNING:
                return "WARNING";
        case LEVEL_ERROR:
                return "ERROR";
        case LEVEL_CRITICAL:
                return "CRITICAL";
        default:
                return "";
        }
}

static const char *generate_logging_name(const char *name)
{
        if (name == NULL) {
                return "CLOG";
        }

        return name;
}

ATTR_PRINTF(5)
void internal_logger(const struct logger *log, enum log_level level,
                     const char *file, size_t line, const char *fmt, ...)
{
        if (level < log->min_level || log->quiet) {
                return;
        }

        fprintf(log->stream,
                "[%s:%s] (%s:%zu) - ",
                generate_logging_name(log->name),
                log_level_to_string(level),
                file,
                line);

        va_list args;
        va_start(args, fmt);
        vfprintf(log->stream, fmt, args);
        va_end(args);

        fputs("\n", log->stream);

        if (level >= LEVEL_ERROR && log->error_handler_func != NULL) {
                log->error_handler_func(level);
        }
}

ATTR_PRINTF(3)
void internal_logger_short(const struct logger *log, enum log_level level,
                           const char *fmt, ...)
{
        if (level < log->min_level || log->quiet) {
                return;
        }

        fprintf(log->stream,
                "[%s:%s] - ",
                generate_logging_name(log->name),
                log_level_to_string(level));

        va_list args;
        va_start(args, fmt);
        vfprintf(log->stream, fmt, args);
        va_end(args);

        fputs("\n", log->stream);

        if (level >= LEVEL_ERROR && log->error_handler_func != NULL) {
                log->error_handler_func(level);
        }
}
