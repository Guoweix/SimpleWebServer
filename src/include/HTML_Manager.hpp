#ifndef __HTML_MANAGER_HPP__
#define __HTML_MANAGER_HPP__

#include <string>
#include <unordered_map>
#include <filesystem>


class htmlManager
{
    std::filesystem::path source;
    std::unordered_map<std::string, std::string> map;

    std::string loadResponse(std::string path);
    bool isFileInDirectory(std::filesystem::path,std::filesystem::path);

    public:
    int init(std::string tar);
    std::string getResponse(std::string url);


};

extern htmlManager html_manager;
#endif

