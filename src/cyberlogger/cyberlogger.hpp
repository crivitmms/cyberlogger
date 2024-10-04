#ifndef __CYBERLOGGER_H__
#define __CYBERLOGGER_H__

#include "destinations/filedestination.hpp"
#include "destinations/streamdestination.hpp"
#include "logger/logger.hpp"
#include "loglevel/loglevel.hpp"

#ifndef NO_DEFAULT_SINGLETON
#include "util/singletonwrap.hpp"
#endif
#ifndef NO_DEFAULT_MACROS
#include "logs/easy_logentry.hpp"
#endif

#endif   // __CYBERLOGGER_H__