#pragma once

#include <math.h>
#include <stddef.h>
#include <stdint.h>

#define DUMMY                                                                 \
  do                                                                          \
    {                                                                         \
    }                                                                         \
  while (0)

#define NOP DUMMY

#define ARRAYLEN(x) (sizeof (x) / sizeof (x)[0])
#define ARRAYEND(x) (&(x)[ARRAYLEN (x)])

#define FORCED_TYPE_CONV(type, var) ((type)(var))

#define __TOSTRING(x) #x
#define TOSTRING(x) __TOSTRING (x)

#define __CONTACT(x, y) x##y
#define CONTACT(x, y) __CONTACT (x, y)
#define CONTACT2(_1, _2) CONTACT (_1, _2)
#define CONTACT3(_1, _2, _3) CONTACT (CONTACT (_1, _2), _3)
#define CONTACT4(_1, _2, _3, _4) CONTACT (CONTACT3 (_1, _2, _3), _4)

#if !defined(UNUSED)
#define UNUSED(x) ((void)(x))
#endif /* UNUSE */

#if !defined(MAYBE_UNUSE)
#define MAYBE_UNUSE(x) UNUSED (x)
#endif /* MAYBE_UNUSED */

#if !defined(DEFAULT_NONE_INTERFACE)
#define DEFAULT_NONE_INTERFACE NULL
#endif /* DISCARD_INTERFACE */

#if !defined(UNUSED_FUNC)
#define UNUSED_FUNC __attribute__ ((unused))
#endif

#define BIT(x) (1 << (x))

#define COMPVAL(x, y) ((x) - (y))

#define FLOATEQU(f, v)                                                        \
  (((double)(f) - (double)(v)) < 1e-15                                        \
           && ((double)(f) - (double)(v)) > -1e-15                            \
       ? 1                                                                    \
       : 0)
#define FLOATNBR(f, v)                                                        \
  (((double)(f) - (double)(v)) < 1e-10                                        \
           && ((double)(f) - (double)(v)) > -1e-10                            \
       ? 1                                                                    \
       : 0)

#define SWAPI(x, y)                                                           \
  do                                                                          \
    {                                                                         \
      x = x + y;                                                              \
      y = x - y;                                                              \
      x = x - y;                                                              \
    }                                                                         \
  while (0)

#define SWAPF SWAPI

static inline int16_t
compUI16 (uint16_t a, uint16_t b)
{
  return (int16_t)(a - b);
}

static inline int32_t
compUI32 (uint32_t a, uint32_t b)
{
  return (int32_t)(a - b);
}

static inline int32_t
swapI32 (int32_t x)
{
  return ((((uint32_t)x & 0x000000ffU) << 24)
          | (((uint32_t)x & 0x0000ff00U) << 8)
          | (((uint32_t)x & 0x00ff0000U) >> 8)
          | (((uint32_t)x & 0xff000000U) >> 24));
}

static inline int16_t
swapI16 (int16_t x)
{
  return ((((uint16_t)x & 0x00ffU) << 8) | (((uint16_t)x & 0xff00U) >> 8));
}

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
