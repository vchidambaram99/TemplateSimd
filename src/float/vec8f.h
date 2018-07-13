#ifndef TSIMD_VEC8F_H
#define TSIMD_VEC8F_H

#include "../../tsimd.h"

#ifdef __AVX__
namespace TSimd{
    template<> class vec<float,8>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(float a){ data = _mm256_set1_ps(a); }
        TSIMD_INLINE vec(float* a){ data = _mm256_loadu_ps(a); }
        TSIMD_INLINE vec(__m256 a){ data = a; }
        TSIMD_INLINE vec(float a, float b, float c, float d, float e, float f, float g, float h){ data = _mm256_set_ps(h,g,f,e,d,c,b,a); }
        TSIMD_INLINE void store(float* a){ _mm256_storeu_ps(a,data); }
        TSIMD_INLINE float& operator[](std::size_t idx){ return ((float*)(&data))[idx]; }
        TSIMD_INLINE const float& operator[](std::size_t idx) const { return ((float*)(&data))[idx]; }
        TSIMD_INLINE vec<float,8>& operator+=(const vec<float,8>& rhs){
            data = _mm256_add_ps(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<float,8>& operator-=(const vec<float,8>& rhs){
            data = _mm256_sub_ps(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<float,8>& operator*=(const vec<float,8>& rhs){
            data = _mm256_mul_ps(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<float,8>& operator/=(const vec<float,8>& rhs){
            data = _mm256_div_ps(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<float,8> operator+(const vec<float,8>& rhs) const {
            return vec<float,8>(_mm256_add_ps(data,rhs.data));
        }
        TSIMD_INLINE vec<float,8> operator-(const vec<float,8>& rhs) const {
            return vec<float,8>(_mm256_sub_ps(data,rhs.data));
        }
        TSIMD_INLINE vec<float,8> operator*(const vec<float,8>& rhs) const {
            return vec<float,8>(_mm256_mul_ps(data,rhs.data));
        }
        TSIMD_INLINE vec<float,8> operator/(const vec<float,8>& rhs) const {
            return vec<float,8>(_mm256_div_ps(data,rhs.data));
        }
        TSIMD_INLINE vec<float,8>& operator&=(const vec<float,8>& rhs){
            data = _mm256_and_ps(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<float,8>& operator|=(const vec<float,8>& rhs){
            data = _mm256_or_ps(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<float,8>& operator^=(const vec<float,8>& rhs){
            data = _mm256_xor_ps(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<float,8> operator&(const vec<float,8>& rhs) const {
            return vec<float,8>(_mm256_and_ps(data,rhs.data));
        }
        TSIMD_INLINE vec<float,8> operator|(const vec<float,8>& rhs) const {
            return vec<float,8>(_mm256_or_ps(data,rhs.data));
        }
        TSIMD_INLINE vec<float,8> operator^(const vec<float,8>& rhs) const {
            return vec<float,8>(_mm256_xor_ps(data,rhs.data));
        }
        TSIMD_INLINE vec<float,8> operator~() const {
            return vec<float,8>(_mm256_xor_ps(data,_mm256_castsi256_ps(_mm256_set1_epi32(-1))));
        }
        //TODO add macros so that user can decide how fp comparisons should be done (ordered/not) and (signaling/not)
        TSIMD_INLINE vec<float,8> operator==(const vec<float,8>& a) const {
            return _mm256_cmp_ps(data,a.data,_CMP_EQ_OQ);
        }
        TSIMD_INLINE vec<float,8> operator!=(const vec<float,8>& a) const {
            return _mm256_cmp_ps(data,a.data,_CMP_NEQ_OQ);
        }
        TSIMD_INLINE vec<float,8> operator>(const vec<float,8>& a) const {
            return _mm256_cmp_ps(data,a.data,_CMP_GT_OQ);
        }
        TSIMD_INLINE vec<float,8> operator>=(const vec<float,8>& a) const {
            return _mm256_cmp_ps(data,a.data,_CMP_GE_OQ);
        }
        TSIMD_INLINE vec<float,8> operator<(const vec<float,8>& a) const {
            return _mm256_cmp_ps(data,a.data,_CMP_LT_OQ);
        }
        TSIMD_INLINE vec<float,8> operator<=(const vec<float,8>& a) const {
            return _mm256_cmp_ps(data,a.data,_CMP_LE_OQ);
        }
        __m256 data;
        enum{ size = 8 };
        enum{ bits = 256 };
        friend std::ostream& operator<<(std::ostream& out, vec<float,8> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            out<<" "<<v[4]<<" "<<v[5]<<" "<<v[6]<<" "<<v[7];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC8F_H
