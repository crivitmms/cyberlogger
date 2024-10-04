#ifndef __EASY_LOGENTRY_H__
#define __EASY_LOGENTRY_H__

#define makeLogEntry(LoglevelClass, msg, loglevel) LogEntry(msg, LoglevelClass(loglevel), __FILE__, __LINE__)

#define LogEntryDefault(msg, loglevel) makeLogEntry(Loglevel, msg, loglevel)

#define LOG_MSG_UNKNOWN(msg)  LogEntryDefault(msg, cyberlogger::Loglevel::UNKNOWN)
#define LOG_MSG_TRACE(msg)    LogEntryDefault(msg, cyberlogger::Loglevel::TRACE)
#define LOG_MSG_DEBUG(msg)    LogEntryDefault(msg, cyberlogger::Loglevel::DEBUG)
#define LOG_MSG_INFO(msg)     LogEntryDefault(msg, cyberlogger::Loglevel::INFO)
#define LOG_MSG_WARNING(msg)  LogEntryDefault(msg, cyberlogger::Loglevel::WARNING)
#define LOG_MSG_ERROR(msg)    LogEntryDefault(msg, cyberlogger::Loglevel::ERROR)
#define LOG_MSG_CRITICAL(msg) LogEntryDefault(msg, cyberlogger::Loglevel::CRITICAL)

#ifndef NO_DEFAULT_SINGLETON

#define LOGGER cyberlogger::SingleTonWrapper<cyberlogger::Logger>::getInstance()

#define LOG_UNKNOWN(msg)  LOGGER->log(LOG_MSG_UNKNOWN(msg))
#define LOG_TRACE(msg)    LOGGER->log(LOG_MSG_TRACE(msg))
#define LOG_DEBUG(msg)    LOGGER->log(LOG_MSG_DEBUG(msg))
#define LOG_INFO(msg)     LOGGER->log(LOG_MSG_INFO(msg))
#define LOG_WARNING(msg)  LOGGER->log(LOG_MSG_WARNING(msg))
#define LOG_ERROR(msg)    LOGGER->log(LOG_MSG_ERROR(msg))
#define LOG_CRITICAL(msg) LOGGER->log(LOG_MSG_CRITICAL(msg))

#endif

#endif   // __EASY_LOGENTRY_H__