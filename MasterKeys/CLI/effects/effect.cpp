#include "stdafx.h"
#include "SDKDLL.h"
#include "effect.h"

using namespace std;

namespace effects {

	Effect::Effect(const wstring effectName) : 
			mEffectName(effectName) {
		if (!EnableLedControl(true))
			Log(L"Unable to enable LED control");
	}

	void Effect::Log(const wstring &entry) const {
		wcout << "[" << mEffectName << "] " << entry << endl;
	}

	const wstring &Effect::GetName() const {
		return mEffectName;
	}

}