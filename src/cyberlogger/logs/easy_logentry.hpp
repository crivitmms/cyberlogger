#pragma once

#define CL_COUT_DESTINATION std::make_unique<StreamDestination>("cout", std::shared_ptr<std::ostream>(&std::cout, [](std::ostream *) {}))
#define CL_DEFAULT_LOGLEVEL_CONF cyberlogger::Loglevel::getID(),{ \
cyberlogger::Loglevel::UNKNOWN , \
cyberlogger::Loglevel::TRACE   , \
cyberlogger::Loglevel::DEBUG   , \
cyberlogger::Loglevel::INFO    , \
cyberlogger::Loglevel::WARNING , \
cyberlogger::Loglevel::ERROR   , \
cyberlogger::Loglevel::CRITICAL }

#define CL_MAKELOGENTRY(LoglevelClass, msg, loglevel) LogEntry(msg, LoglevelClass(loglevel), __FILE__, __LINE__)

#define CL_LOGENTRYDEFAULT(msg, loglevel) CL_MAKELOGENTRY(Loglevel, msg, loglevel)

#define LOG_MSG_UNKNOWN(msg)  CL_LOGENTRYDEFAULT(msg, cyberlogger::Loglevel::UNKNOWN)
#define LOG_MSG_TRACE(msg)    CL_LOGENTRYDEFAULT(msg, cyberlogger::Loglevel::TRACE)
#define LOG_MSG_DEBUG(msg)    CL_LOGENTRYDEFAULT(msg, cyberlogger::Loglevel::DEBUG)
#define LOG_MSG_INFO(msg)     CL_LOGENTRYDEFAULT(msg, cyberlogger::Loglevel::INFO)
#define LOG_MSG_WARNING(msg)  CL_LOGENTRYDEFAULT(msg, cyberlogger::Loglevel::WARNING)
#define LOG_MSG_ERROR(msg)    CL_LOGENTRYDEFAULT(msg, cyberlogger::Loglevel::ERROR)
#define LOG_MSG_CRITICAL(msg) CL_LOGENTRYDEFAULT(msg, cyberlogger::Loglevel::CRITICAL)

#ifndef NO_DEFAULT_SINGLETON

#define CL_LOGGER cyberlogger::SingleTonWrapper<cyberlogger::Logger>::getInstance()

#define LOG_UNKNOWN(msg)  CL_LOGGER->log(LOG_MSG_UNKNOWN(msg))
#define LOG_TRACE(msg)    CL_LOGGER->log(LOG_MSG_TRACE(msg))
#define LOG_DEBUG(msg)    CL_LOGGER->log(LOG_MSG_DEBUG(msg))
#define LOG_INFO(msg)     CL_LOGGER->log(LOG_MSG_INFO(msg))
#define LOG_WARNING(msg)  CL_LOGGER->log(LOG_MSG_WARNING(msg))
#define LOG_ERROR(msg)    CL_LOGGER->log(LOG_MSG_ERROR(msg))
#define LOG_CRITICAL(msg) CL_LOGGER->log(LOG_MSG_CRITICAL(msg))


#endif
