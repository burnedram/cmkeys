#pragma once
#include "SDKDLL.h"
#include "bufferedeffect.h"

namespace effects {
	class FullRandomEffect : public BufferedEffect {
	public:
		FullRandomEffect();
		virtual void KeyEvent(int iRow, int iColumn, bool isPressed);
	};
}