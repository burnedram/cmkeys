#pragma once

#include "SDKDLL.h"
#include "bufferedeffect.h"

namespace effects {

	class TouchEffect : public BufferedEffect {
	public:
		TouchEffect();
		virtual void KeyEvent(int iRow, int iColumn, bool isPressed);
	private:
		std::default_random_engine mRng;
		std::uniform_int_distribution<int> mRgbDist;
	};

}
