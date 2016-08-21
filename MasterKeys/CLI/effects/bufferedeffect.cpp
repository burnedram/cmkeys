#include "stdafx.h"
#include "bufferedeffect.h"

using namespace std;

namespace effects {

	BufferedEffect::BufferedEffect(const wstring effectName, COLOR_MATRIX *pMatrix) :
			Effect(effectName),
			m_pMatrix(static_cast<COLOR_MATRIX *>(malloc(sizeof(COLOR_MATRIX)))),
			_pNextMatrix(static_cast<COLOR_MATRIX *>(malloc(sizeof(COLOR_MATRIX)))),
			_pCurrentMatrix(pMatrix)
	{
		memcpy(_pNextMatrix.get(), pMatrix, sizeof(COLOR_MATRIX));
		memcpy(m_pMatrix.get(), pMatrix, sizeof(COLOR_MATRIX));
		while (!RefreshLed(true) && IsDevicePlug());
		_updater = thread(&BufferedEffect::Updater, this);
	}

	static COLOR_MATRIX *keyToMatrix(KEY_COLOR &pKey) {
		COLOR_MATRIX *pMatrix = static_cast<COLOR_MATRIX *>(malloc(sizeof(COLOR_MATRIX)));
		for (size_t row = 0; row < MAX_LED_ROW; row++)
			for (size_t column = 0; column < MAX_LED_COLUMN; column++)
				pMatrix->KeyColor[row][column] = pKey;
		return pMatrix;
	}

	BufferedEffect::BufferedEffect(const wstring effectName, KEY_COLOR &pKey) :
		BufferedEffect(effectName, keyToMatrix(pKey)) {
	}

	BufferedEffect::BufferedEffect(const wstring effectName) :
			BufferedEffect(effectName, new COLOR_MATRIX())
	{
	}

	BufferedEffect::~BufferedEffect() {
		_mRun = false;
		unique_lock<mutex> lck(_mutex);
		_mNeedUpdate = false;
		_cond.notify_all();
		lck.unlock();
		_updater.join();
	}

	void BufferedEffect::SwapBuffer() {
		unique_lock<mutex> lck(_mutex);
		_pNextMatrix.swap(m_pMatrix);
		_mNeedUpdate = true;
		_cond.notify_one();
	}

	void BufferedEffect::CopyBuffer() {
		unique_lock<mutex> lck(_mutex);
		memcpy(_pNextMatrix.get(), m_pMatrix.get(), sizeof(COLOR_MATRIX));
		_mNeedUpdate = true;
		_cond.notify_one();
	}

	void BufferedEffect::Updater() {
		while (true) {
			while (!SetAllLedColor(*_pCurrentMatrix) && _mRun && IsDevicePlug());
			unique_lock<mutex> lck(_mutex);
			if (!_mRun)
				break;
			if (!_mNeedUpdate) {
				_cond.wait(lck);
				if (!_mRun)
					break;
			}
			_pCurrentMatrix.swap(_pNextMatrix);
			_mNeedUpdate = false;
			lck.unlock();
		}
	}

}