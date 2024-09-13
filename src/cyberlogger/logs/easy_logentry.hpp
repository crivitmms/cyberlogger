#define uniqueLogEntry(LoglevelClass, msg, loglevel) std::make_unique<LogEntry>(LogEntry(msg, std::make_unique<LoglevelClass>((int)loglevel), __FILE__, __LINE__))

#define uniqueLogEntryDefault(msg, loglevel) uniqueLogEntry(Loglevel, msg, loglevel)