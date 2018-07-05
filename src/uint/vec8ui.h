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
        TSIMD_INLINE unsigned int& operator[](int idx){ return ((unsigned int*)(&data))[idx]; }
        TSIMD_INLINE const unsigned int& operator[](int idx) const { return ((unsigned int*)(&data))[idx]; }
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
        TSIMD_INLINE vec<unsigned int,8> operator&=(const vec<unsigned int,8>& rhs){
            data = _mm256_and_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned int,8> operator|=(const vec<unsigned int,8>& rhs){
            data = _mm256_or_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned int,8> operator^=(const vec<unsigned int,8>& rhs){
            data = _mm256_xor_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned int,8> operator&(const vec<unsigned int,8>& rhs) const {
            return vec<unsigned int,8>(_mm256_and_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned int,8> operator|(const vec<unsigned int,8>& rhs) const {
            return vec<unsigned int,8>(_mm256_or_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned int,8> operator^(const vec<unsigned int,8>& rhs) const {
            return vec<unsigned int,8>(_mm256_xor_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned int,8> operator~() const {
            return vec<unsigned int,8>(_mm256_xor_si256(data,_mm256_set1_epi32(-1)));
        }
        __m256i data;
        enum{ size = 8 };
        enum{ bits = 256 };
        friend std::ostream& operator<<(std::ostream& out, vec<unsigned int,8> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            out<<" "<<v[4]<<" "<<v[5]<<" "<<v[6]<<" "<<v[7];
            return out;
        }
    };
}
#endif

#endif //VEC8UI_H
