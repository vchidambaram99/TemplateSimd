#ifndef TSIMD_VEC4D_H
#define TSIMD_VEC4D_H

#include "../../tsimd.h"

#ifdef __AVX__
namespace TSimd{
    template<> class vec<double,4>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(double a){ data = _mm256_set1_pd(a); }
        TSIMD_INLINE vec(double* a){ data = _mm256_loadu_pd(a); }
        TSIMD_INLINE vec(__m256d a){ data = a; }
        TSIMD_INLINE vec(double a, double b, double c, double d){ data = _mm256_set_pd(d,c,b,a); }
        TSIMD_INLINE void store(double* a){ _mm256_storeu_pd(a,data); }
        TSIMD_INLINE double& operator[](int idx){ return ((double*)(&data))[idx]; }
        TSIMD_INLINE const double& operator[](int idx) const { return ((double*)(&data))[idx]; }
        TSIMD_INLINE vec<double,4>& operator+=(const vec<double,4>& rhs){
            data = _mm256_add_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,4>& operator-=(const vec<double,4>& rhs){
            data = _mm256_sub_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,4>& operator*=(const vec<double,4>& rhs){
            data = _mm256_mul_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,4>& operator/=(const vec<double,4>& rhs){
            data = _mm256_div_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,4> operator+(const vec<double,4>& rhs) const {
            return vec<double,4>(_mm256_add_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,4> operator-(const vec<double,4>& rhs) const {
            return vec<double,4>(_mm256_sub_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,4> operator*(const vec<double,4>& rhs) const {
            return vec<double,4>(_mm256_mul_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,4> operator/(const vec<double,4>& rhs) const {
            return vec<double,4>(_mm256_div_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,4>& operator&=(const vec<double,4>& rhs){
            data = _mm256_and_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,4>& operator|=(const vec<double,4>& rhs){
            data = _mm256_or_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,4>& operator^=(const vec<double,4>& rhs){
            data = _mm256_xor_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,4> operator&(const vec<double,4>& rhs) const {
            return vec<double,4>(_mm256_and_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,4> operator|(const vec<double,4>& rhs) const {
            return vec<double,4>(_mm256_or_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,4> operator^(const vec<double,4>& rhs) const {
            return vec<double,4>(_mm256_xor_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,4> operator~() const {
            return vec<double,4>(_mm256_xor_pd(data,_mm256_castsi256_pd(_mm256_set1_epi32(-1))));
        }
        //TODO add macros so that user can decide how fp comparisons should be done (ordered/not) and (signaling/not)
        TSIMD_INLINE vec<double,4> operator==(const vec<double,4>& a) const {
            return _mm256_cmp_pd(data,a.data,_CMP_EQ_OQ);
        }
        TSIMD_INLINE vec<double,4> operator!=(const vec<double,4>& a) const {
            return _mm256_cmp_pd(data,a.data,_CMP_NEQ_OQ);
        }
        TSIMD_INLINE vec<double,4> operator>(const vec<double,4>& a) const {
            return _mm256_cmp_pd(data,a.data,_CMP_GT_OQ);
        }
        TSIMD_INLINE vec<double,4> operator>=(const vec<double,4>& a) const {
            return _mm256_cmp_pd(data,a.data,_CMP_GE_OQ);
        }
        TSIMD_INLINE vec<double,4> operator<(const vec<double,4>& a) const {
            return _mm256_cmp_pd(data,a.data,_CMP_LT_OQ);
        }
        TSIMD_INLINE vec<double,4> operator<=(const vec<double,4>& a) const {
            return _mm256_cmp_pd(data,a.data,_CMP_LE_OQ);
        }
        __m256d data;
        enum{ size = 4 };
        enum{ bits = 256 };
        friend std::ostream& operator<<(std::ostream& out, vec<double,4> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC4D_H
