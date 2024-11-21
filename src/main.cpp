
#include <iostream>
#include <thread>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <Debug.hpp>
#include <HTML_Manager.hpp>
#include <HTML_Content.hpp>
#include <fstream>

using  namespace std; 
unsigned int PORT=80;
string PATH;

#define BUFFER_SIZE 4096

string getUrl(char * buffer)
{
    int i=0,j;
    while(buffer[i]!=' ')
        i++;
    
    j=i+1;
    while(buffer[j]!=' ')
        j++;
    buffer[j]=0;
    return string(&buffer[i+1]);
}

void handle_client(int client_socket) {
    debug<< line <<"\n";
    char buffer[BUFFER_SIZE];
    read(client_socket, buffer, sizeof(buffer) - 1);

    debug<<"get BUFFER"<<buffer<<"\n";

    string url=getUrl(buffer);

    string file=html_manager.getResponse(url);

    HtmlContent header;
    // 准备响应
    // const char *http_response = "HTTP/1.1 200 OK\r\n"
    //                             "Content-Type: text/html\r\n"
    //                             "Connection: close\r\n"
    //                             "\r\n"
    //                             "<html><body><h1>Hello, World!</h1></body><script src=\"script.js\"></script></html>";

    std::string  http_response;

    if (!file.empty()) {
        header.makeContent(HtmlContent::StatusCode::OK);
        http_response=header.Buffer+file;
    }
    else {
        header.makeContent(HtmlContent::StatusCode::NotFound);
        http_response=header.Buffer;
    }
    
    // 发送响应
    write(client_socket, http_response.c_str(), http_response.length());
    
    // 关闭连接
    close(client_socket);
}

int read_opt()
{
    ifstream opt_file;
    opt_file.open("opt.txt",ios::in);
    if(!opt_file)
    {
        cerr<<"Configuration file does not exist,using default file"<<endl;
    }
    string tmp;

    getline(opt_file,tmp);
    PORT= stoi(tmp);

    getline(opt_file,PATH);
    html_manager.init(PATH);

    HtmlContent::init();

    opt_file.close();
    return 0;
}

int init_socket(int & server_socket, sockaddr_in & server_addr)
{
    // 创建 socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr<<"Socket creation failed"<<endl;
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 绑定 socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr <<"Bind failed"<<std::endl;
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // 监听连接
    if (listen(server_socket, 3) < 0) {
        std::cerr <<"Listen failed"<<std::endl;
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    return 0;
}


int main() {
    int server_socket, client_socket;
    sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    read_opt();

    init_socket(server_socket,server_addr);

    std::cout<<"Server is running on port "<<PORT<<endl;

    while (1) {
        // 接受客户端连接
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        std::thread(handle_client,client_socket).detach();
        // 处理客户端请求
    }

    // 关闭服务器 socket
    close(server_socket);
    return 0;
}