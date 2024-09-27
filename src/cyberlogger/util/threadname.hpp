#ifndef __THREADNAME_H__
#define __THREADNAME_H__

#ifdef _WIN32
#include <Windows.h>
#elif defined(__linux__)
#include <pthread.h>
#include <sys/prctl.h>
#elif defined(__APPLE__)
#include <pthread.h>
#include <pthread_np.h>
#endif

#include <string>

inline void SetThreadName(const std::string &threadName)
{
#ifdef _WIN32
    // Windows
    SetThreadDescription(GetCurrentThread(), threadName.c_str());
#elif defined(__linux__)
    // Linux
    prctl(PR_SET_NAME, threadName.c_str(), 0, 0, 0);
#elif defined(__APPLE__)
    // macOS
    pthread_setname_np(threadName.c_str());
#endif
}

inline std::string GetThreadName()
{
    std::string threadName;
#if defined(_WIN32)
    // Windows
    // Not implemented
    threadName = "";   // Placeholder
#elif defined(__linux__)
    // Linux
    char buffer[16];   // flawfinder: ignore
    if (prctl(PR_GET_NAME, buffer) != 0)
    {
        threadName = "Unknown";   // Error retrieving thread name
    }
    else
    {
        threadName = buffer;
    }
#elif defined(__APPLE__)
    // macOS
    char buffer[1024];   // flawfinder: ignore
    if (pthread_getname_np(pthread_self(), buffer, sizeof(buffer)) != 0)
    {
        threadName = "Unknown";   // Error retrieving thread name
    }
    else
    {
        threadName = buffer;
    }
#endif
    return threadName;
}

#endif   // __THREADNAME_H__