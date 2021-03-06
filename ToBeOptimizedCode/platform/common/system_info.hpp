#pragma once

#include <platform/platform_def.hpp>

#ifdef __LINUX__
#include <sys/sysinfo.h>
#include <unistd.h>
#endif

#ifdef __WINDOWS__
#include <windows.h>
#endif

class SystemInfo
{
 public:
  static int GetCPUNum();
};

