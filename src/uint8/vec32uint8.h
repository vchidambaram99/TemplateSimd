#ifndef TSIMD_VEC32UINT8_H
#define TSIMD_VEC32UINT8_H

#include "../../tsimd.h"

#ifdef __AVX2__
namespace tsimd{
    template<> class vec<uint8_t,32>{
    public:
        typedef mask<256,32> masktype;
        typedef __m256i simdtype;
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(uint8_t a){ data = _mm256_set1_epi8(a); }
        TSIMD_INLINE explicit vec(uint8_t* a){ data = _mm256_loadu_si256((__m256i*)a); }
        TSIMD_INLINE vec(__m256i a){ data = a; }
        TSIMD_INLINE vec(uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4, uint8_t a5, uint8_t a6, uint8_t a7, uint8_t a8, uint8_t a9, uint8_t a10, uint8_t a11, uint8_t a12, uint8_t a13, uint8_t a14, uint8_t a15, uint8_t a16,
                         uint8_t a17, uint8_t a18, uint8_t a19, uint8_t a20, uint8_t a21, uint8_t a22, uint8_t a23, uint8_t a24, uint8_t a25, uint8_t a26, uint8_t a27, uint8_t a28, uint8_t a29, uint8_t a30, uint8_t a31){
            data = _mm256_set_epi8(a31,a30,a29,a28,a27,a26,a25,a24,a23,a22,a21,a20,a19,a18,a17,a16,a15,a14,a13,a12,a11,a10,a9,a8,a7,a6,a5,a4,a3,a2,a1,a0);
        }
        TSIMD_INLINE void store(uint8_t* a) const { _mm256_storeu_si256((__m256i*)a,data); }
        TSIMD_INLINE intl::ConstProxy<uint8_t,32> operator[](const std::size_t idx) const { return intl::ConstProxy<uint8_t,32>(*this,idx); }
        TSIMD_INLINE intl::AssignmentProxy<uint8_t,32> operator[](const std::size_t idx){ return intl::AssignmentProxy<uint8_t,32>(*this,idx); }
        TSIMD_INLINE static vec<uint8_t,32> zero(){ return _mm256_setzero_si256(); }
        TSIMD_INLINE vec<uint8_t,32>& operator+=(const vec<uint8_t,32> rhs){
            data = _mm256_add_epi8(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,32>& operator-=(const vec<uint8_t,32> rhs){
            data = _mm256_sub_epi8(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,32>& operator*=(const vec<uint8_t,32> rhs){
            __m256i a = _mm256_mullo_epi16(data,rhs.data);
            __m256i b = _mm256_mullo_epi16(_mm256_srli_epi16(data,8),_mm256_srli_epi16(rhs.data,8));
            a = _mm256_srli_epi16(_mm256_slli_epi16(a,8),8);
            b = _mm256_slli_epi16(b,8);
            data = _mm256_or_si256(a,b);
            return *this;
        }
        inline vec<uint8_t,32>& operator/=(const vec<uint8_t,32> rhs){ //this seems like a lot, but its faster than scalar
            __m256i zero = _mm256_setzero_si256();
            __m256i loa = _mm256_unpacklo_epi8(data,zero);
            __m256i lob = _mm256_unpacklo_epi8(rhs.data,zero);
            __m256i lloa = _mm256_unpacklo_epi8(loa,zero);
            __m256i llob = _mm256_unpacklo_epi8(lob,zero);
            __m256i hloa = _mm256_unpackhi_epi8(loa,zero);
            __m256i hlob = _mm256_unpackhi_epi8(lob,zero);
            __m256 lloaf = _mm256_cvtepi32_ps(lloa);
            __m256 llobf = _mm256_cvtepi32_ps(llob);
            __m256 hloaf = _mm256_cvtepi32_ps(hloa);
            __m256 hlobf = _mm256_cvtepi32_ps(hlob);
            lloaf = _mm256_div_ps(lloaf,llobf);
            hloaf = _mm256_div_ps(hloaf,hlobf);
            lloa = _mm256_cvttps_epi32(lloaf);
            hloa = _mm256_cvttps_epi32(hloaf);
            loa = _mm256_packs_epi32(lloa,hloa);
            __m256i hia = _mm256_unpackhi_epi8(data,zero);
            __m256i hib = _mm256_unpackhi_epi8(rhs.data,zero);
            __m256i lhia = _mm256_unpacklo_epi8(hia,zero);
            __m256i lhib = _mm256_unpacklo_epi8(hib,zero);
            __m256i hhia = _mm256_unpackhi_epi8(hia,zero);
            __m256i hhib = _mm256_unpackhi_epi8(hib,zero);
            __m256 lhiaf = _mm256_cvtepi32_ps(lhia);
            __m256 lhibf = _mm256_cvtepi32_ps(lhib);
            __m256 hhiaf = _mm256_cvtepi32_ps(hhia);
            __m256 hhibf = _mm256_cvtepi32_ps(hhib);
            lhiaf = _mm256_div_ps(lhiaf,lhibf);
            hhiaf = _mm256_div_ps(hhiaf,hhibf);
            lhia = _mm256_cvttps_epi32(lhiaf);
            hhia = _mm256_cvttps_epi32(hhiaf);
            hia = _mm256_packs_epi32(lhia,hhia);
            data = _mm256_packus_epi16(loa,hia);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,32> operator+(const vec<uint8_t,32> rhs) const {
            return vec<uint8_t,32>(_mm256_add_epi8(data,rhs.data));
        }
        TSIMD_INLINE vec<uint8_t,32> operator-(const vec<uint8_t,32> rhs) const {
            return vec<uint8_t,32>(_mm256_sub_epi8(data,rhs.data));
        }
        TSIMD_INLINE vec<uint8_t,32> operator*(const vec<uint8_t,32> rhs) const {
            __m256i a = _mm256_mullo_epi16(data,rhs.data);
            __m256i b = _mm256_mullo_epi16(_mm256_srli_epi16(data,8),_mm256_srli_epi16(rhs.data,8));
            a = _mm256_srli_epi16(_mm256_slli_epi16(a,8),8);
            b = _mm256_slli_epi16(b,8);
            return vec<uint8_t,32>(_mm256_or_si256(a,b));
        }
        TSIMD_INLINE vec<uint8_t,32> operator/(const vec<uint8_t,32> rhs) const {
            vec<uint8_t,32> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<uint8_t,32> operator-() const {
            return zero()-*this;
        }
        TSIMD_INLINE vec<uint8_t,32>& operator&=(const vec<uint8_t,32> rhs){
            data = _mm256_and_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,32>& operator|=(const vec<uint8_t,32> rhs){
            data = _mm256_or_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,32>& operator^=(const vec<uint8_t,32> rhs){
            data = _mm256_xor_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,32> operator&(const vec<uint8_t,32> rhs) const {
            return vec<uint8_t,32>(_mm256_and_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<uint8_t,32> operator|(const vec<uint8_t,32> rhs) const {
            return vec<uint8_t,32>(_mm256_or_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<uint8_t,32> operator^(const vec<uint8_t,32> rhs) const {
            return vec<uint8_t,32>(_mm256_xor_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<uint8_t,32> operator~() const {
            return vec<uint8_t,32>(_mm256_xor_si256(data,_mm256_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<uint8_t,32>& operator<<=(const int shift){
            __m256i a = _mm256_slli_epi16(data,8);
            data = _mm256_and_si256(a,_mm256_set1_epi8(0xFF<<shift));
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,32>& operator>>=(const int shift){
            __m256i a = _mm256_srli_epi16(data,shift);
            data = _mm256_and_si256(a,_mm256_set1_epi8(((unsigned int)(0xFF))>>shift));
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,32> operator<<(const int shift) const {
            __m256i a = _mm256_slli_epi16(data,8);
            return vec<uint8_t,32>(_mm256_and_si256(a,_mm256_set1_epi8(0xFF<<shift)));
        }
        TSIMD_INLINE vec<uint8_t,32> operator>>(const int shift) const {
            __m256i a = _mm256_srli_epi16(data,shift);
            return vec<uint8_t,32>(_mm256_and_si256(a,_mm256_set1_epi8(((unsigned int)(0xFF))>>shift)));
        }
        TSIMD_INLINE masktype operator==(const vec<uint8_t,32> a) const {
            return _mm256_cmpeq_epi8(data,a.data);
        }
        TSIMD_INLINE masktype operator!=(const vec<uint8_t,32> a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE masktype operator>(const vec<uint8_t,32> a) const {
            return ~(*this<=a);
        }
        TSIMD_INLINE masktype operator>=(const vec<uint8_t,32> a) const {
            return (*this)==_mm256_max_epu8(data,a.data);
        }
        TSIMD_INLINE masktype operator<(const vec<uint8_t,32> a) const {
            return a>*this;
        }
        TSIMD_INLINE masktype operator<=(const vec<uint8_t,32> a) const {
            return (*this)==_mm256_min_epu8(data,a.data);
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
        TSIMD_INLINE vec<uint8_t,32> max(const vec<uint8_t,32> rhs) const {
            return _mm256_max_epu8(data,rhs.data);
        }
        TSIMD_INLINE vec<uint8_t,32> min(const vec<uint8_t,32> rhs) const {
            return _mm256_min_epu8(data,rhs.data);
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
