#ifndef TSIMD_VEC4D_H
#define TSIMD_VEC4D_H

#include "../../tsimd.h"

#ifdef __AVX__
namespace tsimd{
    template<> class vec<double,4>{
    public:
        typedef mask<256,4> masktype;
        typedef __m256d simdtype;
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(double a){ data = _mm256_set1_pd(a); }
        TSIMD_INLINE explicit vec(double* a){ data = _mm256_loadu_pd(a); }
        TSIMD_INLINE vec(__m256d a){ data = a; }
        TSIMD_INLINE vec(double a, double b, double c, double d){ data = _mm256_set_pd(d,c,b,a); }
        TSIMD_INLINE void store(double* a) const { _mm256_storeu_pd(a,data); }
        TSIMD_INLINE intl::ConstProxy<double,4> operator[](const std::size_t idx) const { return intl::ConstProxy<double,4>(*this,idx); }
        TSIMD_INLINE intl::AssignmentProxy<double,4> operator[](const std::size_t idx){ return intl::AssignmentProxy<double,4>(*this,idx); }
        static TSIMD_INLINE vec<double,4> zero(){ return _mm256_setzero_pd(); }
        TSIMD_INLINE vec<double,4>& operator+=(const vec<double,4> rhs){
            data = _mm256_add_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,4>& operator-=(const vec<double,4> rhs){
            data = _mm256_sub_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,4>& operator*=(const vec<double,4> rhs){
            data = _mm256_mul_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,4>& operator/=(const vec<double,4> rhs){
            data = _mm256_div_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,4> operator+(const vec<double,4> rhs) const {
            return vec<double,4>(_mm256_add_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,4> operator-(const vec<double,4> rhs) const {
            return vec<double,4>(_mm256_sub_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,4> operator*(const vec<double,4> rhs) const {
            return vec<double,4>(_mm256_mul_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,4> operator/(const vec<double,4> rhs) const {
            return vec<double,4>(_mm256_div_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,4> operator-() const {
            return zero()-*this;
        }
        TSIMD_INLINE vec<double,4>& operator&=(const vec<double,4> rhs){
            data = _mm256_and_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,4>& operator|=(const vec<double,4> rhs){
            data = _mm256_or_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,4>& operator^=(const vec<double,4> rhs){
            data = _mm256_xor_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,4> operator&(const vec<double,4> rhs) const {
            return vec<double,4>(_mm256_and_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,4> operator|(const vec<double,4> rhs) const {
            return vec<double,4>(_mm256_or_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,4> operator^(const vec<double,4> rhs) const {
            return vec<double,4>(_mm256_xor_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,4> operator~() const {
            return vec<double,4>(_mm256_xor_pd(data,_mm256_castsi256_pd(_mm256_set1_epi32(-1))));
        }
        //TODO add macros so that user can decide how fp comparisons should be done (ordered/not) and (signaling/not)
        TSIMD_INLINE masktype operator==(const vec<double,4> a) const {
            return _mm256_cmp_pd(data,a.data,_CMP_EQ_OQ);
        }
        TSIMD_INLINE masktype operator!=(const vec<double,4> a) const {
            return _mm256_cmp_pd(data,a.data,_CMP_NEQ_OQ);
        }
        TSIMD_INLINE masktype operator>(const vec<double,4> a) const {
            return _mm256_cmp_pd(data,a.data,_CMP_GT_OQ);
        }
        TSIMD_INLINE masktype operator>=(const vec<double,4> a) const {
            return _mm256_cmp_pd(data,a.data,_CMP_GE_OQ);
        }
        TSIMD_INLINE masktype operator<(const vec<double,4> a) const {
            return _mm256_cmp_pd(data,a.data,_CMP_LT_OQ);
        }
        TSIMD_INLINE masktype operator<=(const vec<double,4> a) const {
            return _mm256_cmp_pd(data,a.data,_CMP_LE_OQ);
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
        TSIMD_INLINE vec<double,4> max(const vec<double,4> rhs) const {
            return _mm256_max_pd(data,rhs.data);
        }
        TSIMD_INLINE vec<double,4> min(const vec<double,4> rhs) const {
            return _mm256_min_pd(data,rhs.data);
        }
        __m256d data;
        enum{ size = 4 };
        enum{ bits = 256 };
        friend std::ostream& operator<<(std::ostream& out, vec<double,4> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC4D_H
