#ifndef ULOG_H
#define ULOG_H

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <time.h>

#define ULOG_SUCCESS 0
#define ULOG_FAILURE -1

typedef enum
{
    ULOG_DEBUG = 0,
    ULOG_INFO,
    ULOG_WARN,
    ULOG_ERROR,
} ulog_level_t;

static ulog_level_t min_log_level = ULOG_INFO;

static inline const char* ulog_level_to_string(ulog_level_t level)
{
    switch (level)
    {
        case ULOG_DEBUG:
            return "DEBUG";
        case ULOG_INFO:
            return "INFO";
        case ULOG_WARN:
            return "WARN";
        case ULOG_ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

static inline int ulog_set_min_level(ulog_level_t level)
{
    if (level < ULOG_DEBUG || level > ULOG_ERROR)
    {
        return ULOG_FAILURE;
    };
    min_log_level = level;
    return ULOG_SUCCESS;
}

static inline void ulog_set_verbose(bool verbose)
{
    min_log_level = verbose ? ULOG_DEBUG : ULOG_INFO;
}

static inline bool ulog_enabled(ulog_level_t level)
{
    return level >= min_log_level;
}

static inline int ulog_timestamp(char* buffer, size_t size)
{
    time_t    now = time(NULL);
    struct tm tm_info;
    if (!buffer || size == 0)
        return ULOG_FAILURE;

    if (localtime_r(&now, &tm_info) == NULL)
    {
        buffer[0] = '\0';
        return ULOG_FAILURE;
    }
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", &tm_info);
    return ULOG_SUCCESS;
}

static inline int ulog_printf(ulog_level_t level, const char* fmt, ...)
{
    if (!ulog_enabled(level))
    {
        return ULOG_FAILURE;
    }

    char timestamp[32];
    ulog_timestamp(timestamp, sizeof(timestamp));

    fprintf(stderr, "[%s] %s: ", timestamp, ulog_level_to_string(level));

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fprintf(stderr, "\n");
    fflush(stderr);

    return ULOG_SUCCESS;
}

#define log_debug(fmt, ...) ulog_printf(ULOG_DEBUG, fmt, ##__VA_ARGS__);
#define log_info(fmt, ...) ulog_printf(ULOG_INFO, fmt, ##__VA_ARGS__);
#define log_warn(fmt, ...) ulog_printf(ULOG_WARN, fmt, ##__VA_ARGS__);
#define log_error(fmt, ...) ulog_printf(ULOG_ERROR, fmt, ##__VA_ARGS__);

static inline void ulog_setup(void)
{
    setvbuf(stderr, NULL, _IOLBF, 0);
}

#endif
