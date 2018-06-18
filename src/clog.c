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
        logger->lock = malloc(sizeof(pthread_mutex_t));

        pthread_mutex_init(logger->lock, NULL);

        logger->stream = stderr;
        logger->quiet = false;

        return logger;
}

void destroy_logger(struct logger *log)
{
        pthread_mutex_destroy(log->lock);

        free(log->lock);

        free(log);
}

void set_logging_max_level(struct logger *log, enum log_level level)
{
        log->max_level = level;
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

void internal_logger(const struct logger *log, enum log_level level,
                     const char *file, uint32_t line, const char *fmt, ...)
{
        if (level < log->max_level) {
                return;
        }

        pthread_mutex_lock(log->lock);
        fprintf(log->stream, "%s:%d ", file, line);

        va_list args;
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
        fprintf(stderr, "\n");
        pthread_mutex_unlock(log->lock);
}

void internal_logger_short(const struct logger *log, enum log_level level,
                           const char *fmt, ...)
{
        if (level < log->max_level) {
                return;
        }

        pthread_mutex_lock(log->lock);
        va_list args;
        va_start(args, fmt);
        vfprintf(log->stream, fmt, args);
        va_end(args);
        fprintf(stderr, "\n");
        pthread_mutex_unlock(log->lock);
}
