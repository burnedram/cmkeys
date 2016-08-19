#include "stdafx.h"
#include "SDKDLL.h"
#include "commands.h"
#include "util.h"
#include "effect.h"

using namespace std;

bool bDeviceSet = false;
DEVICE_INDEX currentDevice;
effects::Effect* pCurrentEffect = nullptr;

bool cmd_Quit(wstring cmd, vector<wstring> args) {
	if (pCurrentEffect) {
		EnableKeyInterrupt(false);
		SetKeyCallBack(nullptr);
		delete pCurrentEffect;
	}
	if (!EnableLedControl(true) || !SwitchLedEffect(EFF_BREATH_CYCLE)) {
		wcout << L"Unable to set effect" << endl;
		Sleep(2000);
	}
	EnableLedControl(false);
	wcout << L"Bye!" << endl;
	return false;
}

bool cmd_Echo(wstring cmd, vector<wstring> args) {
	wcout << cmd << endl;
	return true;
}

bool cmd_SetDevice(wstring cmd, vector<wstring> args) {
	if (args.size() == 1 && !bDeviceSet) {
		wcout << L"No device has been set" << endl;
		return true;
	}
	if (args.size() > 2) {
		wcout << L"Expected zero or one argument" << endl;
		return true;
	}
	if (args.size() == 2) {
		wstring dev = args[1];
		if (!dev.compare(L"s")) {
			currentDevice = DEV_MKeys_S;
		}
		else {
			wcout << L"Unknown device \"" << dev << "\"" << endl;
			return true;
		}
		SetControlDevice(currentDevice);
		bDeviceSet = true;
		wcout << L"New device: ";
	}
	wcout << DeviceName(currentDevice) << endl;
	return true;
}

bool cmd_CheckPlug(wstring cmd, vector<wstring> args) {
	bool plug = IsDevicePlug();
	wcout << (plug ? L"true" : L"false") << endl;
	return true;
}

bool cmd_RGB(wstring cmd, vector<wstring> args) {
	if (args.size() != 4) {
		wcout << L"Expected four argumens" << endl;
		return true;
	}

	BYTE r = stoi(args[1]), g = stoi(args[2]), b = stoi(args[3]);
	if (!EnableLedControl(true)) {
		wcout << "Unable to enable LED control" << endl;
		return true;
	}
	if (!SetFullLedColor(r, g, b)) {
		wcout << "Unable to set LED color" << endl;
		return true;
	}
	if (!RefreshLed(false)) {
		wcout << "Unable to refresh LEDs" << endl;
		return true;
	}
	return true;
}

void CALLBACK effectWrapper(int iRow, int iColumn, bool isPressed) {
	pCurrentEffect->KeyEvent(iRow, iColumn, isPressed);
}

bool cmd_Effect(wstring cmd, vector<wstring> args) {
	if (!EnableKeyInterrupt(true)) {
		wcout << "Unable to enable key interrupt" << endl;
		return true;
	}
	if (pCurrentEffect) {
		SetKeyCallBack(nullptr);
		delete pCurrentEffect;
	}
	pCurrentEffect = new effects::TouchEffect();
	SetKeyCallBack(effectWrapper);
	return true;
}
