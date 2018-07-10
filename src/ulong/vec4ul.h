#ifndef TSIMD_VEC4UL_H
#define TSIMD_VEC4UL_H

#include "../../tsimd.h"

#ifdef __AVX2__
namespace TSimd{
    template<> class vec<unsigned long,4>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(unsigned long a){ data = _mm256_set1_epi64x(a); }
        TSIMD_INLINE vec(unsigned long* a){ data = _mm256_loadu_si256((__m256i*)a); }
        TSIMD_INLINE vec(__m256i a){ data = a; }
        TSIMD_INLINE vec(unsigned long a, unsigned long b, unsigned long c, unsigned long d){ data = _mm256_set_epi64x(d,c,b,a); }
        TSIMD_INLINE void store(unsigned long* a){ _mm256_storeu_si256((__m256i*)a,data); }
        TSIMD_INLINE unsigned long& operator[](int idx){ return ((unsigned long*)(&data))[idx]; }
        TSIMD_INLINE const unsigned long& operator[](int idx) const { return ((unsigned long*)(&data))[idx]; }
        TSIMD_INLINE vec<unsigned long,4>& operator+=(const vec<unsigned long,4>& rhs){
            data = _mm256_add_epi64(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned long,4>& operator-=(const vec<unsigned long,4>& rhs){
            data = _mm256_sub_epi64(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned long,4>& operator*=(const vec<unsigned long,4>& rhs){
            __m256i a = _mm256_mul_epu32(data,rhs.data);
            __m256i b = _mm256_mul_epu32(_mm256_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),rhs.data);
            __m256i c = _mm256_mul_epu32(data,_mm256_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
            b = _mm256_slli_epi64(b,32);
            c = _mm256_slli_epi64(c,32);
            data = _mm256_add_epi64(a,_mm256_add_epi64(b,c));
            return *this;
        }
        inline vec<unsigned long,4>& operator/=(const vec<unsigned long,4>& rhs){ //TODO find simd integer division algorithm
            (*this)[0]/=rhs[0];
            (*this)[1]/=rhs[1];
            (*this)[2]/=rhs[2];
            (*this)[3]/=rhs[3];
            return *this;
        }
        TSIMD_INLINE vec<unsigned long,4> operator+(const vec<unsigned long,4>& rhs) const {
            return vec<unsigned long,4>(_mm256_add_epi64(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned long,4> operator-(const vec<unsigned long,4>& rhs) const {
            return vec<unsigned long,4>(_mm256_sub_epi64(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned long,4> operator*(const vec<unsigned long,4>& rhs) const {
            __m256i a = _mm256_mul_epu32(data,rhs.data);
            __m256i b = _mm256_mul_epu32(_mm256_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),rhs.data);
            __m256i c = _mm256_mul_epu32(data,_mm256_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
            b = _mm256_slli_epi64(b,32);
            c = _mm256_slli_epi64(c,32);
            return vec<unsigned long,4>(_mm256_add_epi64(a,_mm256_add_epi64(b,c)));
        }
        TSIMD_INLINE vec<unsigned long,4> operator/(const vec<unsigned long,4>& rhs) const { //TODO find simd integer division algorithm
            vec<unsigned long,4> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<unsigned long,4>& operator&=(const vec<unsigned long,4>& rhs){
            data = _mm256_and_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned long,4>& operator|=(const vec<unsigned long,4>& rhs){
            data = _mm256_or_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned long,4>& operator^=(const vec<unsigned long,4>& rhs){
            data = _mm256_xor_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned long,4> operator&(const vec<unsigned long,4>& rhs) const {
            return vec<unsigned long,4>(_mm256_and_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned long,4> operator|(const vec<unsigned long,4>& rhs) const {
            return vec<unsigned long,4>(_mm256_or_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned long,4> operator^(const vec<unsigned long,4>& rhs) const {
            return vec<unsigned long,4>(_mm256_xor_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned long,4> operator~() const {
            return vec<unsigned long,4>(_mm256_xor_si256(data,_mm256_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<unsigned long,4>& operator<<=(const int& shift){
            data = _mm256_slli_epi64(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<unsigned long,4>& operator>>=(const int& shift){
            data = _mm256_srli_epi64(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<unsigned long,4> operator<<(const int& shift) const {
            return vec<unsigned long,4>(_mm256_slli_epi64(data,shift));
        }
        TSIMD_INLINE vec<unsigned long,4> operator>>(const int& shift) const {
            return vec<unsigned long,4>(_mm256_srli_epi64(data,shift));
        }
        __m256i data;
        enum{ size = 4 };
        enum{ bits = 256 };
        friend std::ostream& operator<<(std::ostream& out, vec<unsigned long,4> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC4UL_H
