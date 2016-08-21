#pragma once
#include "random.h"

class MersenneTwister64Random : public Random {
public:
	MersenneTwister64Random();
	virtual uint8_t Next8();
	virtual uint16_t Next16();
	virtual uint32_t Next32();
	virtual uint64_t Next64();
private:
	std::mt19937_64 _mt;
};