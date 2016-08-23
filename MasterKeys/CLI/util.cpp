#include "stdafx.h"
#include "SDKDLL.h"
#include "util.h"

#include <sstream>

using namespace std;

SIZE_T GetProcessMemoryUsage() {
	PROCESS_MEMORY_COUNTERS memInfo;
	GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(PROCESS_MEMORY_COUNTERS));
	return memInfo.WorkingSetSize;
}

vector<wstring> split(wstring const &input) {
	wistringstream buffer(input);
	vector<wstring> ret;

	typedef istream_iterator<wstring, wchar_t, std::char_traits<wchar_t> > wistream_iterator_wstring;
	copy(wistream_iterator_wstring(buffer),
		wistream_iterator_wstring(),
		back_inserter(ret));
	return ret;
}

const wstring DeviceName(DEVICE_INDEX dev) {
	switch (dev) {
	case (DEV_MKeys_S):
		return L"MasterKeys Pro S";
	default:
		return L"Unknown";
	}
}