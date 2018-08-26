#ifndef TSIMD_MASK_H
#define TSIMD_MASK_H

#include "../../tsimd.h"

namespace tsimd{

    //TODO: add proxies, operator[]s, maybe some integration with vector<bool>
    //TODO: fix masktype typedefs in tsimd classes

    template<int Bits, int Elements>
    class mask;

    #ifdef __SSE__
        template<int Elements>
        class mask<128, Elements>{
        public:
            typedef __m128i simdtype;
            TSIMD_INLINE mask(){}
            template<typename T, int N> TSIMD_INLINE mask(const vec<T,N> a){
                data = reinterpret<__m128i>(a.data);
            }
            TSIMD_INLINE mask(const __m128  a){ data = reinterpret<__m128i>(a); }
            TSIMD_INLINE mask(const __m128i a){ data = a; }
            TSIMD_INLINE mask(const __m128d a){ data = reinterpret<__m128i>(a); }
            TSIMD_INLINE mask<128,Elements>& operator&=(const mask<128,Elements> rhs){
                data = _mm_and_si128(data,rhs.data);
                return *this;
            }
            TSIMD_INLINE mask<128,Elements>& operator|=(const mask<128,Elements> rhs){
                data = _mm_or_si128(data,rhs.data);
                return *this;
            }
            TSIMD_INLINE mask<128,Elements>& operator^=(const mask<128,Elements> rhs){
                data = _mm_xor_si128(data,rhs.data);
                return *this;
            }
            TSIMD_INLINE mask<128,Elements> operator&(const mask<128,Elements> rhs) const {
                return mask<128,Elements>(_mm_and_si128(data,rhs.data));
            }
            TSIMD_INLINE mask<128,Elements> operator|(const mask<128,Elements> rhs) const {
                return mask<128,Elements>(_mm_or_si128(data,rhs.data));
            }
            TSIMD_INLINE mask<128,Elements> operator^(const mask<128,Elements> rhs) const {
                return mask<128,Elements>(_mm_xor_si128(data,rhs.data));
            }
            TSIMD_INLINE mask<128,Elements> operator~() const {
                return mask<128,Elements>(_mm_xor_si128(data,_mm_set1_epi32(-1)));
            }
            TSIMD_INLINE mask<128,Elements> operator==(const mask<128,Elements> a) const {
                return ~(*this!=a);
            }
            TSIMD_INLINE mask<128,Elements> operator!=(const mask<128,Elements> a) const {
                return (*this)^a;
            }
            TSIMD_INLINE mask<128,Elements> operator!() const {
                return ~(*this);
            }
            TSIMD_INLINE bool any() const {
                return _mm_movemask_epi8(data);
            }
            TSIMD_INLINE bool all() const {
                return _mm_movemask_epi8(data)==0xFFFF;
            }
            template<typename T, int N> vec<T,N> select(const vec<T,N> a, const vec<T,N> b) const {
                mask<128,Elements> a1 = a;
                mask<128,Elements> b1 = b;
                #ifdef __SSE4_1__
                    return reinterpret<typename vec<T,N>::simdtype>(_mm_blendv_epi8(a1.data,b1.data,data));
                #else
                    return _mm_or_si128(_mm_and_si128(a1.data,data),_mm_andnot_si128(data,b1.data));
                #endif
            }
            template<typename T, int N> operator vec<T,N>() const {
                return reinterpret<typename vec<T,N>::simdtype>(data);
            }
            template<int E2> operator mask<128,E2>() const {
                return mask<128,E2>(data);
            }
            __m128i data;
            enum{ bits = 128 };
            enum{ size = Elements };
        };

    #endif

    #ifdef __AVX__
        template<int Elements>
        class mask<256, Elements>{
        public:
            typedef __m256i simdtype;
            TSIMD_INLINE mask(){}
            template<typename T, int N> TSIMD_INLINE mask(const vec<T,N> a){
                data = reinterpret<__m256i>(a.data);
            }
            TSIMD_INLINE mask(const __m256  a){ data = reinterpret<__m256i>(a); }
            TSIMD_INLINE mask(const __m256i a){ data = a; }
            TSIMD_INLINE mask(const __m256d a){ data = reinterpret<__m256i>(a); }
            TSIMD_INLINE mask<256,Elements>& operator&=(const mask<256,Elements> rhs){
                data = _mm256_and_si256(data,rhs.data);
                return *this;
            }
            TSIMD_INLINE mask<256,Elements>& operator|=(const mask<256,Elements> rhs){
                data = _mm256_or_si256(data,rhs.data);
                return *this;
            }
            TSIMD_INLINE mask<256,Elements>& operator^=(const mask<256,Elements> rhs){
                data = _mm256_xor_si256(data,rhs.data);
                return *this;
            }
            TSIMD_INLINE mask<256,Elements> operator&(const mask<256,Elements> rhs) const {
                return mask<256,Elements>(_mm256_and_si256(data,rhs.data));
            }
            TSIMD_INLINE mask<256,Elements> operator|(const mask<256,Elements> rhs) const {
                return mask<256,Elements>(_mm256_or_si256(data,rhs.data));
            }
            TSIMD_INLINE mask<256,Elements> operator^(const mask<256,Elements> rhs) const {
                return mask<256,Elements>(_mm256_xor_si256(data,rhs.data));
            }
            TSIMD_INLINE mask<256,Elements> operator~() const {
                return mask<256,Elements>(_mm256_xor_si256(data,_mm256_set1_epi32(-1)));
            }
            TSIMD_INLINE mask<256,Elements> operator==(const mask<256,Elements> a) const {
                return ~(*this!=a);
            }
            TSIMD_INLINE mask<256,Elements> operator!=(const mask<256,Elements> a) const {
                return (*this)^a;
            }
            TSIMD_INLINE mask<256,Elements> operator!() const {
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
                mask<256,Elements> a1 = a;
                mask<256,Elements> b1 = b;
                #ifdef __AVX2__
                    return reinterpret<typename vec<T,N>::simdtype>(_mm256_blendv_epi8(a1.data,b1.data,data));
                #else
                    return _mm256_or_si256(_mm256_and_si256(a1.data,data),_mm256_andnot_si256(data,b1.data));
                #endif
            }
            template<typename T, int N> operator vec<T,N>() const {
                return reinterpret<typename vec<T,N>::simdtype>(data);
            }
            template<int E2> operator mask<256,E2>() const {
                return mask<256,E2>(data);
            }
            __m256i data;
            enum{ bits = 256 };
            enum{ size = Elements };
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
}

#endif //TSIMD_MASK_H
