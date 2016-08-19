#include "stdafx.h"
#include "SDKDLL.h"
#include "effect.h"

using namespace std;

namespace effects {

	Effect::Effect(wstring effectName) {
		mEffectName = effectName;
		if (!EnableLedControl(true))
			Log(L"Unable to enable LED control");
	}

	void Effect::Log(wstring entry) {
		wcout << "[" << mEffectName << "] " << entry << endl;
	}

	TouchEffect::TouchEffect() : 
			Effect(L"TouchEffect"), 
			mRgbDist(0, 255)
	{
		memset(&mColorMatrix, 0, sizeof(COLOR_MATRIX));
		if (!SetAllLedColor(mColorMatrix))
			Log(L"Unable to set background");
		if (!RefreshLed(true))
			Log(L"Unable to enable auto refresh");
		mWorker = thread(&TouchEffect::WorkerLoop, this);
	}

	TouchEffect::~TouchEffect() {
		mRun = false;
		unique_lock<mutex> lck(mMutex);
		mCondition.notify_all();
		lck.unlock();
		mWorker.join();
	}

	void TouchEffect::WorkerLoop() {
		while (true) {
			unique_lock<mutex> lck(mMutex);
			if (!mRun)
				break;
			if (!mUpdated)
				mCondition.wait(lck);
			lck.unlock();
			SetAllLedColor(mColorMatrix);
			//this_thread::sleep_for(chrono::milliseconds(1000 / 100));
		}
	}

	void TouchEffect::KeyEvent(int iRow, int iColumn, bool isPressed) {
		BYTE r = mRgbDist(mRng) * isPressed, g = mRgbDist(mRng) * isPressed, b = mRgbDist(mRng) * isPressed;
		unique_lock<mutex> lck(mMutex);
		mUpdated = true;
		mColorMatrix.KeyColor[iRow][iColumn] = KEY_COLOR(r, g, b);
		mCondition.notify_one();
	}
}