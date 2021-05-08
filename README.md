Information
---
`const_rand` is a C++ 11 `constexpr` pseudo random generator (prng) based on `xorshf96`. The question is, why should you need a prng which generates random bytes while compiling? Why not? This repo is useful if you need to generated keys/nonces/tokens/seeds only once and before the program runs. 

WARNING
---
The initial seed of `xorshf96` is currently just the UNIX time stamp. DO NOT USE THIS CODE IN ANYTHING IMPORTANT. You have been warned. 

Additional Options
----
One can pass `-DCONSTRAND_SEED XYZ` as an additional compiler flag to further seed the rng.

Examples
---
In [examples.cpp](https://github.com/FloydZ/ConstRand/blob/master/example.cpp) are some examples regarding the usage. The main functions are
```cpp

// random array of type
//  std::array<T, sz>
template <typename T, std::size_t sz>
constexpr static auto const_uniform_distribution_array(T min, T max);

// random vector of type
//  std::vector<T>
template <typename T, std::size_t sz>
constexpr static auto const_uniform_distribution_vector(T min, T max);

// random value of type T
template <typename T>
constexpr static T const_uniform_distribution(T min, T max);
```

TODO
---
- generate random struct, class, maps, sets maybe through `uint8_t *` or `dynamic_cast<>` casts?