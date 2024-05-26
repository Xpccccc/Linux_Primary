#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include <iostream>
#include <string>
#include <unistd.h>
#include <functional>
#include <pthread.h>

using namespace std;

// 封装Linux线程
namespace ThreadModule
{
    template <class T>
    using func_t = function<void(T&)>;

    template <class T>
    class Thread
    {
    public:
        Thread(func_t<T> func, T& data, const string& name = "default name") : _func(func), _data(data), _threadname(name), _stop(true) {}
    
        void Execute()
        {
            _func(_data);
        }

        //  隐含this
        static void *threadroutine(void *arg)
        {
            Thread<T> *self = static_cast<Thread<T> *>(arg);
            self->Execute();
            // _func(_data);// static 访问不了成员变量
            return nullptr;
        }
        bool Start()
        {
            int n = pthread_create(&_tid, nullptr, threadroutine, this);
            if (!n)
            {
                _stop = false;
                return true;
            }
            else
            {
                return false;
            }
        }

        void Detach()
        {
            if (!_stop)
            {
                pthread_detach(_tid);
            }
        }

        void Join()
        {
            if (!_stop)
            {
                pthread_join(_tid, nullptr);
            }
        }

        string name()
        {
            return _threadname;
        }

        void Stop()
        {
            _stop = true;
        }

    private:
        pthread_t _tid;
        string _threadname;
        T& _data;
        func_t<T> _func; 
        bool _stop;
    };
    
} // namespace ThreadModule

#endif