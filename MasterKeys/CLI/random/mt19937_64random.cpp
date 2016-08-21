#include "stdafx.h"
#include "mt19937_64random.h"
#include <random>

using namespace std;

// http://codereview.stackexchange.com/questions/109260/seed-stdmt19937-from-stdrandom-device?answertab=votes#tab-top
template<class T = mt19937, size_t N = T::state_size>
static auto ProperlySeededRandomEngine() -> typename enable_if<!!N, T>::type {
	typename T::result_type random_data[N];
	random_device source;
	generate(begin(random_data), end(random_data), ref(source));
	seed_seq seeds(begin(random_data), end(random_data));
	T seededEngine(seeds);
	return seededEngine;
}

MersenneTwister64Random::MersenneTwister64Random() :
	_mt(ProperlySeededRandomEngine<mt19937_64>())
{
}

uint8_t MersenneTwister64Random::Next8() {
	return (uint8_t)_mt();
}

uint16_t MersenneTwister64Random::Next16() {
	return (uint16_t)_mt();
}

uint32_t MersenneTwister64Random::Next32() {
	return (uint32_t)_mt();
}

uint64_t MersenneTwister64Random::Next64() {
	return (uint64_t)_mt();
}
