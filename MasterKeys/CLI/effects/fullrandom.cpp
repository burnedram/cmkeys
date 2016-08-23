#include "stdafx.h"
#include "fullrandom.h"
#include "random\windowsrandom.h"

using namespace std;

namespace effects {

	FullRandomEffect::FullRandomEffect() :
		BufferedEffect(L"FullRandomEffect"),
		_rng(make_unique<WindowsRandom>())
	{
	}

	void FullRandomEffect::KeyEvent(int iRow, int iColumn, bool isPressed) {
		_rng->Fill(m_pMatrix.get(), sizeof(COLOR_MATRIX));
		SwapBuffer();
	}

}