#ifndef TSIMD_VEC32INT8_H
#define TSIMD_VEC32INT8_H

#include "../../tsimd.h"

#ifdef __AVX2__
namespace TSimd{
    template<> class vec<int8_t,32>{
    public:
        typedef mask<256> masktype;
        typedef __m256i simdtype;
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(int8_t a){ data = _mm256_set1_epi8(a); }
        TSIMD_INLINE explicit vec(int8_t* a){ data = _mm256_loadu_si256((__m256i*)a); }
        TSIMD_INLINE vec(__m256i a){ data = a; }
        TSIMD_INLINE vec(int8_t a0, int8_t a1, int8_t a2, int8_t a3, int8_t a4, int8_t a5, int8_t a6, int8_t a7, int8_t a8, int8_t a9, int8_t a10, int8_t a11, int8_t a12, int8_t a13, int8_t a14, int8_t a15, int8_t a16,
                         int8_t a17, int8_t a18, int8_t a19, int8_t a20, int8_t a21, int8_t a22, int8_t a23, int8_t a24, int8_t a25, int8_t a26, int8_t a27, int8_t a28, int8_t a29, int8_t a30, int8_t a31){
            data = _mm256_set_epi8(a31,a30,a29,a28,a27,a26,a25,a24,a23,a22,a21,a20,a19,a18,a17,a16,a15,a14,a13,a12,a11,a10,a9,a8,a7,a6,a5,a4,a3,a2,a1,a0);
        }
        TSIMD_INLINE void store(int8_t* a) const { _mm256_storeu_si256((__m256i*)a,data); }
        TSIMD_INLINE intl::ConstProxy<int8_t,32> operator[](const std::size_t idx) const { return intl::ConstProxy<int8_t,32>(*this,idx); }
        TSIMD_INLINE intl::AssignmentProxy<int8_t,32> operator[](const std::size_t idx){ return intl::AssignmentProxy<int8_t,32>(*this,idx); }
        TSIMD_INLINE static vec<int8_t,32> zero(){ return _mm256_setzero_si256(); }
        TSIMD_INLINE vec<int8_t,32>& operator+=(const vec<int8_t,32> rhs){
            data = _mm256_add_epi8(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int8_t,32>& operator-=(const vec<int8_t,32> rhs){
            data = _mm256_sub_epi8(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int8_t,32>& operator*=(const vec<int8_t,32> rhs){
            __m256i a = _mm256_mullo_epi16(data,rhs.data);
            __m256i b = _mm256_mullo_epi16(_mm256_srli_epi16(data,8),_mm256_srli_epi16(rhs.data,8));
            a = _mm256_srli_epi16(_mm256_slli_epi16(a,8),8);
            b = _mm256_slli_epi16(b,8);
            data = _mm256_or_si256(a,b);
            return *this;
        }
        inline vec<int8_t,32>& operator/=(const vec<int8_t,32> rhs){ //inefficient, but still faster than scalar
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
        TSIMD_INLINE vec<int8_t,32> operator+(const vec<int8_t,32> rhs) const {
            return vec<int8_t,32>(_mm256_add_epi8(data,rhs.data));
        }
        TSIMD_INLINE vec<int8_t,32> operator-(const vec<int8_t,32> rhs) const {
            return vec<int8_t,32>(_mm256_sub_epi8(data,rhs.data));
        }
        TSIMD_INLINE vec<int8_t,32> operator*(const vec<int8_t,32> rhs) const {
            __m256i a = _mm256_mullo_epi16(data,rhs.data);
            __m256i b = _mm256_mullo_epi16(_mm256_srli_epi16(data,8),_mm256_srli_epi16(rhs.data,8));
            a = _mm256_srli_epi16(_mm256_slli_epi16(a,8),8);
            b = _mm256_slli_epi16(b,8);
            return vec<int8_t,32>(_mm256_or_si256(a,b));
        }
        TSIMD_INLINE vec<int8_t,32> operator/(const vec<int8_t,32> rhs) const {
            vec<int8_t,32> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<int8_t,32> operator-() const {
            return zero()-*this;
        }
        TSIMD_INLINE vec<int8_t,32>& operator&=(const vec<int8_t,32> rhs){
            data = _mm256_and_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int8_t,32>& operator|=(const vec<int8_t,32> rhs){
            data = _mm256_or_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int8_t,32>& operator^=(const vec<int8_t,32> rhs){
            data = _mm256_xor_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int8_t,32> operator&(const vec<int8_t,32> rhs) const {
            return vec<int8_t,32>(_mm256_and_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<int8_t,32> operator|(const vec<int8_t,32> rhs) const {
            return vec<int8_t,32>(_mm256_or_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<int8_t,32> operator^(const vec<int8_t,32> rhs) const {
            return vec<int8_t,32>(_mm256_xor_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<int8_t,32> operator~() const {
            return vec<int8_t,32>(_mm256_xor_si256(data,_mm256_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<int8_t,32>& operator<<=(const int shift){
            __m256i a = _mm256_slli_epi16(data,8);
            data = _mm256_and_si256(a,_mm256_set1_epi8(0xFF<<shift));
            return *this;
        }
        TSIMD_INLINE vec<int8_t,32>& operator>>=(const int shift){
            __m256i hi = _mm256_srai_epi16(_mm256_unpackhi_epi8(data,data),shift+8);
            __m256i lo = _mm256_srai_epi16(_mm256_unpacklo_epi8(data,data),shift+8);
            data = _mm256_packs_epi16(lo,hi);
            return *this;
        }
        TSIMD_INLINE vec<int8_t,32> operator<<(const int shift) const {
            __m256i a = _mm256_slli_epi16(data,8);
            return vec<int8_t,32>(_mm256_and_si256(a,_mm256_set1_epi8(0xFF<<shift)));
        }
        TSIMD_INLINE vec<int8_t,32> operator>>(const int shift) const {
            __m256i hi = _mm256_srai_epi16(_mm256_unpackhi_epi8(data,data),shift+8);
            __m256i lo = _mm256_srai_epi16(_mm256_unpacklo_epi8(data,data),shift+8);
            return vec<int8_t,32>(_mm256_packs_epi16(lo,hi));
        }
        TSIMD_INLINE masktype operator==(const vec<int8_t,32> a) const {
            return _mm256_cmpeq_epi8(data,a.data);
        }
        TSIMD_INLINE masktype operator!=(const vec<int8_t,32> a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE masktype operator>(const vec<int8_t,32> a) const {
            return _mm256_cmpgt_epi8(data,a.data);
        }
        TSIMD_INLINE masktype operator>=(const vec<int8_t,32> a) const {
            return (*this>a)|(*this==a);
        }
        TSIMD_INLINE masktype operator<(const vec<int8_t,32> a) const {
            return a>*this;
        }
        TSIMD_INLINE masktype operator<=(const vec<int8_t,32> a) const {
            return (*this<a)|(*this==a);
        }
        TSIMD_INLINE masktype operator!() const {
            return (*this)==0;
        }
        TSIMD_INLINE bool any() const {
            return (*this!=0).any();
        }
        TSIMD_INLINE bool all() const {
            return (*this!=0).all();
        }
        TSIMD_INLINE vec<int8_t,32> max(const vec<int8_t,32> rhs) const {
            return _mm256_max_epi8(data,rhs.data);
        }
        TSIMD_INLINE vec<int8_t,32> min(const vec<int8_t,32> rhs) const {
            return _mm256_min_epi8(data,rhs.data);
        }
        __m256i data;
        enum{ size = 32 };
        enum{ bits = 256 };
        friend std::ostream& operator<<(std::ostream& out, vec<int8_t,32> v){
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

#endif //TSIMD_VEC32INT8_H
