#pragma once
#include "SDKDLL.h"
#include "bufferedeffect.h"
#include "random/random.h"

namespace effects {
	class FullRandomEffect : public BufferedEffect {
	public:
		FullRandomEffect();
		virtual void KeyEvent(int iRow, int iColumn, bool isPressed);

	private:
		std::unique_ptr<Random> _rng;
	};
}