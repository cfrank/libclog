#include <clog.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
        struct logger *log = create_logger("file");

        FILE *f = fopen("log.txt", "w");

        if (f == NULL) {
                LOG_ERROR(log, "Could not open log.txt for writing");
        }

        set_logging_stream(log, f);

        LOG_ERROR(log, "Logging to file %s", "log.txt");
        LOG_CRITICAL(log, "This was a critical error");

        destroy_logger(log);

        return EXIT_SUCCESS;
}
