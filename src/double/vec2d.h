#ifndef TSIMD_VEC2D_H
#define TSIMD_VEC2D_H

#include "../../tsimd.h"

#ifdef __SSE2__
namespace TSimd{
    template<> class vec<double,2>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(double a){ data = _mm_set_pd1(a); }
        TSIMD_INLINE vec(double* a){ data = _mm_loadu_pd(a); }
        TSIMD_INLINE vec(__m128d a){ data = a; }
        TSIMD_INLINE vec(double a, double b){ data = _mm_set_pd(b,a); }
        TSIMD_INLINE void store(double* a){ _mm_storeu_pd(a,data); }
        TSIMD_INLINE double& operator[](int idx){ return ((double*)(&data))[idx]; }
        TSIMD_INLINE const double& operator[](int idx) const { return ((double*)(&data))[idx]; }
        TSIMD_INLINE vec<double,2>& operator+=(const vec<double,2>& rhs){
            data = _mm_add_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,2>& operator-=(const vec<double,2>& rhs){
            data = _mm_sub_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,2>& operator*=(const vec<double,2>& rhs){
            data = _mm_mul_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,2>& operator/=(const vec<double,2>& rhs){
            data = _mm_div_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,2> operator+(const vec<double,2>& rhs) const {
            return vec<double,2>(_mm_add_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,2> operator-(const vec<double,2>& rhs) const {
            return vec<double,2>(_mm_sub_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,2> operator*(const vec<double,2>& rhs) const {
            return vec<double,2>(_mm_mul_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,2> operator/(const vec<double,2>& rhs) const {
            return vec<double,2>(_mm_div_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,2>& operator&=(const vec<double,2>& rhs){
            data = _mm_and_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,2>& operator|=(const vec<double,2>& rhs){
            data = _mm_or_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,2>& operator^=(const vec<double,2>& rhs){
            data = _mm_xor_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,2> operator&(const vec<double,2>& rhs) const {
            return vec<double,2>(_mm_and_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,2> operator|(const vec<double,2>& rhs) const {
            return vec<double,2>(_mm_or_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,2> operator^(const vec<double,2>& rhs) const {
            return vec<double,2>(_mm_xor_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,2> operator~() const {
            return vec<double,2>(_mm_xor_pd(data,_mm_castsi128_pd(_mm_set1_epi32(-1))));
        }
        __m128d data;
        enum{ size = 2 };
        enum{ bits = 128 };
        friend std::ostream& operator<<(std::ostream& out, vec<double,2> v){
            out<<v[0]<<" "<<v[1];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC2D_H
