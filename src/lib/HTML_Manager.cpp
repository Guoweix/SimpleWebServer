#include "HTML_Manager.hpp"
#include "Debug.hpp"
#include <cstring>
#include <fstream>
#include <string>

htmlManager html_manager;

int htmlManager::init(std::string tar) {
  source = tar;
  return 0;
}

int htmlManager::loadFile(std::string path) {
  std::ifstream ifile;
  std::string tmp;
  tmp = source + path;

  ifile.open(tmp);
  debug << tmp << "\n";
char getstr[1000];
ifile.getline(getstr,1000);
  debug << std::string((std::istreambuf_iterator<char>(ifile)),
                            std::istreambuf_iterator<char>());
 
  if (ifile) {
    map[path] = std::string((std::istreambuf_iterator<char>(ifile)),
                            std::istreambuf_iterator<char>());
  } else {
    debug << "can't open the path: " << path << "\n";
    ifile.close();
    return 1;
  }
  ifile.close();
  return 0;
}

int htmlManager::getFlie(std::string url, char *buffer) {
  auto it = map.find(url);
  if (it == map.end()) {
    loadFile(url);
  }
  strcpy(buffer, it->second.c_str());
  return it->second.length();
}