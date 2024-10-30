#include "HTML_Manager.hpp"
#include "Debug.hpp"
#include <cstring>
#include <fstream>
#include <ios>
#include <string>

htmlManager html_manager;

int htmlManager::init(std::string tar) {
  source = tar;
  return 0;
}

int htmlManager::loadFile(std::string path) {
  std::ifstream ifile;
  std::string tmp;
  debug << "loadFile " << path << "\n";

  tmp = source + path;
  ifile.open(tmp, std::ios::binary);

  if (!ifile) {
    debug << "can't open the path: " << path << "\n";
    ifile.close();
    return 1;
  }
  ifile.seekg(0, std::ios::end);
  std::streamsize fileSize = ifile.tellg();
  ifile.seekg(0, std::ios::beg);
  std::string fileStr(fileSize, '\0');

  ifile.read(&fileStr[0], fileSize);
  debug << "path " << tmp << " file size " << fileSize << " content " << fileStr
        << "\n";
  map[path] = fileStr;
  ifile.close();
  return 0;
}

// 返回值为长度
std::string htmlManager::getFlie(std::string url) {
  debug << line << " getFile" << url << "\n";
  auto it = map.find(url);
  if (it == map.end()) {
    if (loadFile(url)) {
      return "";
    }
    it = map.find(url);
  }
  debug << line << " getFile return " << it->second << "\n";
  return it->second;
}