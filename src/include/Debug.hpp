#ifndef  __DEBUG_HPP__
#define  __DEBUG_HPP__

#include <iostream>

#define line __FILE__<<":"<<__LINE__

class Debug:public std::ostream 
{
    static bool DebugFlag;    
    int level=0;

    public:
    template<typename T>
    Debug & operator <<(T o)
    {
        if (DebugFlag) {
            std::cout<<o;
        }
        return *this;
    };
};


extern Debug debug;

#endif  