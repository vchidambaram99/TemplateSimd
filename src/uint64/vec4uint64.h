#ifndef TSIMD_VEC4UINT64_H
#define TSIMD_VEC4UINT64_H

#include "../../tsimd.h"

#ifdef __AVX2__
namespace tsimd{
    template<> class vec<uint64_t,4>{
    public:
        typedef mask<256,4> masktype;
        typedef __m256i simdtype;
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(uint64_t a){ data = _mm256_set1_epi64x(a); }
        TSIMD_INLINE explicit vec(uint64_t* a){ data = _mm256_loadu_si256((__m256i*)a); }
        TSIMD_INLINE vec(__m256i a){ data = a; }
        TSIMD_INLINE vec(uint64_t a, uint64_t b, uint64_t c, uint64_t d){ data = _mm256_set_epi64x(d,c,b,a); }
        TSIMD_INLINE void store(uint64_t* a) const { _mm256_storeu_si256((__m256i*)a,data); }
        TSIMD_INLINE intl::ConstProxy<uint64_t,4> operator[](const std::size_t idx) const { return intl::ConstProxy<uint64_t,4>(*this,idx); }
        TSIMD_INLINE intl::AssignmentProxy<uint64_t,4> operator[](const std::size_t idx){ return intl::AssignmentProxy<uint64_t,4>(*this,idx); }
        TSIMD_INLINE static vec<uint64_t,4> zero(){ return _mm256_setzero_si256(); }
        TSIMD_INLINE vec<uint64_t,4>& operator+=(const vec<uint64_t,4> rhs){
            data = _mm256_add_epi64(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint64_t,4>& operator-=(const vec<uint64_t,4> rhs){
            data = _mm256_sub_epi64(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint64_t,4>& operator*=(const vec<uint64_t,4> rhs){
            __m256i a = _mm256_mul_epu32(data,rhs.data);
            __m256i b = _mm256_mul_epu32(_mm256_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),rhs.data);
            __m256i c = _mm256_mul_epu32(data,_mm256_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
            b = _mm256_slli_epi64(b,32);
            c = _mm256_slli_epi64(c,32);
            data = _mm256_add_epi64(a,_mm256_add_epi64(b,c));
            return *this;
        }
        inline vec<uint64_t,4>& operator/=(const vec<uint64_t,4> rhs){
            uint64_t a[4];
            uint64_t b[4];
            store(a);
            rhs.store(b);
            a[0]/=b[0];
            a[1]/=b[1];
            a[2]/=b[2];
            a[3]/=b[3];
            data = _mm256_loadu_si256((__m256i*)a);
            return *this;
        }
        TSIMD_INLINE vec<uint64_t,4> operator+(const vec<uint64_t,4> rhs) const {
            return vec<uint64_t,4>(_mm256_add_epi64(data,rhs.data));
        }
        TSIMD_INLINE vec<uint64_t,4> operator-(const vec<uint64_t,4> rhs) const {
            return vec<uint64_t,4>(_mm256_sub_epi64(data,rhs.data));
        }
        TSIMD_INLINE vec<uint64_t,4> operator*(const vec<uint64_t,4> rhs) const {
            __m256i a = _mm256_mul_epu32(data,rhs.data);
            __m256i b = _mm256_mul_epu32(_mm256_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),rhs.data);
            __m256i c = _mm256_mul_epu32(data,_mm256_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
            b = _mm256_slli_epi64(b,32);
            c = _mm256_slli_epi64(c,32);
            return vec<uint64_t,4>(_mm256_add_epi64(a,_mm256_add_epi64(b,c)));
        }
        TSIMD_INLINE vec<uint64_t,4> operator/(const vec<uint64_t,4> rhs) const {
            vec<uint64_t,4> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<uint64_t,4> operator-() const {
            return zero()-*this;
        }
        TSIMD_INLINE vec<uint64_t,4>& operator&=(const vec<uint64_t,4> rhs){
            data = _mm256_and_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint64_t,4>& operator|=(const vec<uint64_t,4> rhs){
            data = _mm256_or_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint64_t,4>& operator^=(const vec<uint64_t,4> rhs){
            data = _mm256_xor_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint64_t,4> operator&(const vec<uint64_t,4> rhs) const {
            return vec<uint64_t,4>(_mm256_and_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<uint64_t,4> operator|(const vec<uint64_t,4> rhs) const {
            return vec<uint64_t,4>(_mm256_or_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<uint64_t,4> operator^(const vec<uint64_t,4> rhs) const {
            return vec<uint64_t,4>(_mm256_xor_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<uint64_t,4> operator~() const {
            return vec<uint64_t,4>(_mm256_xor_si256(data,_mm256_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<uint64_t,4>& operator<<=(const int shift){
            data = _mm256_slli_epi64(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<uint64_t,4>& operator>>=(const int shift){
            data = _mm256_srli_epi64(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<uint64_t,4> operator<<(const int shift) const {
            return vec<uint64_t,4>(_mm256_slli_epi64(data,shift));
        }
        TSIMD_INLINE vec<uint64_t,4> operator>>(const int shift) const {
            return vec<uint64_t,4>(_mm256_srli_epi64(data,shift));
        }
        TSIMD_INLINE masktype operator==(const vec<uint64_t,4> a) const {
            return _mm256_cmpeq_epi64(data,a.data);
        }
        TSIMD_INLINE masktype operator!=(const vec<uint64_t,4> a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE masktype operator>(const vec<uint64_t,4> a) const {
            return ~(*this<=a);
        }
        TSIMD_INLINE masktype operator>=(const vec<uint64_t,4> a) const {
            vec<uint64_t,4> b;
            b[0] = (*this)[0] >= a[0];
            b[1] = (*this)[1] >= a[1];
            b[2] = (*this)[2] >= a[2];
            b[3] = (*this)[3] >= a[3];
            return masktype(~b+1);
        }
        TSIMD_INLINE masktype operator<(const vec<uint64_t,4> a) const {
            return a>*this;
        }
        TSIMD_INLINE masktype operator<=(const vec<uint64_t,4> a) const {
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
        TSIMD_INLINE vec<uint64_t,4> max(const vec<uint64_t,4> rhs) const {
            return select(*this>rhs,*this,rhs);
        }
        TSIMD_INLINE vec<uint64_t,4> min(const vec<uint64_t,4> rhs) const {
            return select(*this<rhs,*this,rhs);
        }
        __m256i data;
        enum{ size = 4 };
        enum{ bits = 256 };
        friend std::ostream& operator<<(std::ostream& out, vec<uint64_t,4> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC4UINT64_H
