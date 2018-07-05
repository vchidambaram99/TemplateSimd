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
        TSIMD_INLINE float& operator[](int idx){ return ((float*)(&data))[idx]; }
        TSIMD_INLINE const float& operator[](int idx) const { return ((float*)(&data))[idx]; }
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
        TSIMD_INLINE vec<float,4> operator&=(const vec<float,4>& rhs){
            data = _mm_and_ps(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<float,4> operator|=(const vec<float,4>& rhs){
            data = _mm_or_ps(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<float,4> operator^=(const vec<float,4>& rhs){
            data = _mm_xor_ps(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<float,4> operator&(const vec<float,4>& rhs) const {
            return vec<float,4>(_mm_and_ps(data,rhs.data));
        }
        TSIMD_INLINE vec<float,4> operator|(const vec<float,4>& rhs) const {
            return vec<float,4>(_mm_or_ps(data,rhs.data));
        }
        TSIMD_INLINE vec<float,4> operator^(const vec<float,4>& rhs) const {
            return vec<float,4>(_mm_xor_ps(data,rhs.data));
        }
        TSIMD_INLINE vec<float,4> operator~() const {
            return vec<float,4>(_mm_xor_ps(data,_mm_castsi128_ps(_mm_set1_epi32(-1))));
        }
        __m128 data;
        enum{ size = 4 };
        enum{ bits = 128 };
        friend std::ostream& operator<<(std::ostream& out, vec<float,4> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            return out;
        }
    };
}
#endif

#endif
