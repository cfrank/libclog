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
