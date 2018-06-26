#ifndef VEC8UI_H
#define VEC8UI_H

#ifdef __AVX2__
namespace TSimd{
    template<> class vec<unsigned int,8>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(unsigned int a){ data = _mm256_set1_epi32(a); }
        TSIMD_INLINE vec(unsigned int* a){ data = _mm256_loadu_si256((__m256i*)a); }
        TSIMD_INLINE vec(__m256i a){ data = a; }
        TSIMD_INLINE vec(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g, unsigned int h){ data = _mm256_set_epi32(h,g,f,e,d,c,b,a); }
        TSIMD_INLINE void store(unsigned int* a){ _mm256_storeu_si256((__m256i*)a,data); }
        TSIMD_INLINE vec<unsigned int,8>& operator+=(const vec<unsigned int,8>& rhs){
            data = _mm256_add_epi32(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned int,8>& operator-=(const vec<unsigned int,8>& rhs){
            data = _mm256_sub_epi32(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned int,8>& operator*=(const vec<unsigned int,8>& rhs){
            data = _mm256_mullo_epi32(data,rhs.data);
            return *this;
        }
        inline vec<unsigned int,8>& operator/=(const vec<unsigned int,8>& rhs){ //TODO find simd unsigned integer division algorithm
            ((unsigned int*)&data)[0]/=((unsigned int*)&rhs.data)[0];
            ((unsigned int*)&data)[1]/=((unsigned int*)&rhs.data)[1];
            ((unsigned int*)&data)[2]/=((unsigned int*)&rhs.data)[2];
            ((unsigned int*)&data)[3]/=((unsigned int*)&rhs.data)[3];
            ((unsigned int*)&data)[4]/=((unsigned int*)&rhs.data)[4];
            ((unsigned int*)&data)[5]/=((unsigned int*)&rhs.data)[5];
            ((unsigned int*)&data)[6]/=((unsigned int*)&rhs.data)[6];
            ((unsigned int*)&data)[7]/=((unsigned int*)&rhs.data)[7];
            return *this;
        }
        TSIMD_INLINE vec<unsigned int,8> operator+(const vec<unsigned int,8>& rhs) const {
            return vec<unsigned int,8>(_mm256_add_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned int,8> operator-(const vec<unsigned int,8>& rhs) const {
            return vec<unsigned int,8>(_mm256_sub_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned int,8> operator*(const vec<unsigned int,8>& rhs) const {
            return vec<unsigned int,8>(_mm256_mullo_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned int,8> operator/(const vec<unsigned int,8>& rhs) const { //TODO find simd unsigned integer division algorithm
            vec<unsigned int,8> r(data);
            r/=rhs;
            return r;
        }
        __m256i data;
        enum{ size = 8 };
        friend std::ostream& operator<<(std::ostream& out, vec<unsigned int, 8> v){
            out<<((unsigned int*)&v.data)[0]<<" "<<((unsigned int*)&v.data)[1]<<" "<<((unsigned int*)&v.data)[2]<<" "<<((unsigned int*)&v.data)[3];
            out<<" "<<((unsigned int*)&v.data)[4]<<" "<<((unsigned int*)&v.data)[5]<<" "<<((unsigned int*)&v.data)[6]<<" "<<((unsigned int*)&v.data)[7];
            return out;
        }
    };
}
#endif

#endif //VEC8UI_H
