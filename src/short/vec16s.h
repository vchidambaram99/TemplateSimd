#ifndef VEC16S_H
#define VEC16S_H

#include "../../tsimd.h"

#ifdef __SSE2__
namespace TSimd{
    template<> class vec<short,16>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(short a){ data = _mm256_set1_epi16(a); }
        TSIMD_INLINE vec(short* a){ data = _mm256_loadu_si256((__m256i*)a); }
        TSIMD_INLINE vec(__m256i a){ data = a; }
        TSIMD_INLINE vec(short a, short b, short c, short d, short e, short f, short g, short h, short i, short j, short k, short l, short m, short n, short o, short p){
            data = _mm256_set_epi16(p,o,n,m,l,k,j,i,h,g,f,e,d,c,b,a);
        }
        TSIMD_INLINE void store(short* a){ _mm256_storeu_si256((__m256i*)a,data); }
        TSIMD_INLINE short& operator[](int idx){ return ((short*)(&data))[idx]; }
        TSIMD_INLINE const short& operator[](int idx) const { return ((short*)(&data))[idx]; }
        TSIMD_INLINE vec<short,16>& operator+=(const vec<short,16>& rhs){
            data = _mm256_add_epi16(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<short,16>& operator-=(const vec<short,16>& rhs){
            data = _mm256_sub_epi16(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<short,16>& operator*=(const vec<short,16>& rhs){
            data = _mm256_mullo_epi16(data,rhs.data);
            return *this;
        }
        inline vec<short,16>& operator/=(const vec<short,16>& rhs){ //TODO find simd integer division algorithm
            (*this)[0]/=rhs[0];
            (*this)[1]/=rhs[1];
            (*this)[2]/=rhs[2];
            (*this)[3]/=rhs[3];
            (*this)[4]/=rhs[4];
            (*this)[5]/=rhs[5];
            (*this)[6]/=rhs[6];
            (*this)[7]/=rhs[7];
            (*this)[8]/=rhs[8];
            (*this)[9]/=rhs[9];
            (*this)[10]/=rhs[10];
            (*this)[11]/=rhs[11];
            (*this)[12]/=rhs[12];
            (*this)[13]/=rhs[13];
            (*this)[14]/=rhs[14];
            (*this)[15]/=rhs[15];
            return *this;
        }
        TSIMD_INLINE vec<short,16> operator+(const vec<short,16>& rhs) const {
            return vec<short,16>(_mm256_add_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<short,16> operator-(const vec<short,16>& rhs) const {
            return vec<short,16>(_mm256_sub_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<short,16> operator*(const vec<short,16>& rhs) const {
            return vec<short,16>(_mm256_mullo_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<short,16> operator/(const vec<short,16>& rhs) const { //TODO find simd integer division algorithm
            vec<short,16> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<short,16> operator&=(const vec<short,16>& rhs){
            data = _mm256_and_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<short,16> operator|=(const vec<short,16>& rhs){
            data = _mm256_or_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<short,16> operator^=(const vec<short,16>& rhs){
            data = _mm256_xor_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<short,16> operator&(const vec<short,16>& rhs) const {
            return vec<short,16>(_mm256_and_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<short,16> operator|(const vec<short,16>& rhs) const {
            return vec<short,16>(_mm256_or_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<short,16> operator^(const vec<short,16>& rhs) const {
            return vec<short,16>(_mm256_xor_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<short,16> operator~() const {
            return vec<short,16>(_mm256_xor_si256(data,_mm256_set1_epi32(-1)));
        }
        __m256i data;
        enum{ size = 16 };
        enum{ bits = 256 };
        friend std::ostream& operator<<(std::ostream& out, vec<short,16> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            out<<" "<<v[4]<<" "<<v[5]<<" "<<v[6]<<" "<<v[7];
            out<<" "<<v[8]<<" "<<v[9]<<" "<<v[10]<<" "<<v[11];
            out<<" "<<v[12]<<" "<<v[13]<<" "<<v[14]<<" "<<v[15];
            return out;
        }
    };
}
#endif

#endif //VEC16S_H
