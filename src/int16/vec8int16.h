#ifndef TSIMD_VEC8INT16_H
#define TSIMD_VEC8INT16_H

#include "../../tsimd.h"

#ifdef __SSE2__
namespace tsimd{
    template<> class vec<int16_t,8>{
    public:
        typedef mask<128,8> masktype;
        typedef __m128i simdtype;
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(int16_t a){ data = _mm_set1_epi16(a); }
        TSIMD_INLINE explicit vec(int16_t* a){ data = _mm_loadu_si128((__m128i*)a); }
        TSIMD_INLINE vec(__m128i a){ data = a; }
        TSIMD_INLINE vec(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f, int16_t g, int16_t h){
            data = _mm_set_epi16(h,g,f,e,d,c,b,a);
        }
        TSIMD_INLINE void store(int16_t* a) const { _mm_storeu_si128((__m128i*)a,data); }
        TSIMD_INLINE intl::ConstProxy<int16_t,8> operator[](const std::size_t idx) const { return intl::ConstProxy<int16_t,8>(*this,idx); }
        TSIMD_INLINE intl::AssignmentProxy<int16_t,8> operator[](const std::size_t idx){ return intl::AssignmentProxy<int16_t,8>(*this,idx); }
        TSIMD_INLINE static vec<int16_t,8> zero(){ return _mm_setzero_si128(); }
        TSIMD_INLINE vec<int16_t,8>& operator+=(const vec<int16_t,8> rhs){
            data = _mm_add_epi16(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int16_t,8>& operator-=(const vec<int16_t,8> rhs){
            data = _mm_sub_epi16(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int16_t,8>& operator*=(const vec<int16_t,8> rhs){
            data = _mm_mullo_epi16(data,rhs.data);
            return *this;
        }
        inline vec<int16_t,8>& operator/=(const vec<int16_t,8> rhs){
            __m128i signa = _mm_srai_epi16(data,15);
            __m128i signb = _mm_srai_epi16(rhs.data,15);
            __m128i loa = _mm_unpacklo_epi16(data,signa);
            __m128i lob = _mm_unpacklo_epi16(rhs.data,signb);
            __m128i hia = _mm_unpackhi_epi16(data,signa);
            __m128i hib = _mm_unpackhi_epi16(rhs.data,signb);
            __m128 loaf = _mm_cvtepi32_ps(loa);
            __m128 lobf = _mm_cvtepi32_ps(lob);
            __m128 hiaf = _mm_cvtepi32_ps(hia);
            __m128 hibf = _mm_cvtepi32_ps(hib);
            loaf = _mm_div_ps(loaf,lobf);
            hiaf = _mm_div_ps(hiaf,hibf);
            loa = _mm_cvttps_epi32(loaf);
            hia = _mm_cvttps_epi32(hiaf);
            data = _mm_packs_epi32(loa,hia);
            return *this;
        }
        TSIMD_INLINE vec<int16_t,8> operator+(const vec<int16_t,8> rhs) const {
            return vec<int16_t,8>(_mm_add_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<int16_t,8> operator-(const vec<int16_t,8> rhs) const {
            return vec<int16_t,8>(_mm_sub_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<int16_t,8> operator*(const vec<int16_t,8> rhs) const {
            return vec<int16_t,8>(_mm_mullo_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<int16_t,8> operator/(const vec<int16_t,8> rhs) const {
            vec<int16_t,8> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<int16_t,8> operator-() const {
            return zero()-*this;
        }
        TSIMD_INLINE vec<int16_t,8>& operator&=(const vec<int16_t,8> rhs){
            data = _mm_and_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int16_t,8>& operator|=(const vec<int16_t,8> rhs){
            data = _mm_or_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int16_t,8>& operator^=(const vec<int16_t,8> rhs){
            data = _mm_xor_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int16_t,8> operator&(const vec<int16_t,8> rhs) const {
            return vec<int16_t,8>(_mm_and_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<int16_t,8> operator|(const vec<int16_t,8> rhs) const {
            return vec<int16_t,8>(_mm_or_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<int16_t,8> operator^(const vec<int16_t,8> rhs) const {
            return vec<int16_t,8>(_mm_xor_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<int16_t,8> operator~() const {
            return vec<int16_t,8>(_mm_xor_si128(data,_mm_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<int16_t,8>& operator<<=(const int shift){
            data = _mm_slli_epi16(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<int16_t,8>& operator>>=(const int shift){
            data = _mm_srai_epi16(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<int16_t,8> operator<<(const int shift) const {
            return vec<int16_t,8>(_mm_slli_epi16(data,shift));
        }
        TSIMD_INLINE vec<int16_t,8> operator>>(const int shift) const {
            return vec<int16_t,8>(_mm_srai_epi16(data,shift));
        }
        TSIMD_INLINE masktype operator==(const vec<int16_t,8> a) const {
            return _mm_cmpeq_epi16(data,a.data);
        }
        TSIMD_INLINE masktype operator!=(const vec<int16_t,8> a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE masktype operator>(const vec<int16_t,8> a) const {
            return _mm_cmpgt_epi16(data,a.data);
        }
        TSIMD_INLINE masktype operator>=(const vec<int16_t,8> a) const {
            return (*this>a)|(*this==a);
        }
        TSIMD_INLINE masktype operator<(const vec<int16_t,8> a) const {
            return _mm_cmplt_epi16(data,a.data);
        }
        TSIMD_INLINE masktype operator<=(const vec<int16_t,8> a) const {
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
        TSIMD_INLINE vec<int16_t,8> max(const vec<int16_t,8> rhs) const {
            return _mm_max_epi16(data,rhs.data);
        }
        TSIMD_INLINE vec<int16_t,8> min(const vec<int16_t,8> rhs) const {
            return _mm_min_epi16(data,rhs.data);
        }
        __m128i data;
        enum{ size = 8 };
        enum{ bits = 128 };
        friend std::ostream& operator<<(std::ostream& out, vec<int16_t,8> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            out<<" "<<v[4]<<" "<<v[5]<<" "<<v[6]<<" "<<v[7];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC8INT16_H
