#include "stdafx.h"
#include "touch.h"
#include "random/windowsrandom.h"

using namespace std;

namespace effects {

	TouchEffect::TouchEffect() : 
		BufferedEffect(L"TouchEffect", KEY_COLOR(0, 0, 0)),
		_rng(make_unique<WindowsRandom>())
	{
	}

	void TouchEffect::KeyEvent(int iRow, int iColumn, bool isPressed) {
		if (isPressed)
			_rng->Fill(&m_pMatrix->KeyColor[iRow][iColumn], sizeof(KEY_COLOR));
		else
			memset(&m_pMatrix->KeyColor[iRow][iColumn], 0, sizeof(KEY_COLOR));
		CopyBuffer();
	}

}