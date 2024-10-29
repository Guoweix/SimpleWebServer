#ifndef __HTML_MANAGER_HPP__
#define __HTML_MANAGER_HPP__

#include <string>
#include <unordered_map>
#include <iostream>

class htmlManager
{
    std::string source;
    std::unordered_map<std::string, std::string> map;

    int loadFile(std::string path);
    public:
    int init(std::string tar);
    int getFlie(std::string url,char * buffer);
};

extern htmlManager html_manager;
#endif

