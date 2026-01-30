#ifndef COMMON_H
#define COMMON_H

#define _POSIX_C_SOURCE 200908L
#define _GNU_SOURCE
#define __USE_GNU

#if __STDC_HOSTED__ == 1

 /* ISO C headers. */
 #include <assert.h>
 #include <ctype.h>
 #include <errno.h>
 #include <locale.h>
 #include <signal.h>
 #include <stdarg.h>
 #include <stdint.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 /* Standard parallel execution model with memory order and atomic types. */
 #if !defined(__STDC_NO_THREADS__) && !defined(__STDC_NO_ATOMICS__)
  #include <threads.h>
  #include <stdatomic.h>
 #endif

#else
 #error "__STDC_HOSTED__ is not defined or is not equal to 1"
#endif /* __STDC_HOSTED__ */

/* Standard Unix-like headers */
#if defined(linux) || defined(__linux__) || defined(unix) || defined(__unix__)

 /* GNU C library (glibc) headers. */
 #include <fcntl.h>       /* POSIX.1‐2017 */
 #include <sys/un.h>
 #include <unistd.h>      /* POSIX.1‐2017 */
 #include <pthread.h>     /* POSIX.1‐2017 */
 #include <sys/time.h>    /* POSIX.1‐2017 */
 #include <sys/stat.h>    /* POSIX.1‐2017 */
 #include <sys/types.h>
 #include <sys/param.h>
 #include <sys/random.h>

#endif

#endif /* COMMON_H */
