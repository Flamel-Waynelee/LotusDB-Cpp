#ifndef PCH_H
#define PCH_H

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#define STDERR(format, ...) fprintf(stderr, format, ##__VA_ARGS__ ); putchar('\n');
#define STDERR_FUNC_LINE() STDERR("func: %s, line: %d", __func__, __LINE__);

#endif
