//
// Created by Ignacio Rossi on 4/1/18.
//

#ifndef CLIONTEST_LOGGING_H
#define CLIONTEST_LOGGING_H

#include <iostream>
#include <sstream>

#ifdef DISABLE_BACKTRACES
#define DUMP_BACKTRACE()
#else
#define DUMP_BACKTRACE() logging::dumpBacktrace()
#endif

#define WRAP_LOG(lf, l, m)                                                                         \
  {                                                                                                \
    std::ostringstream o;                                                                          \
    o << #lf << ": " << m;                                                                         \
    printf("%s\n", o.str().c_str());                                                               \
  }
#ifdef NDEBUG
#define LOG_TRACE(l, m)
#define LOG_DEBUG(l, m)
#else
#define LOG_TRACE(l, m) WRAP_LOG(LOG4CXX_TRACE, l, m)
#define LOG_DEBUG(l, m) WRAP_LOG(LOG4CXX_DEBUG, l, m)
#endif
#define LOG_INFO(l, m) WRAP_LOG(LOG4CXX_INFO, l, m)
#define LOG_WARN(l, m) WRAP_LOG(LOG4CXX_WARN, l, m)
#define LOG_ERROR(l, m) WRAP_LOG(LOG4CXX_ERROR, l, m)
#define LOG_FATAL(l, m) WRAP_LOG(LOG4CXX_FATAL, l, m)
#define LOG_THROW(l, m)                                                                            \
  {                                                                                                \
    LOG_FATAL(l, m);                                                                               \
    DUMP_BACKTRACE();                                                                              \
    std::ostringstream o;                                                                          \
    o << "Oops@" << __FILE__ << ":" << __LINE__ << ". " << m;                                      \
    throw std::runtime_error{o.str()};                                                             \
  }

#define LOG_ASSERT(l, c, m)                                                                        \
  if (!(c)) {                                                                                      \
    LOG_THROW(l, m);                                                                               \
  }

namespace logging {
void terminateWithSignal(int signal);

void terminate();

void dumpBacktrace();
} // namespace logging

#endif // CLIONTEST_LOGGING_H
