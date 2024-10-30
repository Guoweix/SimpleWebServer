#include "HTML_Content.hpp"
#include "Debug.hpp"
#include <cstring>
#include <string>

// "HTTP/1.1 200 OK\r\n"
// "Content-Type: text/html\r\n"
// "Connection: close\r\n"
// "\r\n"
// "<html><body><h1>Hello, World!</h1></body><script
// src=\"script.js\"></script></html>";
const char* HtmlContent::StatusCodeStr[120];

int HtmlContent::makeContent(StatusCode _Status) {
  Status=_Status;
  debug<<map(Status)<<'\n';
  debug<<StatusCodeStr[map(Status)]<<'\n';
  Buffer += "HTTP/1.1 " + std::to_string(Status) + " " + StatusCodeStr[map(Status)] +
            "\r\n";
  Buffer += "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n";

  return 0;
}

int HtmlContent::init() {
  StatusCodeStr[0] = "Continue";
  StatusCodeStr[1] = "Switching Protocols";
  StatusCodeStr[20] = "OK";
  StatusCodeStr[21] = "Created";
  StatusCodeStr[22] = "Accepted";
  StatusCodeStr[64] = "Not Found";
  return 0;
}