# TemplateSimd
Templated wrapper classes for SSE and AVX simd intrinsics (in progress)

Simd intrinsics are annoying to use when you are doing things with templates, so this attempts to wrap them and make that easier. If you want to use it, you can just include "tsimd.h". Don't worry about the makefile or src/Main.cpp, I'm just using those for testing purposes. For now, only a very limited set of operations is supported, and not all of them have simd algorithms. It also supports very little of the intrinsics so far, primarily only basic arithmetic and logical operations. Integer division is implemented using scalar division because I couldn't find or think of an efficient simd algorithm. Comparisons and conversions are what I plan to work on next. I don't have access to AVX512, so I probably won't be implementing wrappers for it any time soon.

Performance:
I've only tested it with g++ and clang++-6.0 on Linux, and it appears to compile to the same instructions as the equivalent raw intrinsics (**if any level of optimization greater than -O0 is turned on**). I imagine it would be the same on other compilers. I haven't tested it on Windows or with other compilers, but I think it should work on the MSVC and ICC/ICL compilers. It only works on anything if you have the instruction sets you want to use enabled (on g++, flags like -mavx and -msse).

Example:
```
TSimd::vec<float,4> a(1,2,3,4); //{1,2,3,4}
TSimd::vec<float,4> b(2);       //{2,2,2,2}
std::cout<<a*b<<std::endl;      //outputs "2 4 6 8"
```
