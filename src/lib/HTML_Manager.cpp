#include "HTML_Manager.hpp"
#include "Debug.hpp"
#include <cstring>
#include <filesystem>
#include <fstream>
#include <ios>
#include <string>

htmlManager html_manager;

int htmlManager::init(std::string tar) {

  source = std::filesystem::absolute(tar);
  source = std::filesystem::canonical(tar);

  if (std::filesystem::exists(tar)) {
    debug << source << "exists\n";
    return 0;
  } else {
    return -1;
  }
}

std::string htmlManager::loadResponse(std::string _path) {
  std::ifstream ifile;
  std::filesystem::path tmp;

  // _path="."+_path;
  std::filesystem::path path("."+_path);
  debug << "loadFile " << path << "\n";
  debug << "loadFile " << source << "\n";

  tmp=source / path;
  if(!std::filesystem::exists(tmp))
  {
    return "";
  }

  tmp=std::filesystem::canonical(tmp);
  debug << "loadFile " << tmp << "\n";
  if(!isFileInDirectory(tmp,source ))
  {
  debug << " permission denied " << tmp << "\n";
  return "";
    
  }


  ifile.open(tmp, std::ios::binary);

  if (!ifile) {
    debug << "can't open the path: " << tmp << "\n";
    ifile.close();
    return "";
  }
  ifile.seekg(0, std::ios::end);
  std::streamsize fileSize = ifile.tellg();
  ifile.seekg(0, std::ios::beg);
  std::string fileStr(fileSize, '\0');

  ifile.read(&fileStr[0], fileSize);
  // debug << "path " << tmp << " file size " << fileSize << " content " <<
  // fileStr
  // << "\n";
  // map[path] = fileStr;
  ifile.close();
  return fileStr;
}

// 返回值为长度
std::string htmlManager::getResponse(std::string url) {
  debug << line << " getFile" << url << "\n";
  auto it = map.find(url);
  if (it == map.end()) {
    return loadResponse(url);
  }
  // debug << line << " getFile return " << it->second << "\n";
  return it->second;
}


bool htmlManager::isFileInDirectory(std::filesystem::path file,std::filesystem::path dir)
{
  std::string sfile=file.string();
  std::string sdir=dir.string();
  int count=0;
  for (auto i=sdir.begin(); i!=sdir.end(); i++) {
    if (*i!=sfile[count++]) {
      return  false;
    }
  }
  return  true;
}