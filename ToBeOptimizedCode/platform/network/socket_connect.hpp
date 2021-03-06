#pragma once

#include "socket_def.hpp"

#ifdef __LINUX__
#include <cstring>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#endif
#ifdef __WINDOWS__
#include <queue>

//#define _WINSOCK_DEPRECATED_NO_WARNINGS

#endif

class ISocketHandler;

class SocketConnect
{
 public:
  SocketConnect();
  ~SocketConnect();
  
  void ResetHandler(ISocketHandler *handler = NULL);

  bool Connect(IPAddr ip, Port port);
  bool Write(const char *data, int length);
  bool Disconnect();

  bool CheckOnHandle(IPAddr ip, Port port);
  Port GetLocalPort() { return local_port_;  }

 protected:
  ISocketHandler *handler_;

  bool running_;

  IPAddr remote_ip_addr_;
  Port remote_port_;
  Port local_port_;

  char buff_[MAX_SOCKET_MSG_BUFF_LENGTH];

#ifdef __LINUX__
  int local_sock_;

  struct epoll_event epoll_event_list_[MAX_EPOLL_EVENTS];
  int epoll_fd_;
#endif
#ifdef __WINDOWS__
  SOCKET local_sock_;
#endif
};

