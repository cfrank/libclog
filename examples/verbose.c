#include <clog.h>
#include <stdlib.h>

int main(void)
{
        struct logger *log = create_logger("verbose");

        set_logging_min_level(log, LEVEL_TRACE);

        LOG_TRACE(log, "By default this message would %s be shown", "not");

        set_logging_min_level(log, LEVEL_ERROR);

        /*
         * Because we set the max logging level to LEVEL_ERROR above
         * this will not print anything
         */
        LOG_TRACE(log, "This message is below the minimum logging level");

        destroy_logger(log);

        return EXIT_SUCCESS;
}
