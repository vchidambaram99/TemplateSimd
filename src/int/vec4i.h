#ifndef TSIMD_VEC4I_H
#define TSIMD_VEC4I_H

#include "../../tsimd.h"

#ifdef __SSE2__
namespace TSimd{
    template<> class vec<int,4>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(int a){ data = _mm_set1_epi32(a); }
        TSIMD_INLINE vec(int* a){ data = _mm_loadu_si128((__m128i*)a); }
        TSIMD_INLINE vec(__m128i a){ data = a; }
        TSIMD_INLINE vec(int a, int b, int c, int d){ data = _mm_set_epi32(d,c,b,a); }
        TSIMD_INLINE void store(int* a){ _mm_storeu_si128((__m128i*)a,data); }
        TSIMD_INLINE int& operator[](int idx){ return ((int*)(&data))[idx]; }
        TSIMD_INLINE const int& operator[](int idx) const { return ((int*)(&data))[idx]; }
        TSIMD_INLINE vec<int,4>& operator+=(const vec<int,4>& rhs){
            data = _mm_add_epi32(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int,4>& operator-=(const vec<int,4>& rhs){
            data = _mm_sub_epi32(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int,4>& operator*=(const vec<int,4>& rhs){
            #ifdef __SSE4_1__
                data = _mm_mullo_epi32(data,rhs.data);
                return *this;
            #else
                __m128i a = _mm_mul_epu32(data,rhs.data);
                __m128i b = _mm_mul_epu32(_mm_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),_mm_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
                a = _mm_shuffle_epi32(a,_MM_SHUFFLE(3,2,2,0));
                b = _mm_shuffle_epi32(b,_MM_SHUFFLE(3,2,2,0));
                data = _mm_unpacklo_epi32(a,b);
                return *this;
            #endif
        }
        inline vec<int,4>& operator/=(const vec<int,4>& rhs){ //TODO find simd integer division algorithm
            (*this)[0]/=rhs[0];
            (*this)[1]/=rhs[1];
            (*this)[2]/=rhs[2];
            (*this)[3]/=rhs[3];
            return *this;
        }
        TSIMD_INLINE vec<int,4> operator+(const vec<int,4>& rhs) const {
            return vec<int,4>(_mm_add_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<int,4> operator-(const vec<int,4>& rhs) const {
            return vec<int,4>(_mm_sub_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<int,4> operator*(const vec<int,4>& rhs) const {
            #ifdef __SSE4_1__
                return vec<int,4>(_mm_mullo_epi32(data,rhs.data));
            #else
                __m128i a = _mm_mul_epu32(data,rhs.data);
                __m128i b = _mm_mul_epu32(_mm_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),_mm_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
                a = _mm_shuffle_epi32(a,_MM_SHUFFLE(3,2,2,0));
                b = _mm_shuffle_epi32(b,_MM_SHUFFLE(3,2,2,0));
                return vec<int,4>(_mm_unpacklo_epi32(a,b));
            #endif
        }
        TSIMD_INLINE vec<int,4> operator/(const vec<int,4>& rhs) const { //TODO find simd integer division algorithm
            vec<int,4> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<int,4>& operator&=(const vec<int,4>& rhs){
            data = _mm_and_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int,4>& operator|=(const vec<int,4>& rhs){
            data = _mm_or_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int,4>& operator^=(const vec<int,4>& rhs){
            data = _mm_xor_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int,4> operator&(const vec<int,4>& rhs) const {
            return vec<int,4>(_mm_and_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<int,4> operator|(const vec<int,4>& rhs) const {
            return vec<int,4>(_mm_or_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<int,4> operator^(const vec<int,4>& rhs) const {
            return vec<int,4>(_mm_xor_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<int,4> operator~() const {
            return vec<int,4>(_mm_xor_si128(data,_mm_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<int,4>& operator<<=(const int& shift){
            data = _mm_slli_epi32(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<int,4>& operator>>=(const int& shift){
            data = _mm_srai_epi32(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<int,4> operator<<(const int& shift) const {
            return vec<int,4>(_mm_slli_epi32(data,shift));
        }
        TSIMD_INLINE vec<int,4> operator>>(const int& shift) const {
            return vec<int,4>(_mm_srai_epi32(data,shift));
        }
        __m128i data;
        enum{ size = 4 };
        enum{ bits = 128 };
        friend std::ostream& operator<<(std::ostream& out, vec<int, 4> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC4I_H
