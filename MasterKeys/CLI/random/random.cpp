#include "stdafx.h"
#include "random.h"

uint16_t Random::Next16() {
	return ((uint16_t)Next8() << 8) | Next8();
}

uint32_t Random::Next32() {
	return ((uint32_t)Next16() << 16) | Next16();
}

uint64_t Random::Next64() {
	return ((uint64_t)Next32() << 32) | Next32();
}

bool Random::Fill(void *pBuffer, size_t bufferSize) {
	size_t remainderSize = bufferSize % sizeof(uint64_t);
	bufferSize -= remainderSize;
	uint64_t *pData = static_cast<uint64_t *>(pBuffer);
	uint64_t *pEnd = reinterpret_cast<uint64_t *>(static_cast<unsigned char *>(pBuffer) + bufferSize);
	while (pData < pEnd)
		*pData++ = Next64();
	if (remainderSize)
	{
		uint64_t remainder = Next64();
		memcpy(pData, &remainder, remainderSize);
	}
	return true;
}
