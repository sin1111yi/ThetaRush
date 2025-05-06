#pragma once

#include <stddef.h>
#include <stdint.h>

#if !defined(UNUSED_PARAM)
// Eliminate warning caused by unused variables and parameters.
#define UNUSED_PARAM(x) ((void)(x))
#endif

#if !defined(UNUSED_FUNC)
#define UNUSED_FUNC __attribute__ ((unused))
#endif

#if !defined(DISCARD)
// Discard result of x (usually an I/O register access).
#define DISCARD(x) ((void)(x))
#endif

#define BIT(x) (1 << (x))

#if __GNUC__ > 6
#define FALLTHROUGH                                                           \
  ;                                                                           \
  __attribute__ ((fallthrough))
#else
#define FALLTHROUGH                                                           \
  do                                                                          \
    {                                                                         \
    }                                                                         \
  while (0)
#endif