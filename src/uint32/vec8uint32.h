#ifndef TSIMD_VEC8UINT32_H
#define TSIMD_VEC8UINT32_H

#include "../../tsimd.h"

#ifdef __AVX2__
namespace TSimd{
    template<> class vec<uint32_t,8>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(uint32_t a){ data = _mm256_set1_epi32(a); }
        TSIMD_INLINE explicit vec(uint32_t* a){ data = _mm256_loadu_si256((__m256i*)a); }
        TSIMD_INLINE vec(__m256i a){ data = a; }
        TSIMD_INLINE vec(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f, uint32_t g, uint32_t h){ data = _mm256_set_epi32(h,g,f,e,d,c,b,a); }
        TSIMD_INLINE void store(uint32_t* a) const { _mm256_storeu_si256((__m256i*)a,data); }
        TSIMD_INLINE intl::AssignmentProxy<uint32_t,8> operator[](const std::size_t idx){ return intl::AssignmentProxy<uint32_t,8>(*this,idx); }
        TSIMD_INLINE vec<uint32_t,8>& operator+=(const vec<uint32_t,8> rhs){
            data = _mm256_add_epi32(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint32_t,8>& operator-=(const vec<uint32_t,8> rhs){
            data = _mm256_sub_epi32(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint32_t,8>& operator*=(const vec<uint32_t,8> rhs){
            data = _mm256_mullo_epi32(data,rhs.data);
            return *this;
        }
        inline vec<uint32_t,8>& operator/=(const vec<uint32_t,8> rhs){
            uint32_t a[8];
            uint32_t b[8];
            store(a);
            rhs.store(b);
            a[0]/=b[0];
            a[1]/=b[1];
            a[2]/=b[2];
            a[3]/=b[3];
            a[4]/=b[4];
            a[5]/=b[5];
            a[6]/=b[6];
            a[7]/=b[7];
            data = _mm256_loadu_si256((__m256i*)a);
            return *this;
        }
        TSIMD_INLINE vec<uint32_t,8> operator+(const vec<uint32_t,8> rhs) const {
            return vec<uint32_t,8>(_mm256_add_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<uint32_t,8> operator-(const vec<uint32_t,8> rhs) const {
            return vec<uint32_t,8>(_mm256_sub_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<uint32_t,8> operator*(const vec<uint32_t,8> rhs) const {
            return vec<uint32_t,8>(_mm256_mullo_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<uint32_t,8> operator/(const vec<uint32_t,8> rhs) const {
            vec<uint32_t,8> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<uint32_t,8> operator&=(const vec<uint32_t,8> rhs){
            data = _mm256_and_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint32_t,8> operator|=(const vec<uint32_t,8> rhs){
            data = _mm256_or_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint32_t,8> operator^=(const vec<uint32_t,8> rhs){
            data = _mm256_xor_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint32_t,8> operator&(const vec<uint32_t,8> rhs) const {
            return vec<uint32_t,8>(_mm256_and_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<uint32_t,8> operator|(const vec<uint32_t,8> rhs) const {
            return vec<uint32_t,8>(_mm256_or_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<uint32_t,8> operator^(const vec<uint32_t,8> rhs) const {
            return vec<uint32_t,8>(_mm256_xor_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<uint32_t,8> operator~() const {
            return vec<uint32_t,8>(_mm256_xor_si256(data,_mm256_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<uint32_t,8>& operator<<=(const int shift){
            data = _mm256_slli_epi32(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<uint32_t,8>& operator>>=(const int shift){
            data = _mm256_srli_epi32(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<uint32_t,8> operator<<(const int shift) const {
            return vec<uint32_t,8>(_mm256_slli_epi32(data,shift));
        }
        TSIMD_INLINE vec<uint32_t,8> operator>>(const int shift) const {
            return vec<uint32_t,8>(_mm256_srli_epi32(data,shift));
        }
        TSIMD_INLINE vec<uint32_t,8> operator==(const vec<uint32_t,8> a) const {
            return _mm256_cmpeq_epi32(data,a.data);
        }
        TSIMD_INLINE vec<uint32_t,8> operator!=(const vec<uint32_t,8> a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE vec<uint32_t,8> operator>(const vec<uint32_t,8> a) const {
            return ~(*this<=a);
        }
        TSIMD_INLINE vec<uint32_t,8> operator>=(const vec<uint32_t,8> a) const {
            return (*this)==_mm256_max_epu32(data,a.data);
        }
        TSIMD_INLINE vec<uint32_t,8> operator<(const vec<uint32_t,8> a) const {
            return a>*this;
        }
        TSIMD_INLINE vec<uint32_t,8> operator<=(const vec<uint32_t,8> a) const {
            return (*this)==_mm256_min_epu32(data,a.data);
        }
        __m256i data;
        enum{ size = 8 };
        enum{ bits = 256 };
        friend std::ostream& operator<<(std::ostream& out, vec<uint32_t,8> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            out<<" "<<v[4]<<" "<<v[5]<<" "<<v[6]<<" "<<v[7];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC8UINT32_H
