#ifndef __SINGLETONWRAP_H__
#define __SINGLETONWRAP_H__

namespace cyberlogger
{
    template <typename T>
    class SingleTonWrapper
    {
    public:
        static T *getInstance()
        {
            static T instance;
            return &instance;
        }

        SingleTonWrapper(const SingleTonWrapper &) = delete;
        SingleTonWrapper &operator=(const SingleTonWrapper &) = delete;
    };

}   // namespace cyberlogger

#endif   // __SINGLETONWRAP_H__