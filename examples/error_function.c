#include <clog.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool error_occured = false;

void handle_error(enum log_level level)
{
        error_occured = true;
}

int main(void)
{
        struct logger *log = create_logger("error_function");

        set_logging_min_level(log, LEVEL_INFO);
        set_logging_error_func(log, handle_error);

        LOG_CRITICAL(log, "There has been a critical error!");

        if (error_occured) {
                LOG_INFO_SHORT(log,
                               "The error handler function has been called");
        }

        destroy_logger(log);

        return EXIT_SUCCESS;
}
