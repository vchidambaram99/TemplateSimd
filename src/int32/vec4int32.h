#ifndef TSIMD_VEC4INT32_H
#define TSIMD_VEC4INT32_H

#include "../../tsimd.h"

#ifdef __SSE2__
namespace TSimd{
    template<> class vec<int32_t,4>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(int32_t a){ data = _mm_set1_epi32(a); }
        TSIMD_INLINE explicit vec(int32_t* a){ data = _mm_loadu_si128((__m128i*)a); }
        TSIMD_INLINE vec(__m128i a){ data = a; }
        TSIMD_INLINE vec(int32_t a, int32_t b, int32_t c, int32_t d){ data = _mm_set_epi32(d,c,b,a); }
        TSIMD_INLINE void store(int32_t* a) const { _mm_storeu_si128((__m128i*)a,data); }
        TSIMD_INLINE intl::ConstProxy<int32_t,4> operator[](const std::size_t idx) const { return intl::ConstProxy<int32_t,4>(*this,idx); }
        TSIMD_INLINE intl::AssignmentProxy<int32_t,4> operator[](const std::size_t idx){ return intl::AssignmentProxy<int32_t,4>(*this,idx); }
        TSIMD_INLINE static vec<int32_t,4> zero(){ return _mm_setzero_si128(); }
        TSIMD_INLINE vec<int32_t,4>& operator+=(const vec<int32_t,4> rhs){
            data = _mm_add_epi32(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int32_t,4>& operator-=(const vec<int32_t,4> rhs){
            data = _mm_sub_epi32(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int32_t,4>& operator*=(const vec<int32_t,4> rhs){
            #ifdef __SSE4_1__
                data = _mm_mullo_epi32(data,rhs.data);
                return *this;
            #else
                __m128i a = _mm_mul_epu32(data,rhs.data);
                __m128i b = _mm_mul_epu32(_mm_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),_mm_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
                a = _mm_shuffle_epi32(a,_MM_SHUFFLE(3,2,2,0));
                b = _mm_shuffle_epi32(b,_MM_SHUFFLE(3,2,2,0));
                data = _mm_unpacklo_epi32(a,b);
                return *this;
            #endif
        }
        inline vec<int32_t,4>& operator/=(const vec<int32_t,4> rhs){
            __m128d loa = _mm_cvtepi32_pd(data);
            __m128d lob = _mm_cvtepi32_pd(rhs.data);
            __m128d hia = _mm_cvtepi32_pd(_mm_srli_si128(data,8));
            __m128d hib = _mm_cvtepi32_pd(_mm_srli_si128(rhs.data,8));
            loa = _mm_div_pd(loa,lob);
            hia = _mm_div_pd(hia,hib);
            __m128i lo = _mm_cvttpd_epi32(loa);
            __m128i hi = _mm_cvttpd_epi32(hia);
            data = _mm_or_si128(lo,_mm_slli_si128(hi,8));
            return *this;
        }
        TSIMD_INLINE vec<int32_t,4> operator+(const vec<int32_t,4> rhs) const {
            return vec<int32_t,4>(_mm_add_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<int32_t,4> operator-(const vec<int32_t,4> rhs) const {
            return vec<int32_t,4>(_mm_sub_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<int32_t,4> operator*(const vec<int32_t,4> rhs) const {
            #ifdef __SSE4_1__
                return vec<int32_t,4>(_mm_mullo_epi32(data,rhs.data));
            #else
                __m128i a = _mm_mul_epu32(data,rhs.data);
                __m128i b = _mm_mul_epu32(_mm_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),_mm_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
                a = _mm_shuffle_epi32(a,_MM_SHUFFLE(3,2,2,0));
                b = _mm_shuffle_epi32(b,_MM_SHUFFLE(3,2,2,0));
                return vec<int32_t,4>(_mm_unpacklo_epi32(a,b));
            #endif
        }
        TSIMD_INLINE vec<int32_t,4> operator/(const vec<int32_t,4> rhs) const {
            vec<int32_t,4> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<int32_t,4> operator-() const {
            return zero()-*this;
        }
        TSIMD_INLINE vec<int32_t,4>& operator&=(const vec<int32_t,4> rhs){
            data = _mm_and_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int32_t,4>& operator|=(const vec<int32_t,4> rhs){
            data = _mm_or_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int32_t,4>& operator^=(const vec<int32_t,4> rhs){
            data = _mm_xor_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int32_t,4> operator&(const vec<int32_t,4> rhs) const {
            return vec<int32_t,4>(_mm_and_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<int32_t,4> operator|(const vec<int32_t,4> rhs) const {
            return vec<int32_t,4>(_mm_or_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<int32_t,4> operator^(const vec<int32_t,4> rhs) const {
            return vec<int32_t,4>(_mm_xor_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<int32_t,4> operator~() const {
            return vec<int32_t,4>(_mm_xor_si128(data,_mm_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<int32_t,4>& operator<<=(const int shift){
            data = _mm_slli_epi32(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<int32_t,4>& operator>>=(const int shift){
            data = _mm_srai_epi32(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<int32_t,4> operator<<(const int shift) const {
            return vec<int32_t,4>(_mm_slli_epi32(data,shift));
        }
        TSIMD_INLINE vec<int32_t,4> operator>>(const int shift) const {
            return vec<int32_t,4>(_mm_srai_epi32(data,shift));
        }
        TSIMD_INLINE vec<int32_t,4> operator==(const vec<int32_t,4> a) const {
            return _mm_cmpeq_epi32(data,a.data);
        }
        TSIMD_INLINE vec<int32_t,4> operator!=(const vec<int32_t,4> a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE vec<int32_t,4> operator>(const vec<int32_t,4> a) const {
            return _mm_cmpgt_epi32(data,a.data);
        }
        TSIMD_INLINE vec<int32_t,4> operator>=(const vec<int32_t,4> a) const {
            return (*this>a)|(*this==a);
        }
        TSIMD_INLINE vec<int32_t,4> operator<(const vec<int32_t,4> a) const {
            return _mm_cmplt_epi32(data,a.data);
        }
        TSIMD_INLINE vec<int32_t,4> operator<=(const vec<int32_t,4> a) const {
            return (*this<a)|(*this==a);
        }
        TSIMD_INLINE vec<int32_t,4> operator!() const {
            return (*this)==0;
        }
        TSIMD_INLINE bool any() const {
            return _mm_movemask_epi8((*this!=0).data);
        }
        TSIMD_INLINE bool all() const {
            return !_mm_movemask_epi8((*this==0).data);
        }
        TSIMD_INLINE vec<int32_t,4> max(const vec<int32_t,4> rhs) const {
            #ifdef __SSE4_1__
                return _mm_max_epi32(data,rhs.data);
            #else
                return select(*this>rhs,*this,rhs);
            #endif
        }
        TSIMD_INLINE vec<int32_t,4> min(const vec<int32_t,4> rhs) const {
            #ifdef __SSE4_1__
                return _mm_min_epi32(data,rhs.data);
            #else
                return select(*this<rhs,*this,rhs);
            #endif
        }
        __m128i data;
        enum{ size = 4 };
        enum{ bits = 128 };
        friend std::ostream& operator<<(std::ostream& out, vec<int32_t, 4> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC4INT32_H
