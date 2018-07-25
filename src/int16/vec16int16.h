#ifndef TSIMD_VEC16INT16_H
#define TSIMD_VEC16INT16_H

#include "../../tsimd.h"

#ifdef __AVX2__
namespace TSimd{
    template<> class vec<int16_t,16>{
    public:
        typedef mask<256> masktype;
        typedef __m256i simdtype;
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(int16_t a){ data = _mm256_set1_epi16(a); }
        TSIMD_INLINE explicit vec(int16_t* a){ data = _mm256_loadu_si256((__m256i*)a); }
        TSIMD_INLINE vec(__m256i a){ data = a; }
        TSIMD_INLINE vec(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f, int16_t g, int16_t h, int16_t i, int16_t j, int16_t k, int16_t l, int16_t m, int16_t n, int16_t o, int16_t p){
            data = _mm256_set_epi16(p,o,n,m,l,k,j,i,h,g,f,e,d,c,b,a);
        }
        TSIMD_INLINE void store(int16_t* a) const { _mm256_storeu_si256((__m256i*)a,data); }
        TSIMD_INLINE intl::ConstProxy<int16_t,16> operator[](const std::size_t idx) const { return intl::ConstProxy<int16_t,16>(*this,idx); }
        TSIMD_INLINE intl::AssignmentProxy<int16_t,16> operator[](const std::size_t idx){ return intl::AssignmentProxy<int16_t,16>(*this,idx); }
        TSIMD_INLINE static vec<int16_t,16> zero(){ return _mm256_setzero_si256(); }
        TSIMD_INLINE vec<int16_t,16>& operator+=(const vec<int16_t,16> rhs){
            data = _mm256_add_epi16(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int16_t,16>& operator-=(const vec<int16_t,16> rhs){
            data = _mm256_sub_epi16(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int16_t,16>& operator*=(const vec<int16_t,16> rhs){
            data = _mm256_mullo_epi16(data,rhs.data);
            return *this;
        }
        inline vec<int16_t,16>& operator/=(const vec<int16_t,16> rhs){
            __m256i signa = _mm256_srai_epi16(data,15);
            __m256i signb = _mm256_srai_epi16(rhs.data,15);
            __m256i loa = _mm256_unpacklo_epi16(data,signa);
            __m256i lob = _mm256_unpacklo_epi16(rhs.data,signb);
            __m256i hia = _mm256_unpackhi_epi16(data,signa);
            __m256i hib = _mm256_unpackhi_epi16(rhs.data,signb);
            __m256 loaf = _mm256_cvtepi32_ps(loa);
            __m256 lobf = _mm256_cvtepi32_ps(lob);
            __m256 hiaf = _mm256_cvtepi32_ps(hia);
            __m256 hibf = _mm256_cvtepi32_ps(hib);
            loaf = _mm256_div_ps(loaf,lobf);
            hiaf = _mm256_div_ps(hiaf,hibf);
            loa = _mm256_cvttps_epi32(loaf);
            hia = _mm256_cvttps_epi32(hiaf);
            data = _mm256_packs_epi32(loa,hia);
            return *this;
        }
        TSIMD_INLINE vec<int16_t,16> operator+(const vec<int16_t,16> rhs) const {
            return vec<int16_t,16>(_mm256_add_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<int16_t,16> operator-(const vec<int16_t,16> rhs) const {
            return vec<int16_t,16>(_mm256_sub_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<int16_t,16> operator*(const vec<int16_t,16> rhs) const {
            return vec<int16_t,16>(_mm256_mullo_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<int16_t,16> operator/(const vec<int16_t,16> rhs) const {
            vec<int16_t,16> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<int16_t,16> operator-() const {
            return zero()-*this;
        }
        TSIMD_INLINE vec<int16_t,16>& operator&=(const vec<int16_t,16> rhs){
            data = _mm256_and_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int16_t,16>& operator|=(const vec<int16_t,16> rhs){
            data = _mm256_or_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int16_t,16>& operator^=(const vec<int16_t,16> rhs){
            data = _mm256_xor_si256(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<int16_t,16> operator&(const vec<int16_t,16> rhs) const {
            return vec<int16_t,16>(_mm256_and_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<int16_t,16> operator|(const vec<int16_t,16> rhs) const {
            return vec<int16_t,16>(_mm256_or_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<int16_t,16> operator^(const vec<int16_t,16> rhs) const {
            return vec<int16_t,16>(_mm256_xor_si256(data,rhs.data));
        }
        TSIMD_INLINE vec<int16_t,16> operator~() const {
            return vec<int16_t,16>(_mm256_xor_si256(data,_mm256_set1_epi32(-1)));
        }
        TSIMD_INLINE vec<int16_t,16>& operator<<=(const int shift){
            data = _mm256_slli_epi16(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<int16_t,16>& operator>>=(const int shift){
            data = _mm256_srai_epi16(data,shift);
            return *this;
        }
        TSIMD_INLINE vec<int16_t,16> operator<<(const int shift) const {
            return vec<int16_t,16>(_mm256_slli_epi16(data,shift));
        }
        TSIMD_INLINE vec<int16_t,16> operator>>(const int shift) const {
            return vec<int16_t,16>(_mm256_srai_epi16(data,shift));
        }
        TSIMD_INLINE masktype operator==(const vec<int16_t,16> a) const {
            return _mm256_cmpeq_epi16(data,a.data);
        }
        TSIMD_INLINE masktype operator!=(const vec<int16_t,16> a) const {
            return ~(*this==a);
        }
        TSIMD_INLINE masktype operator>(const vec<int16_t,16> a) const {
            return _mm256_cmpgt_epi16(data,a.data);
        }
        TSIMD_INLINE masktype operator>=(const vec<int16_t,16> a) const {
            return (*this>a)|(*this==a);
        }
        TSIMD_INLINE masktype operator<(const vec<int16_t,16> a) const {
            return a>*this;
        }
        TSIMD_INLINE masktype operator<=(const vec<int16_t,16> a) const {
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
        TSIMD_INLINE vec<int16_t,16> max(const vec<int16_t,16> rhs) const {
            return _mm256_max_epi16(data,rhs.data);
        }
        TSIMD_INLINE vec<int16_t,16> min(const vec<int16_t,16> rhs) const {
            return _mm256_min_epi16(data,rhs.data);
        }
        __m256i data;
        enum{ size = 16 };
        enum{ bits = 256 };
        friend std::ostream& operator<<(std::ostream& out, vec<int16_t,16> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            out<<" "<<v[4]<<" "<<v[5]<<" "<<v[6]<<" "<<v[7];
            out<<" "<<v[8]<<" "<<v[9]<<" "<<v[10]<<" "<<v[11];
            out<<" "<<v[12]<<" "<<v[13]<<" "<<v[14]<<" "<<v[15];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC16INT16_H
