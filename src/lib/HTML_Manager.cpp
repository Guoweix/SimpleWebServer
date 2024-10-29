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
  std::string fileStr;
  std::string tmpStr;
 
  if (ifile) {
   while (std::getline(ifile,tmpStr)) {
      fileStr+= tmpStr;
   }
    map[path]=fileStr;
    
    debug<<line<<'\n'; 
  } else {
    debug << "can't open the path: " << path << "\n";
    ifile.close();
    return 1;
  }
  ifile.close();
  return 0;
}

//返回值为长度
std::string htmlManager::getFlie(std::string url) {
  auto it = map.find(url);
  if (it == map.end()) {
    if(loadFile(url))
    {
      return 0;
    }
    it = map.find(url);
  }


  return it->second;
}