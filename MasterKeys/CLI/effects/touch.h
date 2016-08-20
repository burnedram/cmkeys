#pragma once

#include "SDKDLL.h"
#include "effect.h"

namespace effects {

	class TouchEffect : public Effect {
	public:
		TouchEffect();
		~TouchEffect();
		virtual void KeyEvent(int iRow, int iColumn, bool isPressed);
	private:
		std::mutex mMutex;
		std::condition_variable mCondition;
		std::thread mWorker;
		void WorkerLoop();
		volatile bool mRun = true;
		volatile bool mUpdated = false;

		std::default_random_engine mRng;
		std::uniform_int_distribution<int> mRgbDist;
		COLOR_MATRIX mColorMatrix;
	};

}
