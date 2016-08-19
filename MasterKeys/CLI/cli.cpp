// MasterKeys.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SDKDLL.h"
#include "commands.h"
#include "util.h"

using namespace std;
/*
#pragma push_macro("max")
#undef max
		wcin.ignore(std::numeric_limits<std::streamsize>::max());
#pragma pop_macro("max")
*/

typedef bool(*cmdFunc_t)(wstring, vector<wstring>);
unordered_map<wstring, cmdFunc_t> cmdMap;

void RegisterCommands() {
	cmdMap[L"quit"] = cmd_Quit;
	cmdMap[L"q"] = cmd_Quit;
	cmdMap[L"echo"] = cmd_Echo;

	cmdMap[L"dev"] = cmd_SetDevice;
	cmdMap[L"plug"] = cmd_CheckPlug;
	cmdMap[L"rgb"] = cmd_RGB;
	cmdMap[L"effect"] = cmd_Effect;
}

int main()
{
	RegisterCommands();

	WCHAR *pszTime;
	wstring cmd;
	vector<wstring> args;
	setprecision(2);
	do {
		wcout << "MEM: " << fixed << setprecision(2) << GetProcessMemoryUsage() / 1024.0 / 1024.0 << "MiB" << endl;

		pszTime = GetNowTime();
		wcout << pszTime;
		//free(pszTime);

		wcout << L"> ";
		getline(wcin, cmd);
		args = split(cmd);
		if (args.empty())
			continue;
		if (!cmdMap[args.front()]) {
			wcout << L"Unknown command \"" << args.front() << "\"" << endl;
			continue;
		}
		if (!cmdMap[args.front()](cmd, args))
			break;
	} while (true);
    return 0;
}

