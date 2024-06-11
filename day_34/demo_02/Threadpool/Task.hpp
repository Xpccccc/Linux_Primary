#pragma once
#include <string>

using namespace std;

class Task
{
public:
    Task(int a = 0, int b = 0) : _a(a), _b(b), _result(0)
    {
        _result = _a + _b;
    }

    int Result()
    {
        return _result;
    }

    string stringResult()
    {
        return to_string(_a) + " + " + to_string(_b) + " = " + to_string(_result);
    }

    string stringDebug()
    {
        return to_string(_a) + " + " + to_string(_b) + " = ? ";
    }
    void operator()(){ // 重载operator方便threadpool使用t()
        Result();
    }

private:
    int _a;
    int _b;
    int _result;
};