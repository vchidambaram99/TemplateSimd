#ifndef VEC8I_H
#define VEC8I_H

#ifdef __AVX2__
namespace TSimd{
    template<> class vec<int,8>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(int a){ data = _mm256_set1_epi32(a); }
        TSIMD_INLINE vec(int* a){ data = _mm256_loadu_si256((__m256i*)a); }
        TSIMD_INLINE vec(__m256i a){ data = a; }
        TSIMD_INLINE vec(int a, int b, int c, int d, int e, int f, int g, int h){ data = _mm256_set_epi32(h,g,f,e,d,c,b,a); }
        TSIMD_INLINE void store(int* a){ _mm256_storeu_si256((__m256i*)a,data); }
        TSIMD_INLINE vec<int,8>& operator+=(const vec<int,8>& rhs){
            data = _mm256_add_epi32(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int,8>& operator-=(const vec<int,8>& rhs){
            data = _mm256_sub_epi32(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int,8>& operator*=(const vec<int,8>& rhs){
            data = _mm256_mullo_epi32(data,rhs.data);
            return *this;
        }
        inline vec<int,8>& operator/=(const vec<int,8>& rhs){ //TODO find simd integer division algorithm
            ((int*)&data)[0]/=((int*)&rhs.data)[0];
            ((int*)&data)[1]/=((int*)&rhs.data)[1];
            ((int*)&data)[2]/=((int*)&rhs.data)[2];
            ((int*)&data)[3]/=((int*)&rhs.data)[3];
            ((int*)&data)[4]/=((int*)&rhs.data)[4];
            ((int*)&data)[5]/=((int*)&rhs.data)[5];
            ((int*)&data)[6]/=((int*)&rhs.data)[6];
            ((int*)&data)[7]/=((int*)&rhs.data)[7];
            return *this;
        }
        TSIMD_INLINE vec<int,8> operator+(const vec<int,8>& rhs) const {
            return vec<int,8>(_mm256_add_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<int,8> operator-(const vec<int,8>& rhs) const {
            return vec<int,8>(_mm256_sub_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<int,8> operator*(const vec<int,8>& rhs) const {
            return vec<int,8>(_mm256_mullo_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<int,8> operator/(const vec<int,8>& rhs) const { //TODO find simd integer division algorithm
            vec<int,8> r(data);
            r/=rhs;
            return r;
        }
        __m256i data;
        enum{ size = 8 };
        friend std::ostream& operator<<(std::ostream& out, vec<int, 8> v){
            out<<((int*)&v.data)[0]<<" "<<((int*)&v.data)[1]<<" "<<((int*)&v.data)[2]<<" "<<((int*)&v.data)[3];
            out<<" "<<((int*)&v.data)[4]<<" "<<((int*)&v.data)[5]<<" "<<((int*)&v.data)[6]<<" "<<((int*)&v.data)[7];
            return out;
        }
    };
}
#endif

#endif //VEC8I_H
