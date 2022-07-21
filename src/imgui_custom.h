#include <sys/time.h>

#ifndef __linux__
#define timegm mktime
extern "C" int gettimeofday ( struct timeval *tp ,  void *tz ) { uint64_t m = micros(); tp->tv_sec = m / 1000000, tp->tv_usec = m % 1000000; return 0; }
#endif
