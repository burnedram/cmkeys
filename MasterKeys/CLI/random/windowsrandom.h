#pragma once
#include <wincrypt.h>
#include "random.h"

class WindowsRandom : public Random {
public:
	WindowsRandom();
	WindowsRandom(DWORD providerType);
	virtual ~WindowsRandom();

	template<typename T>
	inline T Next();
	virtual uint8_t Next8();
	virtual uint16_t Next16();
	virtual uint32_t Next32();
	virtual uint64_t Next64();
	virtual bool Fill(void *pBuffer, size_t bufferSize);

private:
	HCRYPTPROV _hProv;
};