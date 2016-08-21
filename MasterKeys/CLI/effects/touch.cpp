#include "stdafx.h"
#include "touch.h"

using namespace std;

namespace effects {

	TouchEffect::TouchEffect() : 
			BufferedEffect(L"TouchEffect", KEY_COLOR(0, 0, 0)),
			mRgbDist(0, 255)
	{
	}

	void TouchEffect::KeyEvent(int iRow, int iColumn, bool isPressed) {
		BYTE r = mRgbDist(mRng) * isPressed, g = mRgbDist(mRng) * isPressed, b = mRgbDist(mRng) * isPressed;
		m_pMatrix->KeyColor[iRow][iColumn] = KEY_COLOR(r, g, b);
		CopyBuffer();
	}

}