#ifndef TSIMD_VEC8INT32_H
#define TSIMD_VEC8INT32_H

#include "../../tsimd.h"

#ifdef __AVX2__
namespace TSimd{
    template<> class vec<int32_t,8>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(int32_t a){ data = _mm256_set1_epi32(a); }
        TSIMD_INLINE explicit vec(int32_t* a){ data = _mm256_loadu_si256((__m256i*)a); }
        TSIMD_INLINE vec(__m256i a){ data = a; }
        TSIMD_INLINE vec(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e, int32_t f, int32_t g, int32_t h){ data = _mm256_set_epi32(h,g,f,e,d,c,b,a); }
        TSIMD_INLINE void store(int32_t* a) const { _mm256_storeu_si256((__m256i*)a,data); }
        TSIMD_INLINE intl::AssignmentProxy<int32_t,8> operator[](const std::size_t idx){ return intl::AssignmentProxy<int32_t,8>(*this,idx); }
        TSIMD_INLINE vec<int32_t,8>& operator+=(const vec<int32_t,8> rhs){
            data = _mm256_add_epi32(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int32_t,8>& operator-=(const vec<int32_t,8> rhs){
            data = _mm256_sub_epi32(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int32_t,8>& operator*=(const vec<int32_t,8> rhs){
            data = _mm256_mullo_epi32(data,rhs.data);
            return *this;
        }
        inline vec<int32_t,8>& operator/=(const vec<int32_t,8> rhs){
            __m256d loa = _mm256_cvtepi32_pd(_mm256_castsi256_si128(data));
            __m256d lob = _mm256_cvtepi32_pd(_mm256_castsi256_si128(rhs.data));
            __m256d hia = _mm256_cvtepi32_pd(_mm256_extractf128_si256(data,1));
            __m256d hib = _mm256_cvtepi32_pd(_mm256_extractf128_si256(rhs.data,1));
            loa = _mm256_div_pd(loa,lob);
            hia = _mm256_div_pd(hia,hib);
            __m128i lo = _mm256_cvttpd_epi32(loa);
            __m128i hi = _mm256_cvttpd_epi32(hia);
            data = _mm256_insertf128_si256(_mm256_castsi128_si256(lo),hi,1);
            return *this;
        }
        TSIMD_INLINE vec<int32_t,8> operator+(const vec<int32_t,8> rhs) const {
            return vec<int32_t,8>(_mm256_add_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<int32_t,8> operator-(const vec<int32_t,8> rhs) const {
            return vec<int32_t,8>(_mm256_sub_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<int32_t,8> operator*(const vec<int32_t,8> rhs) const {
            return vec<int32_t,8>(_mm256_mullo_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<int32_t,8> operator/(const vec<int32_t,8> rhs) const {
            vec<int32_t,8> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<int32_t,8>& operator&=(const vec<int32_t,8> rhs){
            data = _mm256_and_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int32_t,8>& operator|=(const vec<int32_t,8> rhs){
            data = _mm256_or_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int32_t,8>& operator^=(const vec<int32_t,8> rhs){
            data = _mm256_xor_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int32_t,8> operator&(const vec<int32_t,8> rhs) const {
            return vec<int32_t,8>(_mm256_and_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<int32_t,8> operator|(const vec<int32_t,8> rhs) const {
            return vec<int32_t,8>(_mm256_or_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<int32_t,8> operator^(const vec<int32_t,8> rhs) const {
            return vec<int32_t,8>(_mm256_xor_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<int32_t,8> operator~() const {
            return vec<int32_t,8>(_mm256_xor_si256(data,_mm256_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<int32_t,8>& operator<<=(const int shift){
            data = _mm256_slli_epi32(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<int32_t,8>& operator>>=(const int shift){
            data = _mm256_srai_epi32(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<int32_t,8> operator<<(const int shift) const {
            return vec<int32_t,8>(_mm256_slli_epi32(data,shift));
        }
        TSIMD_INLINE vec<int32_t,8> operator>>(const int shift) const {
            return vec<int32_t,8>(_mm256_srai_epi32(data,shift));
        }
        TSIMD_INLINE vec<int32_t,8> operator==(const vec<int32_t,8> a) const {
            return _mm256_cmpeq_epi32(data,a.data);
        }
        TSIMD_INLINE vec<int32_t,8> operator!=(const vec<int32_t,8> a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE vec<int32_t,8> operator>(const vec<int32_t,8> a) const {
            return _mm256_cmpgt_epi32(data,a.data);
        }
        TSIMD_INLINE vec<int32_t,8> operator>=(const vec<int32_t,8> a) const {
            return (*this>a)|(*this==a);
        }
        TSIMD_INLINE vec<int32_t,8> operator<(const vec<int32_t,8> a) const {
            return a>*this;
        }
        TSIMD_INLINE vec<int32_t,8> operator<=(const vec<int32_t,8> a) const {
            return (*this<a)|(*this==a);
        }
        __m256i data;
        enum{ size = 8 };
        enum{ bits = 256 };
        friend std::ostream& operator<<(std::ostream& out, vec<int32_t, 8> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            out<<" "<<v[4]<<" "<<v[5]<<" "<<v[6]<<" "<<v[7];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC8INT32_H
