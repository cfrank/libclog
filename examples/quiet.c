#include <clog.h>
#include <stdlib.h>

int main(void)
{
        struct logger *log = create_logger("quiet");

        set_logging_quiet(log, true);

        LOG_ERROR(log, "Because our log is set to quiet I will not be shown");

        set_logging_quiet(log, false);

        LOG_ERROR(log, "Now that we have set quiet to false you will see me");

        destroy_logger(log);

        return EXIT_SUCCESS;
}
