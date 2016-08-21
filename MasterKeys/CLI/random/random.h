#pragma once

class Random {
public:
	Random() {};
	virtual ~Random() {};

	virtual uint8_t Next8() = 0;
	virtual uint16_t Next16();
	virtual uint32_t Next32();
	virtual uint64_t Next64();
	virtual bool Fill(void *pBuffer, size_t bufferSize);
};