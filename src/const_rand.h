#ifndef CONST_RAND_H
#define CONST_RAND_H

#include <array>
#include <cstdint>
#include <vector>

#include "unix_timestamp.h"

// xorshf96 init values
static const uint64_t constrand_random_x = 123456789u,
                      constrand_random_y = 362436069u,
                      constrand_random_z = 521288629u;

// LCE, init value values
const static uint32_t constrand_lce_m = 234234234;
const static uint32_t constrand_lce_a = 9348579;
const static uint32_t constrand_lce_c = 74857354;
static uint64_t ctr = 0;

template<typename T>
constexpr uint32_t initvalue() {
	ctr += ((constrand_lce_a * ctr + constrand_lce_c) % constrand_lce_m);
	;
	return ctr + T(UNIX_TIMESTAMP) * T(__TIME_SECONDS__)
#ifdef CONSTRAND_SEED
	       + CONSTRAND_SEED
#endif
	        ;
}

template<typename T>
constexpr static T xorshf96(T &random_x,
                            T &random_y,
                            T &random_z) {
	//period 2^96-1
	uint64_t t = 0;
	random_x ^= random_x << 16u;
	random_x ^= random_x >> 5u;
	random_x ^= random_x << 1u;

	t = random_x;
	random_x = random_y;
	random_y = random_z;
	random_z = t ^ random_x ^ random_y;

	return random_z;
}


template<typename T>
constexpr static T const_uniform_distribution_lce(T &previous) {
	previous = ((constrand_lce_a * previous + constrand_lce_c) % constrand_lce_m);
	return previous;
}


template<typename T>
constexpr static double const_uniform_distribution_n_lce(T &previous) {
	auto dst = const_uniform_distribution_lce<T>(previous);
	return static_cast<double>(dst) / constrand_lce_m;
}


template<typename T>
constexpr static T const_uniform_distribution_xorsh96(T min, T max) {
	auto x = initvalue<T>(),
	     y = initvalue<T>(),
	     z = initvalue<T>();
	return static_cast<T>((xorshf96(x, y, z) % (max - min)) + min);
}

template<typename T>
constexpr static T const_uniform_distribution(T min, T max) {
	return static_cast<T>(const_uniform_distribution_xorsh96<T>(min, max));
}


template<typename T, std::size_t sz>
constexpr static auto const_uniform_distribution_array_lce(T min, T max) {
	std::array<T, sz> dst{};
	auto previous = initvalue<T>();
	for (auto &el: dst)
		el = static_cast<T>(const_uniform_distribution_n_lce(previous) * (max - min) + min);

	return dst;
}

template<typename T, std::size_t sz>
constexpr static auto const_uniform_distribution_array_xorshf96(T min, T max) {
	std::array<T, sz> dst{};
	auto x = initvalue<T>(),
	     y = initvalue<T>(),
	     z = initvalue<T>();

	for (auto &el: dst)
		el = static_cast<T>((xorshf96(x, y, z) % (max - min)) + min);

	return dst;
}


template<typename T, std::size_t sz>
constexpr static auto const_uniform_distribution_vector_xorshf96(T min, T max) {
	std::vector<T> dst{};
	auto x = initvalue<T>(),
	     y = initvalue<T>(),
	     z = initvalue<T>();

	dst.resize(sz);
	for (std::size_t i = 0; i < sz; ++i) {
		dst[i] = static_cast<T>((xorshf96(x, y, z) % (max - min)) + min);
	}
	return dst;
}

template<typename T, std::size_t sz>
constexpr static auto const_uniform_distribution_array(T min, T max) {
	return const_uniform_distribution_array_xorshf96<T, sz>(min, max);
}

template<typename T, std::size_t sz>
constexpr static auto const_uniform_distribution_vector(T min, T max) {
	return const_uniform_distribution_vector_xorshf96<T, sz>(min, max);
}


#endif//CONST_RAND_H
