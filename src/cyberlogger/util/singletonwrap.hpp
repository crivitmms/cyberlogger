#pragma once

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

