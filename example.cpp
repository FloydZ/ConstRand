#include <cstdint>
#include <limits>
#include <iostream>

#include "const_rand.h"

int main() {
	constexpr std::size_t size = 50;

	// Array Type
	auto a = const_uniform_distribution_array<uint32_t, size>(
			std::numeric_limits<uint32_t>::min(),
			std::numeric_limits<uint32_t>::max()
		);

	// Vector Type
	auto v = const_uniform_distribution_vector<uint32_t, size>(
			std::numeric_limits<uint32_t>::min(),
			std::numeric_limits<uint32_t>::max()
	);

	for (const auto A: a) { std::cout << A << ","; }
	std::cout <<"\n";
	for (const auto V: v) { std::cout << V << ","; }

	// Simple Type
	std::cout << "\nRandom Bit: " << const_uniform_distribution(0, 2) << "\n";
	return 0;
}