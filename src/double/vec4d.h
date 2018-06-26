#ifndef VEC4D_H
#define VEC4D_H

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
        __m256d data;
        enum{ size = 4 };
        friend std::ostream& operator<<(std::ostream& out, vec<double,4> v){
            out<<((double*)&v.data)[0]<<" "<<((double*)&v.data)[1]<<" "<<((double*)&v.data)[2]<<" "<<((double*)&v.data)[3];
            return out;
        }
    };
}
#endif

#endif //VEC4D_H
