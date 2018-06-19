#include <clog.h>

int main(void)
{
        struct logger *log = create_logger("MYLOGGER");

        LOG_ERROR(log, "An error has occured: %s", "Error Name");
        LOG_ERROR_SHORT(log, "A short error has occured: %s", log->name);

        LOG_ERROR(log, "An error has occured - literally");

        LOG_ERROR(log, "Your %s", "Message");

        destroy_logger(log);
}
