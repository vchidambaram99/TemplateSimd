#ifndef TSIMD_VEC16C_H
#define TSIMD_VEC16C_H

#include "../../tsimd.h"

#ifdef __SSE2__
namespace TSimd{
    template<> class vec<char,16>{
    public:
        typedef mask<128> masktype;
        typedef __m128i simdtype;
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(char a){ data = _mm_set1_epi8(a); }
        TSIMD_INLINE explicit vec(char* a){ data = _mm_loadu_si128((__m128i*)a); }
        TSIMD_INLINE vec(__m128i a){ data = a; }
        TSIMD_INLINE vec(char a, char b, char c, char d, char e, char f, char g, char h, char i, char j, char k, char l, char m, char n, char o, char p){
            data = _mm_set_epi8(p,o,n,m,l,k,j,i,h,g,f,e,d,c,b,a);
        }
        TSIMD_INLINE void store(char* a) const { _mm_storeu_si128((__m128i*)a,data); }
        TSIMD_INLINE intl::ConstProxy<char,16> operator[](const std::size_t idx) const { return intl::ConstProxy<char,16>(*this,idx); }
        TSIMD_INLINE intl::AssignmentProxy<char,16> operator[](const std::size_t idx){ return intl::AssignmentProxy<char,16>(*this,idx); }
        TSIMD_INLINE static vec<char,16> zero(){ return _mm_setzero_si128(); }
        TSIMD_INLINE vec<char,16>& operator+=(const vec<char,16> rhs){
            data = _mm_add_epi8(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<char,16>& operator-=(const vec<char,16> rhs){
            data = _mm_sub_epi8(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<char,16>& operator*=(const vec<char,16> rhs){
            __m128i a = _mm_mullo_epi16(data,rhs.data);
            __m128i b = _mm_mullo_epi16(_mm_srli_epi16(data,8),_mm_srli_epi16(rhs.data,8));
            a = _mm_srli_epi16(_mm_slli_epi16(a,8),8);
            b = _mm_slli_epi16(b,8);
            data = _mm_or_si128(a,b);
            return *this;
        }
        inline vec<char,16>& operator/=(const vec<char,16> rhs){ //inefficient, but still faster than scalar
            __m128i a1 = _mm_srai_epi32(data,24);
            __m128i b1 = _mm_srai_epi32(rhs.data,24);
            __m128 a1f = _mm_cvtepi32_ps(a1);
            __m128 b1f = _mm_cvtepi32_ps(b1);
            a1 = _mm_cvttps_epi32(_mm_div_ps(a1f,b1f));
            a1 = _mm_slli_epi32(a1,24);
            __m128i a2 = _mm_srai_epi32(_mm_slli_epi32(data,8),24);
            __m128i b2 = _mm_srai_epi32(_mm_slli_epi32(rhs.data,8),24);
            __m128 a2f = _mm_cvtepi32_ps(a2);
            __m128 b2f = _mm_cvtepi32_ps(b2);
            a2 = _mm_cvttps_epi32(_mm_div_ps(a2f,b2f));
            a2 = _mm_srli_epi32(_mm_slli_epi32(a2,24),8);
            __m128i a3 = _mm_srai_epi32(_mm_slli_epi32(data,16),24);
            __m128i b3 = _mm_srai_epi32(_mm_slli_epi32(rhs.data,16),24);
            __m128 a3f = _mm_cvtepi32_ps(a3);
            __m128 b3f = _mm_cvtepi32_ps(b3);
            a3 = _mm_cvttps_epi32(_mm_div_ps(a3f,b3f));
            a3 = _mm_srli_epi32(_mm_slli_epi32(a3,24),16);
            __m128i a4 = _mm_srai_epi32(_mm_slli_epi32(data,24),24);
            __m128i b4 = _mm_srai_epi32(_mm_slli_epi32(rhs.data,24),24);
            __m128 a4f = _mm_cvtepi32_ps(a4);
            __m128 b4f = _mm_cvtepi32_ps(b4);
            a4 = _mm_cvttps_epi32(_mm_div_ps(a4f,b4f));
            a4 = _mm_srli_epi32(_mm_slli_epi32(a4,24),24);
            data = _mm_or_si128(a1,_mm_or_si128(a2,_mm_or_si128(a3,a4)));
            return *this;
        }
        TSIMD_INLINE vec<char,16> operator+(const vec<char,16> rhs) const {
            return vec<char,16>(_mm_add_epi8(data,rhs.data));
        }
        TSIMD_INLINE vec<char,16> operator-(const vec<char,16> rhs) const {
            return vec<char,16>(_mm_sub_epi8(data,rhs.data));
        }
        TSIMD_INLINE vec<char,16> operator*(const vec<char,16> rhs) const {
            __m128i a = _mm_mullo_epi16(data,rhs.data);
            __m128i b = _mm_mullo_epi16(_mm_srli_epi16(data,8),_mm_srli_epi16(rhs.data,8));
            a = _mm_srli_epi16(_mm_slli_epi16(a,8),8);
            b = _mm_slli_epi16(b,8);
            return vec<char,16>(_mm_or_si128(a,b));
        }
        TSIMD_INLINE vec<char,16> operator/(const vec<char,16> rhs) const {
            vec<char,16> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<char,16> operator-() const {
            return zero()-*this;
        }
        TSIMD_INLINE vec<char,16>& operator&=(const vec<char,16> rhs){
            data = _mm_and_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<char,16>& operator|=(const vec<char,16> rhs){
            data = _mm_or_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<char,16>& operator^=(const vec<char,16> rhs){
            data = _mm_xor_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<char,16> operator&(const vec<char,16> rhs) const {
            return vec<char,16>(_mm_and_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<char,16> operator|(const vec<char,16> rhs) const {
            return vec<char,16>(_mm_or_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<char,16> operator^(const vec<char,16> rhs) const {
            return vec<char,16>(_mm_xor_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<char,16> operator~() const {
            return vec<char,16>(_mm_xor_si128(data,_mm_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<char,16>& operator<<=(const int shift){
            __m128i a = _mm_slli_epi16(data,8);
            data = _mm_and_si128(a,_mm_set1_epi8(0xFF<<shift));
            return *this;
        }
        TSIMD_INLINE vec<char,16>& operator>>=(const int shift){
            __m128i hi = _mm_srai_epi16(_mm_unpackhi_epi8(data,data),shift+8);
            __m128i lo = _mm_srai_epi16(_mm_unpacklo_epi8(data,data),shift+8);
            data = _mm_packs_epi16(lo,hi);
            return *this;
        }
        TSIMD_INLINE vec<char,16> operator<<(const int shift) const {
            __m128i a = _mm_slli_epi16(data,8);
            return vec<char,16>(_mm_and_si128(a,_mm_set1_epi8(0xFF<<shift)));
        }
        TSIMD_INLINE vec<char,16> operator>>(const int shift) const {
            __m128i hi = _mm_srai_epi16(_mm_unpackhi_epi8(data,data),shift+8);
            __m128i lo = _mm_srai_epi16(_mm_unpacklo_epi8(data,data),shift+8);
            return vec<char,16>(_mm_packs_epi16(lo,hi));
        }
        TSIMD_INLINE masktype operator==(const vec<char,16> a) const {
            return _mm_cmpeq_epi8(data,a.data);
        }
        TSIMD_INLINE masktype operator!=(const vec<char,16> a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE masktype operator>(const vec<char,16> a) const {
            return _mm_cmpgt_epi8(data,a.data);
        }
        TSIMD_INLINE masktype operator>=(const vec<char,16> a) const {
            return (*this>a)|(*this==a);
        }
        TSIMD_INLINE masktype operator<(const vec<char,16> a) const {
            return _mm_cmplt_epi8(data,a.data);
        }
        TSIMD_INLINE masktype operator<=(const vec<char,16> a) const {
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
        TSIMD_INLINE vec<char,16> max(const vec<char,16> rhs) const {
            #ifdef __SSE4_1__
                return _mm_max_epi8(data,rhs.data);
            #else
                return select(*this>rhs,*this,rhs);
            #endif
        }
        TSIMD_INLINE vec<char,16> min(const vec<char,16> rhs) const {
            #ifdef __SSE4_1__
                return _mm_min_epi8(data,rhs.data);
            #else
                return select(*this<rhs,*this,rhs);
            #endif
        }
        __m128i data;
        enum{ size = 16 };
        enum{ bits = 128 };
        friend std::ostream& operator<<(std::ostream& out, vec<char, 16> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            out<<" "<<v[4]<<" "<<v[5]<<" "<<v[6]<<" "<<v[7];
            out<<" "<<v[8]<<" "<<v[9]<<" "<<v[10]<<" "<<v[11];
            out<<" "<<v[12]<<" "<<v[13]<<" "<<v[14]<<" "<<v[15];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC16C_H
