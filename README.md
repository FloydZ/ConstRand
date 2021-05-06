`const_rand` is a C++ 11 `constexpr` base Pseudo Random Generator (PRNG) based on `xorshf96`. This  makes it super-fast. 
The question is, why should you need a prng which generates random bytes based upon compile time generation. And the answer is: why not?

This repo is useful if you need to generated keys only once, and before the program runs. Any cryptographic appilcation could benefit from this.

WARNING
---
The inital seed of the `xorshf96` is currently just the UNIX time stamp. 
DO NOT USE THIS CODE IN ANYTHING IMPORTANT. 
You have been warned. 

Addtionial Options
----
You can pass `-DCONSTRAND_SEED XYZ` as an additional compiler flag to further seed the RNG.