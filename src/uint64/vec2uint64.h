#ifndef TSIMD_VEC2UINT64_H
#define TSIMD_VEC2UINT64_H

#include "../../tsimd.h"

#ifdef __SSE2__
namespace TSimd{
    template<> class vec<uint64_t,2>{
    public:
        typedef mask<128> masktype;
        typedef __m128i simdtype;
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(uint64_t a){ data = _mm_set1_epi64x(a); }
        TSIMD_INLINE explicit vec(uint64_t* a){ data = _mm_loadu_si128((__m128i*)a); }
        TSIMD_INLINE vec(__m128i a){ data = a; }
        TSIMD_INLINE vec(uint64_t a, uint64_t b){ data = _mm_set_epi64x(b,a); }
        TSIMD_INLINE void store(uint64_t* a) const { _mm_storeu_si128((__m128i*)a,data); }
        TSIMD_INLINE intl::ConstProxy<uint64_t,2> operator[](const std::size_t idx) const { return intl::ConstProxy<uint64_t,2>(*this,idx); }
        TSIMD_INLINE intl::AssignmentProxy<uint64_t,2> operator[](const std::size_t idx){ return intl::AssignmentProxy<uint64_t,2>(*this,idx); }
        TSIMD_INLINE static vec<uint64_t,2> zero(){ return _mm_setzero_si128(); }
        TSIMD_INLINE vec<uint64_t,2>& operator+=(const vec<uint64_t,2> rhs){
            data = _mm_add_epi64(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint64_t,2>& operator-=(const vec<uint64_t,2> rhs){
            data = _mm_sub_epi64(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint64_t,2>& operator*=(const vec<uint64_t,2> rhs){
            __m128i a = _mm_mul_epu32(data,rhs.data);
            __m128i b = _mm_mul_epu32(_mm_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),rhs.data);
            __m128i c = _mm_mul_epu32(data,_mm_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
            b = _mm_slli_epi64(b,32);
            c = _mm_slli_epi64(c,32);
            data = _mm_add_epi64(a,_mm_add_epi64(b,c));
            return *this;
        }
        inline vec<uint64_t,2>& operator/=(const vec<uint64_t,2> rhs){
            uint64_t a[2];
            uint64_t b[2];
            store(a);
            rhs.store(b);
            a[0]/=b[0];
            a[1]/=b[1];
            data = _mm_loadu_si128((__m128i*)a);
            return *this;
        }
        TSIMD_INLINE vec<uint64_t,2> operator+(const vec<uint64_t,2> rhs) const {
            return vec<uint64_t,2>(_mm_add_epi64(data,rhs.data));
        }
        TSIMD_INLINE vec<uint64_t,2> operator-(const vec<uint64_t,2> rhs) const {
            return vec<uint64_t,2>(_mm_sub_epi64(data,rhs.data));
        }
        TSIMD_INLINE vec<uint64_t,2> operator*(const vec<uint64_t,2> rhs) const {
            __m128i a = _mm_mul_epu32(data,rhs.data);
            __m128i b = _mm_mul_epu32(_mm_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),rhs.data);
            __m128i c = _mm_mul_epu32(data,_mm_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
            b = _mm_slli_epi64(b,32);
            c = _mm_slli_epi64(c,32);
            return vec<uint64_t,2>(_mm_add_epi64(a,_mm_add_epi64(b,c)));
        }
        TSIMD_INLINE vec<uint64_t,2> operator/(const vec<uint64_t,2> rhs) const {
            vec<uint64_t,2> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<uint64_t,2> operator-() const {
            return zero()-*this;
        }
        TSIMD_INLINE vec<uint64_t,2>& operator&=(const vec<uint64_t,2> rhs){
            data = _mm_and_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint64_t,2>& operator|=(const vec<uint64_t,2> rhs){
            data = _mm_or_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint64_t,2>& operator^=(const vec<uint64_t,2> rhs){
            data = _mm_xor_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint64_t,2> operator&(const vec<uint64_t,2> rhs) const {
            return vec<uint64_t,2>(_mm_and_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<uint64_t,2> operator|(const vec<uint64_t,2> rhs) const {
            return vec<uint64_t,2>(_mm_or_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<uint64_t,2> operator^(const vec<uint64_t,2> rhs) const {
            return vec<uint64_t,2>(_mm_xor_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<uint64_t,2> operator~() const {
            return vec<uint64_t,2>(_mm_xor_si128(data,_mm_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<uint64_t,2>& operator<<=(const int shift){
            data = _mm_slli_epi64(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<uint64_t,2>& operator>>=(const int shift){
            data = _mm_srli_epi64(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<uint64_t,2> operator<<(const int shift) const {
            return vec<uint64_t,2>(_mm_slli_epi64(data,shift));
        }
        TSIMD_INLINE vec<uint64_t,2> operator>>(const int shift) const {
            return vec<uint64_t,2>(_mm_srli_epi64(data,shift));
        }
        TSIMD_INLINE masktype operator==(const vec<uint64_t,2> a) const {
            #ifdef __SSE4_1__
                return _mm_cmpeq_epi64(data,a.data);
            #else
                __m128i b = _mm_cmpeq_epi32(data,a.data);
                return _mm_and_si128(b,_mm_shuffle_epi32(b,_MM_SHUFFLE(2,3,0,1)));
            #endif
        }
        TSIMD_INLINE masktype operator!=(const vec<uint64_t,2> a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE masktype operator>(const vec<uint64_t,2> a) const {
            return ~(*this<=a);
        }
        TSIMD_INLINE masktype operator>=(const vec<uint64_t,2> a) const {
            vec<uint64_t,2> b;
            b[0] = (*this)[0]>=a[0];
            b[1] = (*this)[1]>=a[1];
            return ~b+1;
        }
        TSIMD_INLINE masktype operator<(const vec<uint64_t,2> a) const {
            return a>*this;
        }
        TSIMD_INLINE masktype operator<=(const vec<uint64_t,2> a) const {
            return a>=*this;
        }
        TSIMD_INLINE masktype operator!() const {
            return (*this)==0;
        }
        TSIMD_INLINE bool any() const {
            return (*this!=0).any();
        }
        TSIMD_INLINE bool all() const {
            return (*this!=0).all();
        }
        TSIMD_INLINE vec<uint64_t,2> max(const vec<uint64_t,2> rhs) const {
            return select(*this>rhs,*this,rhs);
        }
        TSIMD_INLINE vec<uint64_t,2> min(const vec<uint64_t,2> rhs) const {
            return select(*this<rhs,*this,rhs);
        }
        __m128i data;
        enum{ size = 2 };
        enum{ bits = 128 };
        friend std::ostream& operator<<(std::ostream& out, vec<uint64_t,2> v){
            out<<v[0]<<" "<<v[1];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC2UINT64_H
