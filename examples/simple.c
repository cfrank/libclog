#include <clog.h>
#include <stdio.h>

int main(void)
{
        struct logger *log = create_logger();

        LOG_ERROR(log, "An error has occured: %s", "Error Name");

        destroy_logger(log);
}
