#include "SharedStuffLib.h"
#include <filesystem>

std::wstring GetWString(std::string strA)
{
	std::wstring strW(strA.begin(), strA.end());
	return strW;
}
std::string GetString(std::wstring wstr)
{
	return std::string(wstr.begin(), wstr.end());
}
int GetWString(wchar_t* wszDestination, const char* szcStr)
{
	int cbWritten = 0;
	std::string str(szcStr);
	std::wstring wstr = GetWString(str);
	cbWritten = swprintf_s(wszDestination, SZ_SIZE, L"%s", wstr.c_str());
	return cbWritten;
}

void ConfigureLoggers(const wchar_t* wszcProductName, bool bIsDebug)
{
	el::Configurations loggersConfigs;
	loggersConfigs.setToDefault();
	std::wstring wstrProductName(wszcProductName);
	std::wstring wstrLogFileName = 
		L"C:\\Users\\musli\\AppData\\Local\\Temp\\" + wstrProductName + L".log";

	loggersConfigs.setGlobally(el::ConfigurationType::Filename, GetString(wstrLogFileName));
	loggersConfigs.setGlobally(el::ConfigurationType::Format,
		"%datetime %level %func >>>%msg<<<");
	loggersConfigs.set(el::Level::Info, el::ConfigurationType::Format,
		"%datetime %level >>>%msg<<<");
	if (bIsDebug == false) {
		loggersConfigs.setGlobally(el::ConfigurationType::ToStandardOutput, "false");
	}

	el::Loggers::reconfigureAllLoggers(loggersConfigs);

	LOG(INFO) << "Working directory: " << std::filesystem::current_path();
}

