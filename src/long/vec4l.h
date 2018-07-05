#ifndef VEC4L_H
#define VEC4L_H

#ifdef __AVX2__
namespace TSimd{
    template<> class vec<long,4>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(long a){ data = _mm256_set1_epi64x(a); }
        TSIMD_INLINE vec(long* a){ data = _mm256_loadu_si256((__m256i*)a); }
        TSIMD_INLINE vec(__m256i a){ data = a; }
        TSIMD_INLINE vec(long a, long b, long c, long d){ data = _mm256_set_epi64x(d,c,b,a); }
        TSIMD_INLINE void store(long* a){ _mm256_storeu_si256((__m256i*)a,data); }
        TSIMD_INLINE long& operator[](int idx){ return ((long*)(&data))[idx]; }
        TSIMD_INLINE const long& operator[](int idx) const { return ((long*)(&data))[idx]; }
        TSIMD_INLINE vec<long,4>& operator+=(const vec<long,4>& rhs){
            data = _mm256_add_epi64(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<long,4>& operator-=(const vec<long,4>& rhs){
            data = _mm256_sub_epi64(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<long,4>& operator*=(const vec<long,4>& rhs){
            __m256i a = _mm256_mul_epu32(data,rhs.data);
            __m256i b = _mm256_mul_epu32(_mm256_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),rhs.data);
            __m256i c = _mm256_mul_epu32(data,_mm256_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
            b = _mm256_slli_epi64(b,32);
            c = _mm256_slli_epi64(c,32);
            data = _mm256_add_epi64(a,_mm256_add_epi64(b,c));
            return *this;
        }
        inline vec<long,4>& operator/=(const vec<long,4>& rhs){ //TODO find simd integer division algorithm
            (*this)[0]/=rhs[0];
            (*this)[1]/=rhs[1];
            (*this)[2]/=rhs[2];
            (*this)[3]/=rhs[3];
            return *this;
        }
        TSIMD_INLINE vec<long,4> operator+(const vec<long,4>& rhs) const {
            return vec<long,4>(_mm256_add_epi64(data,rhs.data));
        }
        TSIMD_INLINE vec<long,4> operator-(const vec<long,4>& rhs) const {
            return vec<long,4>(_mm256_sub_epi64(data,rhs.data));
        }
        TSIMD_INLINE vec<long,4> operator*(const vec<long,4>& rhs) const {
            __m256i a = _mm256_mul_epu32(data,rhs.data);
            __m256i b = _mm256_mul_epu32(_mm256_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),rhs.data);
            __m256i c = _mm256_mul_epu32(data,_mm256_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
            b = _mm256_slli_epi64(b,32);
            c = _mm256_slli_epi64(c,32);
            return vec<long,4>(_mm256_add_epi64(a,_mm256_add_epi64(b,c)));
        }
        TSIMD_INLINE vec<long,4> operator/(const vec<long,4>& rhs) const { //TODO find simd integer division algorithm
            vec<long,4> r(data);
            r/=rhs;
            return r;
        }
        __m256i data;
        enum{ size = 4 };
        friend std::ostream& operator<<(std::ostream& out, vec<long,4> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            return out;
        }
    };
}
#endif

#endif //VEC4L_H
