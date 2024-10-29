#ifndef  __DEBUG_HPP__
#define  __DEBUG_HPP__

#include <iostream>

class Debug:public std::ostream 
{
    static bool DebugFlag;    
    int level=0;

    public:
    template<typename T>
    Debug & operator <<(T o)
    {
        if (DebugFlag) {
            std::cout<<"[ Debug:"<<level <<"]"<<o<<std::endl;
        }
        return *this;
    };
};


extern Debug debug;

#endif  