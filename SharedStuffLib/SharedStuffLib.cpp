#include "SharedStuffLib.h"
#include <filesystem>
#include <array>

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

void RunShellCommand(const wchar_t* wszcCommand, wchar_t* wszOutput)
{
	std::array<wchar_t, 128> buffer;
	std::wstring result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_wpopen(wszcCommand, L"r"), _pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgetws(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	wcscpy_s(wszOutput, 50000, result.c_str());
}

void PrintCover(const wchar_t* wszcProductName)
{
	const wchar_t* wszcBanner = 
LR"BANNER(>>===================================================================<<
||                                                                   ||
||     $$$$$$\                                           $$\         ||
||    $$  __$$\                                          $$ |        ||
||    $$ /  \__| $$$$$$\   $$$$$$$\  $$$$$$\   $$$$$$\ $$$$$$\       ||
||    \$$$$$$\  $$  __$$\ $$  _____|$$  __$$\ $$  __$$\\_$$  _|      ||
||     \____$$\ $$$$$$$$ |$$ /      $$ |  \__|$$$$$$$$ | $$ |        ||
||    $$\   $$ |$$   ____|$$ |      $$ |      $$   ____| $$ |$$\     ||
||    \$$$$$$  |\$$$$$$$\ \$$$$$$$\ $$ |      \$$$$$$$\  \$$$$  |    ||
||     \______/  \_______| \_______|\__|       \_______|  \____/     ||
||                                                                   ||
||                                                                   ||
||    $$\      $$\                     $$\                           ||
||    $$ | $\  $$ |                    $$ |                          ||
||    $$ |$$$\ $$ | $$$$$$\   $$$$$$\  $$ |  $$\  $$$$$$$\           ||
||    $$ $$ $$\$$ |$$  __$$\ $$  __$$\ $$ | $$  |$$  _____|          ||
||    $$$$  _$$$$ |$$ /  $$ |$$ |  \__|$$$$$$  / \$$$$$$\            ||
||    $$$  / \$$$ |$$ |  $$ |$$ |      $$  _$$<   \____$$\           ||
||    $$  /   \$$ |\$$$$$$  |$$ |      $$ | \$$\ $$$$$$$  |          ||
||    \__/     \__| \______/ \__|      \__|  \__|\_______/           ||
||                                                                   ||
>>===================================================================<<
It's silent. Shhh...!)BANNER";

	wprintf(L"%s\n\n", wszcBanner);
	//wprintf(L"Product name: %s\n", wszcProductName);
}

void ReplaceCharacter(wchar_t* wszString, wchar_t cOld, wchar_t cNew)
{
	for (int i = 0; i < wcslen(wszString); i++) {
		if (wszString[i] == cOld) {
			wszString[i] = cNew;
		}
	}
}
