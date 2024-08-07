#pragma once

#include <easylogging++.h>

#define SZ_SIZE (size_t)500

std::wstring GetWString(std::string str);
std::string GetString(std::wstring wstr);
int GetWString(wchar_t* wszDestination, const char* szcStr);

/*F+F+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: ConfigureLoggers()

  Summary:  Configures each loggers with default settings.

  Args:     szcLogFileName

  Returns:  void
-----------------------------------------------------------------F-F*/
void ConfigureLoggers(const wchar_t* szcProductName, bool bIsDebug);
