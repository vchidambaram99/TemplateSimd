#ifndef TSIMD_VEC8UINT16_H
#define TSIMD_VEC8UINT16_H

#include "../../tsimd.h"

#ifdef __SSE2__
namespace TSimd{
    template<> class vec<uint16_t,8>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(uint16_t a){ data = _mm_set1_epi16(a); }
        TSIMD_INLINE explicit vec(uint16_t* a){ data = _mm_loadu_si128((__m128i*)a); }
        TSIMD_INLINE vec(__m128i a){ data = a; }
        TSIMD_INLINE vec(uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e, uint16_t f, uint16_t g, uint16_t h){
            data = _mm_set_epi16(h,g,f,e,d,c,b,a);
        }
        TSIMD_INLINE void store(uint16_t* a) const { _mm_storeu_si128((__m128i*)a,data); }
        TSIMD_INLINE intl::ConstProxy<uint16_t,8> operator[](const std::size_t idx) const { return intl::ConstProxy<uint16_t,8>(*this,idx); }
        TSIMD_INLINE intl::AssignmentProxy<uint16_t,8> operator[](const std::size_t idx){ return intl::AssignmentProxy<uint16_t,8>(*this,idx); }
        TSIMD_INLINE static vec<uint16_t,8> zero(){ return _mm_setzero_si128(); }
        TSIMD_INLINE vec<uint16_t,8>& operator+=(const vec<uint16_t,8> rhs){
            data = _mm_add_epi16(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint16_t,8>& operator-=(const vec<uint16_t,8> rhs){
            data = _mm_sub_epi16(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint16_t,8>& operator*=(const vec<uint16_t,8> rhs){
            data = _mm_mullo_epi16(data,rhs.data);
            return *this;
        }
        inline vec<uint16_t,8>& operator/=(const vec<uint16_t,8> rhs){
            __m128i zero = _mm_setzero_si128();
            __m128i loa = _mm_unpacklo_epi16(data,zero);
            __m128i lob = _mm_unpacklo_epi16(rhs.data,zero);
            __m128i hia = _mm_unpackhi_epi16(data,zero);
            __m128i hib = _mm_unpackhi_epi16(rhs.data,zero);
            __m128 loaf = _mm_cvtepi32_ps(loa);
            __m128 lobf = _mm_cvtepi32_ps(lob);
            __m128 hiaf = _mm_cvtepi32_ps(hia);
            __m128 hibf = _mm_cvtepi32_ps(hib);
            loaf = _mm_div_ps(loaf,lobf);
            hiaf = _mm_div_ps(hiaf,hibf);
            loa = _mm_cvttps_epi32(loaf);
            hia = _mm_cvttps_epi32(hiaf);
            #ifdef __SSE4_1__
                data = _mm_packus_epi32(loa,hia);
            #else
                loa = _mm_slli_epi32(loa,16);
                loa = _mm_srai_epi32(loa,16);
                hia = _mm_slli_epi32(hia,16);
                hia = _mm_srai_epi32(hia,16);
                data = _mm_packs_epi32(loa,hia);
            #endif
            return *this;
        }
        TSIMD_INLINE vec<uint16_t,8> operator+(const vec<uint16_t,8> rhs) const {
            return vec<uint16_t,8>(_mm_add_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<uint16_t,8> operator-(const vec<uint16_t,8> rhs) const {
            return vec<uint16_t,8>(_mm_sub_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<uint16_t,8> operator*(const vec<uint16_t,8> rhs) const {
            return vec<uint16_t,8>(_mm_mullo_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<uint16_t,8> operator/(const vec<uint16_t,8> rhs) const {
            vec<uint16_t,8> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<uint16_t,8> operator-() const {
            return zero()-*this;
        }
        TSIMD_INLINE vec<uint16_t,8>& operator&=(const vec<uint16_t,8> rhs){
            data = _mm_and_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint16_t,8>& operator|=(const vec<uint16_t,8> rhs){
            data = _mm_or_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint16_t,8>& operator^=(const vec<uint16_t,8> rhs){
            data = _mm_xor_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<uint16_t,8> operator&(const vec<uint16_t,8> rhs) const {
            return vec<uint16_t,8>(_mm_and_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<uint16_t,8> operator|(const vec<uint16_t,8> rhs) const {
            return vec<uint16_t,8>(_mm_or_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<uint16_t,8> operator^(const vec<uint16_t,8> rhs) const {
            return vec<uint16_t,8>(_mm_xor_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<uint16_t,8> operator~() const {
            return vec<uint16_t,8>(_mm_xor_si128(data,_mm_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<uint16_t,8>& operator<<=(const int shift){
            data = _mm_slli_epi16(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<uint16_t,8>& operator>>=(const int shift){
            data = _mm_srli_epi16(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<uint16_t,8> operator<<(const int shift) const {
            return vec<uint16_t,8>(_mm_slli_epi16(data,shift));
        }
        TSIMD_INLINE vec<uint16_t,8> operator>>(const int shift) const {
            return vec<uint16_t,8>(_mm_srli_epi16(data,shift));
        }
        TSIMD_INLINE vec<uint16_t,8> operator==(const vec<uint16_t,8> a) const {
            return _mm_cmpeq_epi16(data,a.data);
        }
        TSIMD_INLINE vec<uint16_t,8> operator!=(const vec<uint16_t,8> a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE vec<uint16_t,8> operator>(const vec<uint16_t,8> a) const {
            return ~(*this<=a);
        }
        TSIMD_INLINE vec<uint16_t,8> operator>=(const vec<uint16_t,8> a) const {
            #ifdef __SSE4_1__
                return (*this)==_mm_max_epu16(data,a.data);
            #else
                __m128i sgte = _mm_cmpgt_epi16(data,a.data);
                __m128i lz = _mm_srai_epi16(data,15);
                __m128i lza = _mm_srai_epi16(a.data,15);
                sgte = _mm_xor_si128(sgte,_mm_xor_si128(lz,lza));
                return _mm_or_si128(sgte,_mm_cmpeq_epi16(data,a.data));
            #endif
        }
        TSIMD_INLINE vec<uint16_t,8> operator<(const vec<uint16_t,8> a) const {
            return a>*this;
        }
        TSIMD_INLINE vec<uint16_t,8> operator<=(const vec<uint16_t,8> a) const {
            #ifdef __SSE4_1__
                return (*this)==_mm_min_epu16(data,a.data);
            #else
                return a>=*this;
            #endif
        }
        TSIMD_INLINE vec<uint16_t,8> operator!() const {
            return (*this)==0;
        }
        TSIMD_INLINE bool any() const {
            return _mm_movemask_epi8((*this!=0).data);
        }
        TSIMD_INLINE bool all() const {
            return !_mm_movemask_epi8((*this==0).data);
        }
        TSIMD_INLINE vec<uint16_t,8> max(const vec<uint16_t,8> rhs) const {
            #ifdef __SSE4_1__
                return _mm_max_epu16(data,rhs.data);
            #else
                return select(*this>rhs,*this,rhs);
            #endif
        }
        TSIMD_INLINE vec<uint16_t,8> min(const vec<uint16_t,8> rhs) const {
            #ifdef __SSE4_1__
                return _mm_min_epu16(data,rhs.data);
            #else
                return select(*this<rhs,*this,rhs);
            #endif
        }
        __m128i data;
        enum{ size = 8 };
        enum{ bits = 128 };
        friend std::ostream& operator<<(std::ostream& out, vec<uint16_t,8> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            out<<" "<<v[4]<<" "<<v[5]<<" "<<v[6]<<" "<<v[7];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC8UINT16_H
