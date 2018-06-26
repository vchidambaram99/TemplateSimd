#ifndef VEC8F_H
#define VEC8F_H

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
        __m256 data;
        enum{ size = 8 };
        friend std::ostream& operator<<(std::ostream& out, vec<float,8> v){
            out<<((float*)&v.data)[0]<<" "<<((float*)&v.data)[1]<<" "<<((float*)&v.data)[2]<<" "<<((float*)&v.data)[3];
            out<<" "<<((float*)&v.data)[4]<<" "<<((float*)&v.data)[5]<<" "<<((float*)&v.data)[6]<<" "<<((float*)&v.data)[7];
            return out;
        }
    };
}
#endif

#endif //VEC8F_H
