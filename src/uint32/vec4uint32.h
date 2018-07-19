#ifndef TSIMD_VEC4UINT32_H
#define TSIMD_VEC4UINT32_H

#include "../../tsimd.h"

#ifdef __SSE2__
namespace TSimd{
    template<> class vec<uint32_t,4>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(uint32_t a){ data = _mm_set1_epi32(a); }
        TSIMD_INLINE explicit vec(uint32_t* a){ data = _mm_loadu_si128((__m128i*)a); }
        TSIMD_INLINE vec(__m128i a){ data = a; }
        TSIMD_INLINE vec(uint32_t a, uint32_t b, uint32_t c, uint32_t d){ data = _mm_set_epi32(d,c,b,a); }
        TSIMD_INLINE void store(uint32_t* a) const { _mm_storeu_si128((__m128i*)a,data); }
        TSIMD_INLINE intl::AssignmentProxy<uint32_t,4> operator[](const std::size_t idx){ return intl::AssignmentProxy<uint32_t,4>(*this,idx); }
        TSIMD_INLINE vec<uint32_t,4>& operator+=(const vec<uint32_t,4> rhs){
            data = _mm_add_epi32(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint32_t,4>& operator-=(const vec<uint32_t,4> rhs){
            data = _mm_sub_epi32(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint32_t,4>& operator*=(const vec<uint32_t,4> rhs){
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
        inline vec<uint32_t,4>& operator/=(const vec<uint32_t,4> rhs){
            uint32_t a[4];
            uint32_t b[4];
            store(a);
            rhs.store(b);
            a[0]/=b[0];
            a[1]/=b[1];
            a[2]/=b[2];
            a[3]/=b[3];
            data = _mm_loadu_si128((__m128i*)a);
            return *this;
        }
        TSIMD_INLINE vec<uint32_t,4> operator+(const vec<uint32_t,4> rhs) const {
            return vec<uint32_t,4>(_mm_add_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<uint32_t,4> operator-(const vec<uint32_t,4> rhs) const {
            return vec<uint32_t,4>(_mm_sub_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<uint32_t,4> operator*(const vec<uint32_t,4> rhs) const {
            #ifdef __SSE4_1__
                return vec<uint32_t,4>(_mm_mullo_epi32(data,rhs.data));
            #else
                __m128i a = _mm_mul_epu32(data,rhs.data);
                __m128i b = _mm_mul_epu32(_mm_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),_mm_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
                a = _mm_shuffle_epi32(a,_MM_SHUFFLE(3,2,2,0));
                b = _mm_shuffle_epi32(b,_MM_SHUFFLE(3,2,2,0));
                return vec<uint32_t,4>(_mm_unpacklo_epi32(a,b));
            #endif
        }
        TSIMD_INLINE vec<uint32_t,4> operator/(const vec<uint32_t,4> rhs) const {
            vec<uint32_t,4> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<uint32_t, 4>& operator&=(const vec<uint32_t, 4> rhs){
            data = _mm_and_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint32_t, 4>& operator|=(const vec<uint32_t, 4> rhs){
            data = _mm_or_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint32_t, 4>& operator^=(const vec<uint32_t, 4> rhs){
            data = _mm_xor_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint32_t, 4> operator&(const vec<uint32_t, 4> rhs) const {
            return vec<uint32_t, 4>(_mm_and_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<uint32_t, 4> operator|(const vec<uint32_t, 4> rhs) const {
            return vec<uint32_t, 4>(_mm_or_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<uint32_t, 4> operator^(const vec<uint32_t, 4> rhs) const {
            return vec<uint32_t, 4>(_mm_xor_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<uint32_t, 4> operator~() const {
            return vec<uint32_t, 4>(_mm_xor_si128(data,_mm_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<uint32_t,4>& operator<<=(const int shift){
            data = _mm_slli_epi32(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<uint32_t,4>& operator>>=(const int shift){
            data = _mm_srli_epi32(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<uint32_t,4> operator<<(const int shift) const {
            return vec<uint32_t,4>(_mm_slli_epi32(data,shift));
        }
        TSIMD_INLINE vec<uint32_t,4> operator>>(const int shift) const {
            return vec<uint32_t,4>(_mm_srli_epi32(data,shift));
        }
        TSIMD_INLINE vec<uint32_t,4> operator==(const vec<uint32_t,4> a) const {
            return _mm_cmpeq_epi32(data,a.data);
        }
        TSIMD_INLINE vec<uint32_t,4> operator!=(const vec<uint32_t,4> a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE vec<uint32_t,4> operator>(const vec<uint32_t,4> a) const {
            return ~(*this<=a);
        }
        TSIMD_INLINE vec<uint32_t,4> operator>=(const vec<uint32_t,4> a) const {
            #ifdef __SSE4_1__
                return (*this)==_mm_max_epu32(data,a.data);
            #else
                __m128i sgte = _mm_cmpgt_epi32(data,a.data);
                __m128i lz  = _mm_srai_epi32(data,31);
                __m128i lza  = _mm_srai_epi32(a.data,31);
                sgte = _mm_xor_si128(sgte,_mm_xor_si128(lz,lza));
                return _mm_or_si128(sgte,_mm_cmpeq_epi32(data,a.data));
            #endif
        }
        TSIMD_INLINE vec<uint32_t,4> operator<(const vec<uint32_t,4> a) const {
            return a>*this;
        }
        TSIMD_INLINE vec<uint32_t,4> operator<=(const vec<uint32_t,4> a) const {
            #ifdef __SSE4_1__
                return (*this)==_mm_min_epu32(data,a.data);
            #else
                return a>=*this;
            #endif
        }
        __m128i data;
        enum{ size = 4 };
        enum{ bits = 128 };
        friend std::ostream& operator<<(std::ostream& out, vec<uint32_t, 4> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC4UINT32_H
