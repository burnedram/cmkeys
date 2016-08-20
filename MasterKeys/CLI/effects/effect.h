#pragma once

namespace effects {

	class Effect {
	public:
		Effect(const std::wstring effectName);
		void Log(const std::wstring &entry) const;
		virtual ~Effect() {};
		virtual void KeyEvent(int iRow, int iColumn, bool isPressed) = 0;

		const std::wstring &GetName() const;
	protected:
		const std::wstring mEffectName;
	};

}