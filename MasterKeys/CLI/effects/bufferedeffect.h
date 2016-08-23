#pragma once

#include "SDKDLL.h"
#include "effect.h"

namespace effects {

	class BufferedEffect : public Effect {
	public:
		BufferedEffect(const std::wstring effectName, COLOR_MATRIX *pMatrix);
		BufferedEffect(const std::wstring effectName, KEY_COLOR &pKey);
		BufferedEffect(const std::wstring effecName);
		virtual ~BufferedEffect();
		virtual void KeyEvent(int iRow, int iColumn, bool isPressed) = 0;

	protected:
		std::unique_ptr<COLOR_MATRIX> m_pMatrix;
		void SwapBuffer();
		void CopyBuffer();

	private:
		std::mutex _mutex;
		std::condition_variable _cond;
		std::unique_ptr<COLOR_MATRIX> _pNextMatrix;
		std::unique_ptr<COLOR_MATRIX> _pCurrentMatrix;
		std::thread _updater;
		void Updater();
		volatile bool _mRun = true;
		volatile bool _mNeedUpdate = false;
	};

}
