#pragma once

namespace effects {

	class Effect {
	public:
		Effect(std::wstring effectName);
		void Log(std::wstring entry);
		virtual ~Effect() {};
		virtual void KeyEvent(int iRow, int iColumn, bool isPressed) = 0;
	protected:
		std::wstring mEffectName;
	};

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