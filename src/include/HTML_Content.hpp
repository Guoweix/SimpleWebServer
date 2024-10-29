#ifndef __HTML_CONTENT_HPP__
#define __HTML_CONTENT_HPP__

#include <string>

class HtmlContent {

  enum StatusCode : int {
    Continue = 100,
    OK = 200,
    Created = 201,
    NotFound = 404,
  };

  static const char
      *StatusCodeStr[120]; 

  StatusCode Status = OK;
  int Content_Length;
  std::string Content_Type;
  int Connect;
  inline int map(int i) { return ((i / 100) - 1) * 20 + (i % 100); };


public:
  std::string Buffer;
  int makeContent();
  static int init();
};

#endif