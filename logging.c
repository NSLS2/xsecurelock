#include "logging.h"

#ifdef SYSLOG
#define _GNU_SOURCE
#include <syslog.h>
#include <string.h>
#define SYSLOG_LOG_NAME     "xsecurelock"
#endif
#include <errno.h>   // for errno
#include <stdarg.h>  // for va_end, va_list, va_start
#include <stdio.h>   // for fputs, stderr, vfprintf, perror, NULL
#include <time.h>
#include <unistd.h>

#ifndef SYSLOG
static void PrintLogPrefix(void) {
  time_t t = time(NULL);
  struct tm tm_buf;
  struct tm *tm = gmtime_r(&t, &tm_buf);
  char s[32];
  if (!strftime(s, sizeof(s), "%Y-%m-%dT%H:%M:%SZ ", tm)) {
    *s = 0;
  }
  fprintf(stderr, "%s%ld xsecurelock: ", s, (long)getpid());
}
#endif

void Log(const char *format, ...) {
  va_list args;
  va_start(args, format);
#ifdef SYSLOG
  openlog(SYSLOG_LOG_NAME, LOG_PID | LOG_NDELAY | LOG_AUTHPRIV);
  vsyslog(LOG_INFO, format, args);
  closelog();
#else
  PrintLogPrefix();
  vfprintf(stderr, format, args);
  fputs(".\n", stderr);
#endif
  va_end(args);
}

void LogErrno(const char *format, ...) {
  int errno_save = errno;
  va_list args;
  va_start(args, format);
#ifdef SYSLOG
  char buffer[256];
  vsnprintf(buffer, sizeof(buffer), format, args);
  openlog(SYSLOG_LOG_NAME, LOG_PID | LOG_NDELAY | LOG_PERROR, LOG_AUTHPRIV);
  syslog(LOG_INFO, "%s: %s", buffer, strerror(errno_save));
  closelog();
#else
  PrintLogPrefix();
  vfprintf(stderr, format, args);
  fputs(": ", stderr);
  errno = errno_save;
  perror(NULL);
#endif
  va_end(args);
  errno = errno_save;
}
