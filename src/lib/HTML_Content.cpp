#include "HTML_Content.hpp"
#include <cstring>
#include <random>
#include <string>

// "HTTP/1.1 200 OK\r\n"
// "Content-Type: text/html\r\n"
// "Connection: close\r\n"
// "\r\n"
// "<html><body><h1>Hello, World!</h1></body><script
// src=\"script.js\"></script></html>";
const char* HtmlContent::StatusCodeStr[120];

int HtmlContent::makeContent() {
  Buffer += "HTTP/1.1 " + std::to_string(Status) + " " + StatusCodeStr[Status] +
            "\r\n";
  Buffer += "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n";

  return 0;
}

int HtmlContent::init() {
  StatusCodeStr[0] = "Continue";
  StatusCodeStr[1] = "Switching Protocols";
  StatusCodeStr[10] = "OK";
  StatusCodeStr[11] = "Created";
  StatusCodeStr[12] = "Accepted";
  StatusCodeStr[34] = "Not Found";
  return 0;
}