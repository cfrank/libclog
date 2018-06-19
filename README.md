# libclog

A Simple C logging library. Tries not to do too much.

## Example:
```c
/* You can also install as a dynamic lib if you prefer */
#include "clog.h"

struct logger *log = create_logger("MYLOGGER");

LOG_ERROR(log, "Your %s", "Message");
LOG_ERROR_SHORT(log, "Your Short %s", "Message");

destroy_logger(log);
```
> [MYLOGGER:ERROR] (myfile.c:123) - Your Message
>
> [MYLOGGER:ERROR] - Your Short Message

## Configuration
```c
/*
 * When creating a logger you can specify a name which will be
 * appended to all messages
 *
 * (defaults to: "CLOG")
 */
struct logger *create_logger(const char *name);
```
```c
/*
 * Rename the logger
 *
 * (defaults to: <whatever you named it during "create_logger">)
 */
void set_logger_name(struct logger *log, const char *name);
```
```c
/* Set the minimum logging level to output
 *
 * (defaults to: LEVEL_ERROR)
 */
void set_logging_max_level(struct logger *log, enum log_level level);
```
```c
/*
 * Set a function which will be logged when a log with level >= LEVEL_ERROR
 * occurs.
 *
 * (defaults to: NULL)
 *
 * error_func_t = void(*error_func_t)(enum log_level level)
 */
void set_logging_error_func(struct logger *log, error_func_t error_handler_func);
```
```c
/* Set the stream with which logs will be output.
 *
 * (defaults to: stderr)
 */
void set_logging_stream(struct logger *log, FILE *stream);
```
```c
/*
 * Silence the logger - No logs will be output when quiet = true
 *
 * (defaults to: false)
 */
void set_logging_quiet(struct logger *log, bool quiet);
```


## Build Requirements:

* CMake > 3.9
* C99

## Requirements:

C99 Standard Library

## Install steps (recommended):

The easiest way to use this is just to copy over the files and compile them
along side your project.

## Library install steps:

I recommend doing an "out of source build" so that CMake generated files don't
pollute the root directory. The following steps will assume that you are
following that.
```bash
mkdir build;cd build
cmake ../
make
sudo make install
```
The typical shared library files will be placed in their usual location, and can
be viewed in the generated `build/install_manifest.json` file

## Contributing:

Please set up your editor to either warn or automatically fix errors produced
by clang-format. Or if not possible, just run clang format on your changes.
Also please follow the rules specified in .editor-config.

Please, before making a pull request, make sure the following doesn't produce
any errors:
```bash
cmake -DCMAKE_BUILD_TYPE=Debug <ROOT DIR LOCATION>
make
```
