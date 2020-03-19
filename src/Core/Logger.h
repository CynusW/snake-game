#pragma once

#include <fstream>
#include <string>

class Logger
{
public:
    static void Init()
    {
        s_out.open("log.txt");
    }

    template <typename _Ty>
    static void Log(const _Ty& _value)
    {
        s_out << _value;
    }

private:
    static std::ofstream s_out;
};

std::ofstream Logger::s_out;
