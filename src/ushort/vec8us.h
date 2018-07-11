#ifndef TSIMD_VEC8US_H
#define TSIMD_VEC8US_H

#include "../../tsimd.h"

#ifdef __SSE2__
namespace TSimd{
    template<> class vec<unsigned short,8>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(unsigned short a){ data = _mm_set1_epi16(a); }
        TSIMD_INLINE vec(unsigned short* a){ data = _mm_loadu_si128((__m128i*)a); }
        TSIMD_INLINE vec(__m128i a){ data = a; }
        TSIMD_INLINE vec(unsigned short a, unsigned short b, unsigned short c, unsigned short d, unsigned short e, unsigned short f, unsigned short g, unsigned short h){
            data = _mm_set_epi16(h,g,f,e,d,c,b,a);
        }
        TSIMD_INLINE void store(unsigned short* a){ _mm_storeu_si128((__m128i*)a,data); }
        TSIMD_INLINE unsigned short& operator[](int idx){ return ((unsigned short*)(&data))[idx]; }
        TSIMD_INLINE const unsigned short& operator[](int idx) const { return ((unsigned short*)(&data))[idx]; }
        TSIMD_INLINE vec<unsigned short,8>& operator+=(const vec<unsigned short,8>& rhs){
            data = _mm_add_epi16(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned short,8>& operator-=(const vec<unsigned short,8>& rhs){
            data = _mm_sub_epi16(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned short,8>& operator*=(const vec<unsigned short,8>& rhs){
            data = _mm_mullo_epi16(data,rhs.data);
            return *this;
        }
        inline vec<unsigned short,8>& operator/=(const vec<unsigned short,8>& rhs){ //TODO find simd integer division algorithm
            (*this)[0]/=rhs[0];
            (*this)[1]/=rhs[1];
            (*this)[2]/=rhs[2];
            (*this)[3]/=rhs[3];
            (*this)[4]/=rhs[4];
            (*this)[5]/=rhs[5];
            (*this)[6]/=rhs[6];
            (*this)[7]/=rhs[7];
            return *this;
        }
        TSIMD_INLINE vec<unsigned short,8> operator+(const vec<unsigned short,8>& rhs) const {
            return vec<unsigned short,8>(_mm_add_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned short,8> operator-(const vec<unsigned short,8>& rhs) const {
            return vec<unsigned short,8>(_mm_sub_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned short,8> operator*(const vec<unsigned short,8>& rhs) const {
            return vec<unsigned short,8>(_mm_mullo_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned short,8> operator/(const vec<unsigned short,8>& rhs) const { //TODO find simd integer division algorithm
            vec<unsigned short,8> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<unsigned short,8>& operator&=(const vec<unsigned short,8>& rhs){
            data = _mm_and_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned short,8>& operator|=(const vec<unsigned short,8>& rhs){
            data = _mm_or_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned short,8>& operator^=(const vec<unsigned short,8>& rhs){
            data = _mm_xor_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned short,8> operator&(const vec<unsigned short,8>& rhs) const {
            return vec<unsigned short,8>(_mm_and_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned short,8> operator|(const vec<unsigned short,8>& rhs) const {
            return vec<unsigned short,8>(_mm_or_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned short,8> operator^(const vec<unsigned short,8>& rhs) const {
            return vec<unsigned short,8>(_mm_xor_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned short,8> operator~() const {
            return vec<unsigned short,8>(_mm_xor_si128(data,_mm_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<unsigned short,8>& operator<<=(const int& shift){
            data = _mm_slli_epi16(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<unsigned short,8>& operator>>=(const int& shift){
            data = _mm_srli_epi16(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<unsigned short,8> operator<<(const int& shift) const {
            return vec<unsigned short,8>(_mm_slli_epi16(data,shift));
        }
        TSIMD_INLINE vec<unsigned short,8> operator>>(const int& shift) const {
            return vec<unsigned short,8>(_mm_srli_epi16(data,shift));
        }
        TSIMD_INLINE vec<unsigned short,8> operator==(const vec<unsigned short,8>& a) const {
            return _mm_cmpeq_epi16(data,a.data);
        }
        TSIMD_INLINE vec<unsigned short,8> operator!=(const vec<unsigned short,8>& a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE vec<unsigned short,8> operator>(const vec<unsigned short,8>& a) const {
            return ~(*this<=a);
        }
        TSIMD_INLINE vec<unsigned short,8> operator>=(const vec<unsigned short,8>& a) const {
            #ifdef __SSE4_1__
                return (*this)==_mm_max_epu16(data,a.data);
            #else //TODO think of something better
                vec<unsigned short,8> b;
                b[0] = (*this)[0]>=a[0];
                b[1] = (*this)[1]>=a[1];
                b[2] = (*this)[2]>=a[2];
                b[3] = (*this)[3]>=a[3];
                b[4] = (*this)[4]>=a[4];
                b[5] = (*this)[5]>=a[5];
                b[6] = (*this)[6]>=a[6];
                b[7] = (*this)[7]>=a[7];
                return ~b+1;
            #endif
        }
        TSIMD_INLINE vec<unsigned short,8> operator<(const vec<unsigned short,8>& a) const {
            return a>*this;
        }
        TSIMD_INLINE vec<unsigned short,8> operator<=(const vec<unsigned short,8>& a) const {
            #ifdef __SSE4_1__
                return (*this)==_mm_min_epu16(data,a.data);
            #else
                return a>=*this;
            #endif
        }
        __m128i data;
        enum{ size = 8 };
        enum{ bits = 128 };
        friend std::ostream& operator<<(std::ostream& out, vec<unsigned short,8> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            out<<" "<<v[4]<<" "<<v[5]<<" "<<v[6]<<" "<<v[7];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC8US_H
