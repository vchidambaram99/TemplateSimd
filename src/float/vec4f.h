#ifndef VEC4F_H
#define VEC4F_H

#ifdef __SSE__
namespace TSimd{
    template<> class vec<float,4>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(float a){ data = _mm_set_ps1(a); }
        TSIMD_INLINE vec(float* a){ data = _mm_loadu_ps(a); }
        TSIMD_INLINE vec(__m128 a){ data = a; }
        TSIMD_INLINE vec(float a, float b, float c, float d){ data = _mm_set_ps(d,c,b,a); }
        TSIMD_INLINE void store(float* a){ _mm_storeu_ps(a,data); }
        TSIMD_INLINE vec<float,4>& operator+=(const vec<float,4>& rhs){
            data = _mm_add_ps(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<float,4>& operator-=(const vec<float,4>& rhs){
            data = _mm_sub_ps(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<float,4>& operator*=(const vec<float,4>& rhs){
            data = _mm_mul_ps(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<float,4>& operator/=(const vec<float,4>& rhs){
            data = _mm_div_ps(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<float,4> operator+(const vec<float,4>& rhs) const {
            return vec<float,4>(_mm_add_ps(data,rhs.data));
        }
        TSIMD_INLINE vec<float,4> operator-(const vec<float,4>& rhs) const {
            return vec<float,4>(_mm_sub_ps(data,rhs.data));
        }
        TSIMD_INLINE vec<float,4> operator*(const vec<float,4>& rhs) const {
            return vec<float,4>(_mm_mul_ps(data,rhs.data));
        }
        TSIMD_INLINE vec<float,4> operator/(const vec<float,4>& rhs) const {
            return vec<float,4>(_mm_div_ps(data,rhs.data));
        }
        __m128 data;
        enum{ size = 4 };
        friend std::ostream& operator<<(std::ostream& out, vec<float,4> v){
            out<<((float*)&v.data)[0]<<" "<<((float*)&v.data)[1]<<" "<<((float*)&v.data)[2]<<" "<<((float*)&v.data)[3];
            return out;
        }
    };
}
#endif

#endif
