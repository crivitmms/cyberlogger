#define makeLogEntry(LoglevelClass, msg, loglevel) LogEntry(msg, LoglevelClass(loglevel), __FILE__, __LINE__)

#define LogEntryDefault(msg, loglevel) makeLogEntry(Loglevel, msg, loglevel)