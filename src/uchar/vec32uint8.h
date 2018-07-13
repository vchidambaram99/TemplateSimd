#ifndef TSIMD_VEC32UINT8_H
#define TSIMD_VEC32UINT8_H

#include "../../tsimd.h"

#ifdef __AVX2__
namespace TSimd{
    template<> class vec<uint8_t,32>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(uint8_t a){ data = _mm256_set1_epi8(a); }
        TSIMD_INLINE vec(uint8_t* a){ data = _mm256_loadu_si256((__m256i*)a); }
        TSIMD_INLINE vec(__m256i a){ data = a; }
        TSIMD_INLINE vec(uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4, uint8_t a5, uint8_t a6, uint8_t a7, uint8_t a8, uint8_t a9, uint8_t a10, uint8_t a11, uint8_t a12, uint8_t a13, uint8_t a14, uint8_t a15, uint8_t a16,
                         uint8_t a17, uint8_t a18, uint8_t a19, uint8_t a20, uint8_t a21, uint8_t a22, uint8_t a23, uint8_t a24, uint8_t a25, uint8_t a26, uint8_t a27, uint8_t a28, uint8_t a29, uint8_t a30, uint8_t a31){
            data = _mm256_set_epi8(a31,a30,a29,a28,a27,a26,a25,a24,a23,a22,a21,a20,a19,a18,a17,a16,a15,a14,a13,a12,a11,a10,a9,a8,a7,a6,a5,a4,a3,a2,a1,a0);
        }
        TSIMD_INLINE void store(uint8_t* a){ _mm256_storeu_si256((__m256i*)a,data); }
        TSIMD_INLINE uint8_t& operator[](int idx){ return ((uint8_t*)(&data))[idx]; }
        TSIMD_INLINE const uint8_t& operator[](int idx) const { return ((uint8_t*)(&data))[idx]; }
        TSIMD_INLINE vec<uint8_t,32>& operator+=(const vec<uint8_t,32>& rhs){
            data = _mm256_add_epi8(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,32>& operator-=(const vec<uint8_t,32>& rhs){
            data = _mm256_sub_epi8(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,32>& operator*=(const vec<uint8_t,32>& rhs){
            __m256i a = _mm256_mullo_epi16(data,rhs.data);
            __m256i b = _mm256_mullo_epi16(_mm256_srli_epi16(data,8),_mm256_srli_epi16(rhs.data,8));
            a = _mm256_srli_epi16(_mm256_slli_epi16(a,8),8);
            b = _mm256_slli_epi16(b,8);
            data = _mm256_or_si256(a,b);
            return *this;
        }
        inline vec<uint8_t,32>& operator/=(const vec<uint8_t,32>& rhs){ //TODO find simd integer division algorithm
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
            (*this)[16]/=rhs[16];
            (*this)[17]/=rhs[17];
            (*this)[18]/=rhs[18];
            (*this)[19]/=rhs[19];
            (*this)[20]/=rhs[20];
            (*this)[21]/=rhs[21];
            (*this)[22]/=rhs[22];
            (*this)[23]/=rhs[23];
            (*this)[24]/=rhs[24];
            (*this)[25]/=rhs[25];
            (*this)[26]/=rhs[26];
            (*this)[27]/=rhs[27];
            (*this)[28]/=rhs[28];
            (*this)[29]/=rhs[29];
            (*this)[30]/=rhs[30];
            (*this)[31]/=rhs[31];
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,32> operator+(const vec<uint8_t,32>& rhs) const {
            return vec<uint8_t,32>(_mm256_add_epi8(data,rhs.data));
        }
        TSIMD_INLINE vec<uint8_t,32> operator-(const vec<uint8_t,32>& rhs) const {
            return vec<uint8_t,32>(_mm256_sub_epi8(data,rhs.data));
        }
        TSIMD_INLINE vec<uint8_t,32> operator*(const vec<uint8_t,32>& rhs) const {
            __m256i a = _mm256_mullo_epi16(data,rhs.data);
            __m256i b = _mm256_mullo_epi16(_mm256_srli_epi16(data,8),_mm256_srli_epi16(rhs.data,8));
            a = _mm256_srli_epi16(_mm256_slli_epi16(a,8),8);
            b = _mm256_slli_epi16(b,8);
            return vec<uint8_t,32>(_mm256_or_si256(a,b));
        }
        TSIMD_INLINE vec<uint8_t,32> operator/(const vec<uint8_t,32>& rhs) const { //TODO find simd integer division algorithm
            vec<uint8_t,32> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<uint8_t,32>& operator&=(const vec<uint8_t,32>& rhs){
            data = _mm256_and_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,32>& operator|=(const vec<uint8_t,32>& rhs){
            data = _mm256_or_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,32>& operator^=(const vec<uint8_t,32>& rhs){
            data = _mm256_xor_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,32> operator&(const vec<uint8_t,32>& rhs) const {
            return vec<uint8_t,32>(_mm256_and_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<uint8_t,32> operator|(const vec<uint8_t,32>& rhs) const {
            return vec<uint8_t,32>(_mm256_or_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<uint8_t,32> operator^(const vec<uint8_t,32>& rhs) const {
            return vec<uint8_t,32>(_mm256_xor_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<uint8_t,32> operator~() const {
            return vec<uint8_t,32>(_mm256_xor_si256(data,_mm256_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<uint8_t,32>& operator<<=(const int& shift){
            __m256i a = _mm256_slli_epi16(data,8);
            data = _mm256_and_si256(a,_mm256_set1_epi8(0xFF<<shift));
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,32>& operator>>=(const int& shift){
            __m256i a = _mm256_srli_epi16(data,shift);
            data = _mm256_and_si256(a,_mm256_set1_epi8(((unsigned int)(0xFF))>>shift));
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,32> operator<<(const int& shift) const {
            __m256i a = _mm256_slli_epi16(data,8);
            return vec<uint8_t,32>(_mm256_and_si256(a,_mm256_set1_epi8(0xFF<<shift)));
        }
        TSIMD_INLINE vec<uint8_t,32> operator>>(const int& shift) const {
            __m256i a = _mm256_srli_epi16(data,shift);
            return vec<uint8_t,32>(_mm256_and_si256(a,_mm256_set1_epi8(((unsigned int)(0xFF))>>shift)));
        }
        TSIMD_INLINE vec<uint8_t,32> operator==(const vec<uint8_t,32>& a) const {
            return _mm256_cmpeq_epi8(data,a.data);
        }
        TSIMD_INLINE vec<uint8_t,32> operator!=(const vec<uint8_t,32>& a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE vec<uint8_t,32> operator>(const vec<uint8_t,32>& a) const {
            return ~(*this<=a);
        }
        TSIMD_INLINE vec<uint8_t,32> operator>=(const vec<uint8_t,32>& a) const {
            return (*this)==_mm256_max_epu8(data,a.data);
        }
        TSIMD_INLINE vec<uint8_t,32> operator<(const vec<uint8_t,32>& a) const {
            return a>*this;
        }
        TSIMD_INLINE vec<uint8_t,32> operator<=(const vec<uint8_t,32>& a) const {
            return (*this)==_mm256_min_epu8(data,a.data);
        }
        __m256i data;
        enum{ size = 32 };
        enum{ bits = 256 };
        friend std::ostream& operator<<(std::ostream& out, vec<uint8_t, 32> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            out<<" "<<v[4]<<" "<<v[5]<<" "<<v[6]<<" "<<v[7];
            out<<" "<<v[8]<<" "<<v[9]<<" "<<v[10]<<" "<<v[11];
            out<<" "<<v[12]<<" "<<v[13]<<" "<<v[14]<<" "<<v[15];
            out<<" "<<v[16]<<" "<<v[17]<<" "<<v[18]<<" "<<v[19];
            out<<" "<<v[20]<<" "<<v[21]<<" "<<v[22]<<" "<<v[23];
            out<<" "<<v[24]<<" "<<v[25]<<" "<<v[26]<<" "<<v[27];
            out<<" "<<v[28]<<" "<<v[29]<<" "<<v[30]<<" "<<v[31];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC32UINT8_H
