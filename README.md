# TemplateSimd
Templated wrapper classes for SSE and AVX simd intrinsics (in progress)

Simd intrinsics are annoying to use when you are doing things with templates, so this attempts to wrap them and make that easier. If you want to use it, you can just include "tsimd.h". It supports a decent amount of the simd intrinsics and provides implementations for some things that aren't part of the intrinsics. Certain operations are implemented using scalars because I couldn't figure out how to do them efficiently with simd. I don't have access to AVX512 or a non-intel processor, so I probably won't be implementing wrappers for AVX512 or other SIMD instruction sets any time soon.

Performance:
I've only tested it with g++ and clang++ on Linux, and it goes pretty much as fast as raw intrinsics (in the sense that the classes have no overhead) if any level of optimization greater than -O0 is turned on. I imagine it would be the same on other compilers. I haven't tested it on Windows or with other compilers, but I think it should work on the MSVC and ICC/ICL compilers. It only works on anything if you have the instruction sets you want to use enabled (on g++, flags like -mavx and -msse).

Example:
```
TSimd::vec<float,4> a(1,2,3,4); //{1,2,3,4}
TSimd::vec<float,4> b(2);       //{2,2,2,2}
std::cout<<a*b<<std::endl;      //outputs "2 4 6 8"
```
