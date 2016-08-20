#pragma once
#include "SDKDLL.h"
#include "effect.h"

namespace effects {
	class FullRandomEffect : public Effect {
	public:
		FullRandomEffect();
		virtual void KeyEvent(int iRow, int iColumn, bool isPressed);
	private:
		COLOR_MATRIX mColorMatrix;
	};
}