#ifndef REINTERPRET_H
#define REINTERPRET_H

#include "../tsimd.h"

namespace TSimd{
    template<typename T, typename U> TSIMD_INLINE T reinterpret(const U a){
        return T(reinterpret<decltype(T::data),decltype(U::data)>(a.data));
    }
    #ifdef __SSE__
        template<> TSIMD_INLINE __m128 reinterpret(const __m128 a){
            return a;
        }
    #endif
    #ifdef __SSE2__
        template<> TSIMD_INLINE __m128 reinterpret(const __m128i a){
            return _mm_castsi128_ps(a);
        }
        template<> TSIMD_INLINE __m128 reinterpret(const __m128d a){
            return _mm_castpd_ps(a);
        }
        template<> TSIMD_INLINE __m128i reinterpret(const __m128 a){
            return _mm_castps_si128(a);
        }
        template<> TSIMD_INLINE __m128i reinterpret(const __m128i a){
            return a;
        }
        template<> TSIMD_INLINE __m128i reinterpret(const __m128d a){
            return _mm_castpd_si128(a);
        }
        template<> TSIMD_INLINE __m128d reinterpret(const __m128 a){
            return _mm_castps_pd(a);
        }
        template<> TSIMD_INLINE __m128d reinterpret(const __m128i a){
            return _mm_castsi128_pd(a);
        }
        template<> TSIMD_INLINE __m128d reinterpret(const __m128d a){
            return a;
        }
    #endif
    #ifdef __AVX__
        template<> TSIMD_INLINE __m256 reinterpret(const __m256 a){
            return a;
        }
    #endif
    #ifdef __AVX2__
        template<> TSIMD_INLINE __m256 reinterpret(const __m256i a){
            return _mm256_castsi256_ps(a);
        }
        template<> TSIMD_INLINE __m256 reinterpret(const __m256d a){
            return _mm256_castpd_ps(a);
        }
        template<> TSIMD_INLINE __m256i reinterpret(const __m256 a){
            return _mm256_castps_si256(a);
        }
        template<> TSIMD_INLINE __m256i reinterpret(const __m256i a){
            return a;
        }
        template<> TSIMD_INLINE __m256i reinterpret(const __m256d a){
            return _mm256_castpd_si256(a);
        }
        template<> TSIMD_INLINE __m256d reinterpret(const __m256 a){
            return _mm256_castps_pd(a);
        }
        template<> TSIMD_INLINE __m256d reinterpret(const __m256i a){
            return _mm256_castsi256_pd(a);
        }
        template<> TSIMD_INLINE __m256d reinterpret(const __m256d a){
            return a;
        }
    #endif

}

#endif //REINTERPRET_H
