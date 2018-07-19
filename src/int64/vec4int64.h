#ifndef TSIMD_VEC4INT64_H
#define TSIMD_VEC4INT64_H

#include "../../tsimd.h"

#ifdef __AVX2__
namespace TSimd{
    template<> class vec<int64_t,4>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(int64_t a){ data = _mm256_set1_epi64x(a); }
        TSIMD_INLINE explicit vec(int64_t* a){ data = _mm256_loadu_si256((__m256i*)a); }
        TSIMD_INLINE vec(__m256i a){ data = a; }
        TSIMD_INLINE vec(int64_t a, int64_t b, int64_t c, int64_t d){ data = _mm256_set_epi64x(d,c,b,a); }
        TSIMD_INLINE void store(int64_t* a) const { _mm256_storeu_si256((__m256i*)a,data); }
        TSIMD_INLINE intl::AssignmentProxy<int64_t,4> operator[](const std::size_t idx){ return intl::AssignmentProxy<int64_t,4>(*this,idx); }
        TSIMD_INLINE vec<int64_t,4>& operator+=(const vec<int64_t,4>& rhs){
            data = _mm256_add_epi64(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int64_t,4>& operator-=(const vec<int64_t,4>& rhs){
            data = _mm256_sub_epi64(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int64_t,4>& operator*=(const vec<int64_t,4>& rhs){
            __m256i a = _mm256_mul_epu32(data,rhs.data);
            __m256i b = _mm256_mul_epu32(_mm256_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),rhs.data);
            __m256i c = _mm256_mul_epu32(data,_mm256_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
            b = _mm256_slli_epi64(b,32);
            c = _mm256_slli_epi64(c,32);
            data = _mm256_add_epi64(a,_mm256_add_epi64(b,c));
            return *this;
        }
        inline vec<int64_t,4>& operator/=(const vec<int64_t,4>& rhs){
            int64_t a[4];
            int64_t b[4];
            store(a);
            rhs.store(b);
            a[0]/=b[0];
            a[1]/=b[1];
            a[2]/=b[2];
            a[3]/=b[3];
            data = _mm256_loadu_si256((__m256i*)a);
            return *this;
        }
        TSIMD_INLINE vec<int64_t,4> operator+(const vec<int64_t,4>& rhs) const {
            return vec<int64_t,4>(_mm256_add_epi64(data,rhs.data));
        }
        TSIMD_INLINE vec<int64_t,4> operator-(const vec<int64_t,4>& rhs) const {
            return vec<int64_t,4>(_mm256_sub_epi64(data,rhs.data));
        }
        TSIMD_INLINE vec<int64_t,4> operator*(const vec<int64_t,4>& rhs) const {
            __m256i a = _mm256_mul_epu32(data,rhs.data);
            __m256i b = _mm256_mul_epu32(_mm256_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),rhs.data);
            __m256i c = _mm256_mul_epu32(data,_mm256_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
            b = _mm256_slli_epi64(b,32);
            c = _mm256_slli_epi64(c,32);
            return vec<int64_t,4>(_mm256_add_epi64(a,_mm256_add_epi64(b,c)));
        }
        TSIMD_INLINE vec<int64_t,4> operator/(const vec<int64_t,4>& rhs) const {
            vec<int64_t,4> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<int64_t,4>& operator&=(const vec<int64_t,4>& rhs){
            data = _mm256_and_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int64_t,4>& operator|=(const vec<int64_t,4>& rhs){
            data = _mm256_or_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int64_t,4>& operator^=(const vec<int64_t,4>& rhs){
            data = _mm256_xor_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int64_t,4> operator&(const vec<int64_t,4>& rhs) const {
            return vec<int64_t,4>(_mm256_and_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<int64_t,4> operator|(const vec<int64_t,4>& rhs) const {
            return vec<int64_t,4>(_mm256_or_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<int64_t,4> operator^(const vec<int64_t,4>& rhs) const {
            return vec<int64_t,4>(_mm256_xor_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<int64_t,4> operator~() const {
            return vec<int64_t,4>(_mm256_xor_si256(data,_mm256_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<int64_t,4>& operator<<=(const int& shift){
            data = _mm256_slli_epi64(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<int64_t,4>& operator>>=(const int& shift){
            data = _mm256_srai_epi64(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<int64_t,4> operator<<(const int& shift) const {
            return vec<int64_t,4>(_mm256_slli_epi64(data,shift));
        }
        TSIMD_INLINE vec<int64_t,4> operator>>(const int& shift) const {
            return vec<int64_t,4>(_mm256_srai_epi64(data,shift));
        }
        TSIMD_INLINE vec<int64_t,4> operator==(const vec<int64_t,4>& a) const {
            return _mm256_cmpeq_epi64(data,a.data);
        }
        TSIMD_INLINE vec<int64_t,4> operator!=(const vec<int64_t,4>& a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE vec<int64_t,4> operator>(const vec<int64_t,4>& a) const {
            return _mm256_cmpgt_epi64(data,a.data);
        }
        TSIMD_INLINE vec<int64_t,4> operator>=(const vec<int64_t,4>& a) const {
            return (*this>a)|(*this==a);
        }
        TSIMD_INLINE vec<int64_t,4> operator<(const vec<int64_t,4>& a) const {
            return a>*this;
        }
        TSIMD_INLINE vec<int64_t,4> operator<=(const vec<int64_t,4>& a) const {
            return (*this<a)|(*this==a);
        }
        __m256i data;
        enum{ size = 4 };
        enum{ bits = 256 };
        friend std::ostream& operator<<(std::ostream& out, vec<int64_t,4> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC4INT64_H
