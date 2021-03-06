#ifndef TSIMD_VEC16UINT8_H
#define TSIMD_VEC16UINT8_H

#include "../../tsimd.h"

#ifdef __SSE2__
namespace tsimd{
    template<> class vec<uint8_t,16>{
    public:
        typedef mask<128,16> masktype;
        typedef __m128i simdtype;
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(uint8_t a){ data = _mm_set1_epi8(a); }
        TSIMD_INLINE explicit vec(uint8_t* a){ data = _mm_loadu_si128((__m128i*)a); }
        TSIMD_INLINE vec(__m128i a){ data = a; }
        TSIMD_INLINE vec(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint8_t h, uint8_t i, uint8_t j, uint8_t k, uint8_t l, uint8_t m, uint8_t n, uint8_t o, uint8_t p){
            data = _mm_set_epi8(p,o,n,m,l,k,j,i,h,g,f,e,d,c,b,a);
        }
        TSIMD_INLINE void store(uint8_t* a) const { _mm_storeu_si128((__m128i*)a,data); }
        TSIMD_INLINE intl::ConstProxy<uint8_t,16> operator[](const std::size_t idx) const { return intl::ConstProxy<uint8_t,16>(*this,idx); }
        TSIMD_INLINE intl::AssignmentProxy<uint8_t,16> operator[](const std::size_t idx){ return intl::AssignmentProxy<uint8_t,16>(*this,idx); }
        TSIMD_INLINE static vec<uint8_t,16> zero(){ return _mm_setzero_si128(); }
        TSIMD_INLINE vec<uint8_t,16>& operator+=(const vec<uint8_t,16> rhs){
            data = _mm_add_epi8(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,16>& operator-=(const vec<uint8_t,16> rhs){
            data = _mm_sub_epi8(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,16>& operator*=(const vec<uint8_t,16> rhs){
            __m128i a = _mm_mullo_epi16(data,rhs.data);
            __m128i b = _mm_mullo_epi16(_mm_srli_epi16(data,8),_mm_srli_epi16(rhs.data,8));
            a = _mm_srli_epi16(_mm_slli_epi16(a,8),8);
            b = _mm_slli_epi16(b,8);
            data = _mm_or_si128(a,b);
            return *this;
        }
        inline vec<uint8_t,16>& operator/=(const vec<uint8_t,16> rhs){ //this seems like a lot, but its faster than scalar
            __m128i zero = _mm_setzero_si128();
            __m128i loa = _mm_unpacklo_epi8(data,zero);
            __m128i lob = _mm_unpacklo_epi8(rhs.data,zero);
            __m128i lloa = _mm_unpacklo_epi8(loa,zero);
            __m128i llob = _mm_unpacklo_epi8(lob,zero);
            __m128i hloa = _mm_unpackhi_epi8(loa,zero);
            __m128i hlob = _mm_unpackhi_epi8(lob,zero);
            __m128 lloaf = _mm_cvtepi32_ps(lloa);
            __m128 llobf = _mm_cvtepi32_ps(llob);
            __m128 hloaf = _mm_cvtepi32_ps(hloa);
            __m128 hlobf = _mm_cvtepi32_ps(hlob);
            lloaf = _mm_div_ps(lloaf,llobf);
            hloaf = _mm_div_ps(hloaf,hlobf);
            lloa = _mm_cvttps_epi32(lloaf);
            hloa = _mm_cvttps_epi32(hloaf);
            loa = _mm_packs_epi32(lloa,hloa);
            __m128i hia = _mm_unpackhi_epi8(data,zero);
            __m128i hib = _mm_unpackhi_epi8(rhs.data,zero);
            __m128i lhia = _mm_unpacklo_epi8(hia,zero);
            __m128i lhib = _mm_unpacklo_epi8(hib,zero);
            __m128i hhia = _mm_unpackhi_epi8(hia,zero);
            __m128i hhib = _mm_unpackhi_epi8(hib,zero);
            __m128 lhiaf = _mm_cvtepi32_ps(lhia);
            __m128 lhibf = _mm_cvtepi32_ps(lhib);
            __m128 hhiaf = _mm_cvtepi32_ps(hhia);
            __m128 hhibf = _mm_cvtepi32_ps(hhib);
            lhiaf = _mm_div_ps(lhiaf,lhibf);
            hhiaf = _mm_div_ps(hhiaf,hhibf);
            lhia = _mm_cvttps_epi32(lhiaf);
            hhia = _mm_cvttps_epi32(hhiaf);
            hia = _mm_packs_epi32(lhia,hhia);
            data = _mm_packus_epi16(loa,hia);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,16> operator+(const vec<uint8_t,16> rhs) const {
            return vec<uint8_t,16>(_mm_add_epi8(data,rhs.data));
        }
        TSIMD_INLINE vec<uint8_t,16> operator-(const vec<uint8_t,16> rhs) const {
            return vec<uint8_t,16>(_mm_sub_epi8(data,rhs.data));
        }
        TSIMD_INLINE vec<uint8_t,16> operator*(const vec<uint8_t,16> rhs) const {
            __m128i a = _mm_mullo_epi16(data,rhs.data);
            __m128i b = _mm_mullo_epi16(_mm_srli_epi16(data,8),_mm_srli_epi16(rhs.data,8));
            a = _mm_srli_epi16(_mm_slli_epi16(a,8),8);
            b = _mm_slli_epi16(b,8);
            return vec<uint8_t,16>(_mm_or_si128(a,b));
        }
        TSIMD_INLINE vec<uint8_t,16> operator/(const vec<uint8_t,16> rhs) const {
            vec<uint8_t,16> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<uint8_t,16> operator-() const {
            return zero()-*this;
        }
        TSIMD_INLINE vec<uint8_t,16>& operator&=(const vec<uint8_t,16> rhs){
            data = _mm_and_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,16>& operator|=(const vec<uint8_t,16> rhs){
            data = _mm_or_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,16>& operator^=(const vec<uint8_t,16> rhs){
            data = _mm_xor_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,16> operator&(const vec<uint8_t,16> rhs) const {
            return vec<uint8_t,16>(_mm_and_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<uint8_t,16> operator|(const vec<uint8_t,16> rhs) const {
            return vec<uint8_t,16>(_mm_or_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<uint8_t,16> operator^(const vec<uint8_t,16> rhs) const {
            return vec<uint8_t,16>(_mm_xor_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<uint8_t,16> operator~() const {
            return vec<uint8_t,16>(_mm_xor_si128(data,_mm_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<uint8_t,16>& operator<<=(const int shift){
            __m128i a = _mm_slli_epi16(data,8);
            data = _mm_and_si128(a,_mm_set1_epi8(0xFF<<shift));
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,16>& operator>>=(const int shift){
            __m128i a = _mm_srli_epi16(data,shift);
            data = _mm_and_si128(a,_mm_set1_epi8(((unsigned int)(0xFF))>>shift));
            return *this;
        }
        TSIMD_INLINE vec<uint8_t,16> operator<<(const int shift) const {
            __m128i a = _mm_slli_epi16(data,8);
            return vec<uint8_t,16>(_mm_and_si128(a,_mm_set1_epi8(0xFF<<shift)));
        }
        TSIMD_INLINE vec<uint8_t,16> operator>>(const int shift) const {
            __m128i a = _mm_srli_epi16(data,shift);
            return vec<uint8_t,16>(_mm_and_si128(a,_mm_set1_epi8(((unsigned int)(0xFF))>>shift)));
        }
        TSIMD_INLINE masktype operator==(const vec<uint8_t,16> a) const {
            return _mm_cmpeq_epi8(data,a.data);
        }
        TSIMD_INLINE masktype operator!=(const vec<uint8_t,16> a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE masktype operator>(const vec<uint8_t,16> a) const {
            return ~(*this<=a);
        }
        TSIMD_INLINE masktype operator>=(const vec<uint8_t,16> a) const {
            return (*this)==_mm_max_epu8(data,a.data);
        }
        TSIMD_INLINE masktype operator<(const vec<uint8_t,16> a) const {
            return a>*this;
        }
        TSIMD_INLINE masktype operator<=(const vec<uint8_t,16> a) const {
            return (*this)==_mm_min_epu8(data,a.data);
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
        TSIMD_INLINE vec<uint8_t,16> max(const vec<uint8_t,16> rhs) const {
            return _mm_max_epu8(data,rhs.data);
        }
        TSIMD_INLINE vec<uint8_t,16> min(const vec<uint8_t,16> rhs) const {
            return _mm_min_epu8(data,rhs.data);
        }
        __m128i data;
        enum{ size = 16 };
        enum{ bits = 128 };
        friend std::ostream& operator<<(std::ostream& out, vec<uint8_t, 16> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            out<<" "<<v[4]<<" "<<v[5]<<" "<<v[6]<<" "<<v[7];
            out<<" "<<v[8]<<" "<<v[9]<<" "<<v[10]<<" "<<v[11];
            out<<" "<<v[12]<<" "<<v[13]<<" "<<v[14]<<" "<<v[15];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC16UINT8_H
