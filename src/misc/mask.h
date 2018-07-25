#ifndef TSIMD_MASK_H
#define TSIMD_MASK_H

#include "../../tsimd.h"

namespace TSimd{

    template<int Bits>
    class mask;

    template<>
    class mask<1>{
    public:
        typedef bool simdtype;
        TSIMD_INLINE mask(){}
        TSIMD_INLINE mask(const bool a){
            data = a;
        }
        TSIMD_INLINE mask<1>& operator&=(const mask<1> rhs){
            data &= rhs.data;
            return *this;
        }
        TSIMD_INLINE mask<1>& operator|=(const mask<1> rhs){
            data |= rhs.data;
            return *this;
        }
        TSIMD_INLINE mask<1>& operator^=(const mask<1> rhs){
            data ^= rhs.data;
            return *this;
        }
        TSIMD_INLINE mask<1> operator&(const mask<1> rhs) const {
            return mask<1>(data&rhs.data);
        }
        TSIMD_INLINE mask<1> operator|(const mask<1> rhs) const {
            return mask<1>(data|rhs.data);
        }
        TSIMD_INLINE mask<1> operator^(const mask<1> rhs) const {
            return mask<1>(data&rhs.data);
        }
        TSIMD_INLINE mask<1> operator~() const {
            return mask<1>(!data);
        }
        TSIMD_INLINE mask<1> operator==(const mask<1> a) const {
            return data==a.data;
        }
        TSIMD_INLINE mask<1> operator!=(const mask<1> a) const {
            return data!=a.data;
        }
        TSIMD_INLINE mask<1> operator!() const {
            return !data;
        }
        TSIMD_INLINE bool any() const {
            return data;
        }
        TSIMD_INLINE bool all() const {
            return data;
        }
        template<typename T, int N> vec<T,N> select(const vec<T,N> a, const vec<T,N> b) const {
            return data?a:b;
        }
        template<typename T> operator vec<T,1>() const {
            return data;
        }
        bool data;
        enum{ bits = 1 }; //I don't particularly care if this is wrong
    };

    #ifdef __SSE__
        template<>
        class mask<128>{
        public:
            typedef __m128i simdtype;
            TSIMD_INLINE mask(){}
            template<typename T, int N> TSIMD_INLINE mask(const vec<T,N> a){
                data = reinterpret<__m128i>(a.data);
            }
            TSIMD_INLINE mask(const __m128  a){ data = reinterpret<__m128i>(a); }
            TSIMD_INLINE mask(const __m128i a){ data = a; }
            TSIMD_INLINE mask(const __m128d a){ data = reinterpret<__m128i>(a); }
            TSIMD_INLINE mask<128>& operator&=(const mask<128> rhs){
                data = _mm_and_si128(data,rhs.data);
                return *this;
            }
            TSIMD_INLINE mask<128>& operator|=(const mask<128> rhs){
                data = _mm_or_si128(data,rhs.data);
                return *this;
            }
            TSIMD_INLINE mask<128>& operator^=(const mask<128> rhs){
                data = _mm_xor_si128(data,rhs.data);
                return *this;
            }
            TSIMD_INLINE mask<128> operator&(const mask<128> rhs) const {
                return mask<128>(_mm_and_si128(data,rhs.data));
            }
            TSIMD_INLINE mask<128> operator|(const mask<128> rhs) const {
                return mask<128>(_mm_or_si128(data,rhs.data));
            }
            TSIMD_INLINE mask<128> operator^(const mask<128> rhs) const {
                return mask<128>(_mm_xor_si128(data,rhs.data));
            }
            TSIMD_INLINE mask<128> operator~() const {
                return mask<128>(_mm_xor_si128(data,_mm_set1_epi32(-1)));
            }
            TSIMD_INLINE mask<128> operator==(const mask<128> a) const {
                return ~(*this!=a);
            }
            TSIMD_INLINE mask<128> operator!=(const mask<128> a) const {
                return (*this)^a;
            }
            TSIMD_INLINE mask<128> operator!() const {
                return ~(*this);
            }
            TSIMD_INLINE bool any() const {
                return _mm_movemask_epi8(data);
            }
            TSIMD_INLINE bool all() const {
                return _mm_movemask_epi8(data)==0xFFFF;
            }
            template<typename T, int N> vec<T,N> select(const vec<T,N> a, const vec<T,N> b) const {
                mask<128> a1 = a;
                mask<128> b1 = b;
                #ifdef __SSE4_1__
                    return reinterpret<typename vec<T,N>::simdtype>(_mm_blendv_epi8(a1.data,b1.data,data));
                #else
                    return _mm_or_si128(_mm_and_si128(a1.data,data),_mm_andnot_si128(data,b1.data));
                #endif
            }
            template<typename T, int N> operator vec<T,N>() const {
                return reinterpret<typename vec<T,N>::simdtype>(data);
            }
            __m128i data;
            enum{ bits = 128 };
        };

    #endif

    #ifdef __AVX__
        template<>
        class mask<256>{
        public:
            typedef __m256i simdtype;
            TSIMD_INLINE mask(){}
            template<typename T, int N> TSIMD_INLINE mask(const vec<T,N> a){
                data = reinterpret<__m256i>(a.data);
            }
            TSIMD_INLINE mask(const __m256  a){ data = reinterpret<__m256i>(a); }
            TSIMD_INLINE mask(const __m256i a){ data = a; }
            TSIMD_INLINE mask(const __m256d a){ data = reinterpret<__m256i>(a); }
            TSIMD_INLINE mask<256>& operator&=(const mask<256> rhs){
                data = _mm256_and_si256(data,rhs.data);
                return *this;
            }
            TSIMD_INLINE mask<256>& operator|=(const mask<256> rhs){
                data = _mm256_or_si256(data,rhs.data);
                return *this;
            }
            TSIMD_INLINE mask<256>& operator^=(const mask<256> rhs){
                data = _mm256_xor_si256(data,rhs.data);
                return *this;
            }
            TSIMD_INLINE mask<256> operator&(const mask<256> rhs) const {
                return mask<256>(_mm256_and_si256(data,rhs.data));
            }
            TSIMD_INLINE mask<256> operator|(const mask<256> rhs) const {
                return mask<256>(_mm256_or_si256(data,rhs.data));
            }
            TSIMD_INLINE mask<256> operator^(const mask<256> rhs) const {
                return mask<256>(_mm256_xor_si256(data,rhs.data));
            }
            TSIMD_INLINE mask<256> operator~() const {
                return mask<256>(_mm256_xor_si256(data,_mm256_set1_epi32(-1)));
            }
            TSIMD_INLINE mask<256> operator==(const mask<256> a) const {
                return ~(*this!=a);
            }
            TSIMD_INLINE mask<256> operator!=(const mask<256> a) const {
                return (*this)^a;
            }
            TSIMD_INLINE mask<256> operator!() const {
                return ~(*this);
            }
            TSIMD_INLINE bool any() const {
                #ifdef __AVX2__
                    return _mm256_movemask_epi8(data);
                #else
                    return _mm256_movemask_ps(_mm256_castsi256_ps(data));
                #endif
            }
            TSIMD_INLINE bool all() const {
                #ifdef __AVX2__
                    return _mm256_movemask_epi8(data)==(int)0xFFFFFFFF;
                #else
                    return _mm256_movemask_ps(_mm256_castsi256_ps(data))==0xFF;
                #endif
            }
            template<typename T, int N> vec<T,N> select(const vec<T,N> a, const vec<T,N> b) const {
                mask<256> a1 = a;
                mask<256> b1 = b;
                #ifdef __AVX2__
                    return reinterpret<typename vec<T,N>::simdtype>(_mm256_blendv_epi8(a1.data,b1.data,data));
                #else
                    return _mm256_or_si256(_mm256_and_si256(a1.data,data),_mm256_andnot_si256(data,b1.data));
                #endif
            }
            template<typename T, int N> operator vec<T,N>() const {
                return reinterpret<typename vec<T,N>::simdtype>(data);
            }
            __m256i data;
            enum{ bits = 256 };
        };
    #endif

    template<typename T, int N>
    TSIMD_INLINE vec<T,N> select(const typename vec<T,N>::masktype cond, const vec<T,N> a, const vec<T,N> b){
        return cond.select(a,b);
    }
    template<typename T, typename U, int N>
    TSIMD_INLINE vec<T,N> select(const typename vec<T,N>::masktype cond, const U a, const vec<T,N> b){
        return select<T,N>(cond,a,b);
    }
    template<typename T, typename U, int N>
    TSIMD_INLINE vec<T,N> select(const typename vec<T,N>::masktype cond, const vec<T,N> a, const U b){
        return select<T,N>(cond,a,b);
    }
    template<typename T>
    TSIMD_INLINE vec<T,1> select(const mask<1> cond, const vec<T,1> a, const vec<T,1> b){
        return cond.select(a,b);
    }
}

#endif //TSIMD_MASK_H
