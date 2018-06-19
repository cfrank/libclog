#include <clog.h>
#include <stdlib.h>

int main(void)
{
        struct logger *log = create_logger("simple");

        LOG_ERROR(log, "An error has occured: %s", "Error Name");

        destroy_logger(log);

        return EXIT_SUCCESS;
}
