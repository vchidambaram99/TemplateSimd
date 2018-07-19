#ifndef TSIMD_VEC32C_H
#define TSIMD_VEC32C_H

#include "../../tsimd.h"

#ifdef __AVX2__
namespace TSimd{
    template<> class vec<char,32>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(char a){ data = _mm256_set1_epi8(a); }
        TSIMD_INLINE explicit vec(char* a){ data = _mm256_loadu_si256((__m256i*)a); }
        TSIMD_INLINE vec(__m256i a){ data = a; }
        TSIMD_INLINE vec(char a0, char a1, char a2, char a3, char a4, char a5, char a6, char a7, char a8, char a9, char a10, char a11, char a12, char a13, char a14, char a15, char a16,
                         char a17, char a18, char a19, char a20, char a21, char a22, char a23, char a24, char a25, char a26, char a27, char a28, char a29, char a30, char a31){
            data = _mm256_set_epi8(a31,a30,a29,a28,a27,a26,a25,a24,a23,a22,a21,a20,a19,a18,a17,a16,a15,a14,a13,a12,a11,a10,a9,a8,a7,a6,a5,a4,a3,a2,a1,a0);
        }
        TSIMD_INLINE void store(char* a) const { _mm256_storeu_si256((__m256i*)a,data); }
        TSIMD_INLINE intl::AssignmentProxy<char,32> operator[](const std::size_t idx){ return intl::AssignmentProxy<char,32>(*this,idx); }
        TSIMD_INLINE vec<char,32>& operator+=(const vec<char,32> rhs){
            data = _mm256_add_epi8(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<char,32>& operator-=(const vec<char,32> rhs){
            data = _mm256_sub_epi8(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<char,32>& operator*=(const vec<char,32> rhs){
            __m256i a = _mm256_mullo_epi16(data,rhs.data);
            __m256i b = _mm256_mullo_epi16(_mm256_srli_epi16(data,8),_mm256_srli_epi16(rhs.data,8));
            a = _mm256_srli_epi16(_mm256_slli_epi16(a,8),8);
            b = _mm256_slli_epi16(b,8);
            data = _mm256_or_si256(a,b);
            return *this;
        }
        inline vec<char,32>& operator/=(const vec<char,32> rhs){ //inefficient, but still faster than scalar
            __m256i a1 = _mm256_srai_epi32(data,24);
            __m256i b1 = _mm256_srai_epi32(rhs.data,24);
            __m256 a1f = _mm256_cvtepi32_ps(a1);
            __m256 b1f = _mm256_cvtepi32_ps(b1);
            a1 = _mm256_cvttps_epi32(_mm256_div_ps(a1f,b1f));
            a1 = _mm256_slli_epi32(a1,24);
            __m256i a2 = _mm256_srai_epi32(_mm256_slli_epi32(data,8),24);
            __m256i b2 = _mm256_srai_epi32(_mm256_slli_epi32(rhs.data,8),24);
            __m256 a2f = _mm256_cvtepi32_ps(a2);
            __m256 b2f = _mm256_cvtepi32_ps(b2);
            a2 = _mm256_cvttps_epi32(_mm256_div_ps(a2f,b2f));
            a2 = _mm256_srli_epi32(_mm256_slli_epi32(a2,24),8);
            __m256i a3 = _mm256_srai_epi32(_mm256_slli_epi32(data,16),24);
            __m256i b3 = _mm256_srai_epi32(_mm256_slli_epi32(rhs.data,16),24);
            __m256 a3f = _mm256_cvtepi32_ps(a3);
            __m256 b3f = _mm256_cvtepi32_ps(b3);
            a3 = _mm256_cvttps_epi32(_mm256_div_ps(a3f,b3f));
            a3 = _mm256_srli_epi32(_mm256_slli_epi32(a3,24),16);
            __m256i a4 = _mm256_srai_epi32(_mm256_slli_epi32(data,24),24);
            __m256i b4 = _mm256_srai_epi32(_mm256_slli_epi32(rhs.data,24),24);
            __m256 a4f = _mm256_cvtepi32_ps(a4);
            __m256 b4f = _mm256_cvtepi32_ps(b4);
            a4 = _mm256_cvttps_epi32(_mm256_div_ps(a4f,b4f));
            a4 = _mm256_srli_epi32(_mm256_slli_epi32(a4,24),24);
            data = _mm256_or_si256(a1,_mm256_or_si256(a2,_mm256_or_si256(a3,a4)));
            return *this;
        }
        TSIMD_INLINE vec<char,32> operator+(const vec<char,32> rhs) const {
            return vec<char,32>(_mm256_add_epi8(data,rhs.data));
        }
        TSIMD_INLINE vec<char,32> operator-(const vec<char,32> rhs) const {
            return vec<char,32>(_mm256_sub_epi8(data,rhs.data));
        }
        TSIMD_INLINE vec<char,32> operator*(const vec<char,32> rhs) const {
            __m256i a = _mm256_mullo_epi16(data,rhs.data);
            __m256i b = _mm256_mullo_epi16(_mm256_srli_epi16(data,8),_mm256_srli_epi16(rhs.data,8));
            a = _mm256_srli_epi16(_mm256_slli_epi16(a,8),8);
            b = _mm256_slli_epi16(b,8);
            return vec<char,32>(_mm256_or_si256(a,b));
        }
        TSIMD_INLINE vec<char,32> operator/(const vec<char,32> rhs) const {
            vec<char,32> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<char,32>& operator&=(const vec<char,32> rhs){
            data = _mm256_and_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<char,32>& operator|=(const vec<char,32> rhs){
            data = _mm256_or_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<char,32>& operator^=(const vec<char,32> rhs){
            data = _mm256_xor_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<char,32> operator&(const vec<char,32> rhs) const {
            return vec<char,32>(_mm256_and_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<char,32> operator|(const vec<char,32> rhs) const {
            return vec<char,32>(_mm256_or_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<char,32> operator^(const vec<char,32> rhs) const {
            return vec<char,32>(_mm256_xor_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<char,32> operator~() const {
            return vec<char,32>(_mm256_xor_si256(data,_mm256_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<char,32>& operator<<=(const int shift){
            __m256i a = _mm256_slli_epi16(data,8);
            data = _mm256_and_si256(a,_mm256_set1_epi8(0xFF<<shift));
            return *this;
        }
        TSIMD_INLINE vec<char,32>& operator>>=(const int shift){
            __m256i hi = _mm256_srai_epi16(_mm256_unpackhi_epi8(data,data),shift+8);
            __m256i lo = _mm256_srai_epi16(_mm256_unpacklo_epi8(data,data),shift+8);
            data = _mm256_packs_epi16(lo,hi);
            return *this;
        }
        TSIMD_INLINE vec<char,32> operator<<(const int shift) const {
            __m256i a = _mm256_slli_epi16(data,8);
            return vec<char,32>(_mm256_and_si256(a,_mm256_set1_epi8(0xFF<<shift)));
        }
        TSIMD_INLINE vec<char,32> operator>>(const int shift) const {
            __m256i hi = _mm256_srai_epi16(_mm256_unpackhi_epi8(data,data),shift+8);
            __m256i lo = _mm256_srai_epi16(_mm256_unpacklo_epi8(data,data),shift+8);
            return vec<char,32>(_mm256_packs_epi16(lo,hi));
        }
        TSIMD_INLINE vec<char,32> operator==(const vec<char,32> a) const {
            return _mm256_cmpeq_epi8(data,a.data);
        }
        TSIMD_INLINE vec<char,32> operator!=(const vec<char,32> a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE vec<char,32> operator>(const vec<char,32> a) const {
            return _mm256_cmpgt_epi8(data,a.data);
        }
        TSIMD_INLINE vec<char,32> operator>=(const vec<char,32> a) const {
            return (*this>a)|(*this==a);
        }
        TSIMD_INLINE vec<char,32> operator<(const vec<char,32> a) const {
            return a>*this;
        }
        TSIMD_INLINE vec<char,32> operator<=(const vec<char,32> a) const {
            return (*this<a)|(*this==a);
        }
        __m256i data;
        enum{ size = 32 };
        enum{ bits = 256 };
        friend std::ostream& operator<<(std::ostream& out, vec<char, 32> v){
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

#endif //TSIMD_VEC32C_H
