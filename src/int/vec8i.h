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
        TSIMD_INLINE int& operator[](int idx){ return ((int*)(&data))[idx]; }
        TSIMD_INLINE const int& operator[](int idx) const { return ((int*)(&data))[idx]; }
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
            (*this)[0]/=rhs[0];
            (*this)[1]/=rhs[1];
            (*this)[2]/=rhs[2];
            (*this)[3]/=rhs[3];
            (*this)[4]/=rhs[4];
            (*this)[5]/=rhs[5];
            (*this)[6]/=rhs[6];
            (*this)[7]/=rhs[7];
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
        TSIMD_INLINE vec<int,8> operator&=(const vec<int,8>& rhs){
            data = _mm256_and_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int,8> operator|=(const vec<int,8>& rhs){
            data = _mm256_or_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int,8> operator^=(const vec<int,8>& rhs){
            data = _mm256_xor_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int,8> operator&(const vec<int,8>& rhs) const {
            return vec<int,8>(_mm256_and_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<int,8> operator|(const vec<int,8>& rhs) const {
            return vec<int,8>(_mm256_or_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<int,8> operator^(const vec<int,8>& rhs) const {
            return vec<int,8>(_mm256_xor_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<int,8> operator~() const {
            return vec<int,8>(_mm256_xor_si256(data,_mm256_set1_epi32(-1)));
        }
        __m256i data;
        enum{ size = 8 };
        enum{ bits = 256 };
        friend std::ostream& operator<<(std::ostream& out, vec<int, 8> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            out<<" "<<v[4]<<" "<<v[5]<<" "<<v[6]<<" "<<v[7];
            return out;
        }
    };
}
#endif

#endif //VEC8I_H
