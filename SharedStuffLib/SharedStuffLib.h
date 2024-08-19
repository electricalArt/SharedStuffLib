#pragma once

#include <easylogging++.h>

#define SZ_SIZE (size_t)500

std::wstring GetWString(std::string str);
std::string GetString(std::wstring wstr);
int GetWString(wchar_t* wszDestination, const char* szcStr);

/*F+F+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: ConfigureLoggers()

  Summary:  Configures each loggers. Output log file is set to
	$env:temp/<ProductName>.log. The log format is set to preferred.

  Args:     const wchar_t* wszcProductName
			bool bIsDebug

  Returns:  void
-----------------------------------------------------------------F-F*/
void ConfigureLoggers(const wchar_t* wszcProductName, bool bIsDebug);

void RunShellCommand(const wchar_t* wszcCommand, wchar_t* wszOutput);

void PrintCover(const wchar_t* wszcProductName);

void ReplaceCharacter(wchar_t* wszString, wchar_t cOld, wchar_t cNew);
