#ifndef TSIMD_VEC2D_H
#define TSIMD_VEC2D_H

#include "../../tsimd.h"

#ifdef __SSE2__
namespace tsimd{
    template<> class vec<double,2>{
    public:
        typedef mask<128,2> masktype;
        typedef __m128d simdtype;
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(double a){ data = _mm_set_pd1(a); }
        TSIMD_INLINE explicit vec(double* a){ data = _mm_loadu_pd(a); }
        TSIMD_INLINE vec(__m128d a){ data = a; }
        TSIMD_INLINE vec(double a, double b){ data = _mm_set_pd(b,a); }
        TSIMD_INLINE void store(double* a) const { _mm_storeu_pd(a,data); }
        TSIMD_INLINE intl::ConstProxy<double,2> operator[](const std::size_t idx) const { return intl::ConstProxy<double,2>(*this,idx); }
        TSIMD_INLINE intl::AssignmentProxy<double,2> operator[](const std::size_t idx){ return intl::AssignmentProxy<double,2>(*this,idx); }
        static TSIMD_INLINE vec<double,2> zero(){ return _mm_setzero_pd(); }
        TSIMD_INLINE vec<double,2>& operator+=(const vec<double,2> rhs){
            data = _mm_add_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,2>& operator-=(const vec<double,2> rhs){
            data = _mm_sub_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,2>& operator*=(const vec<double,2> rhs){
            data = _mm_mul_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,2>& operator/=(const vec<double,2> rhs){
            data = _mm_div_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,2> operator+(const vec<double,2> rhs) const {
            return vec<double,2>(_mm_add_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,2> operator-(const vec<double,2> rhs) const {
            return vec<double,2>(_mm_sub_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,2> operator*(const vec<double,2> rhs) const {
            return vec<double,2>(_mm_mul_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,2> operator/(const vec<double,2> rhs) const {
            return vec<double,2>(_mm_div_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,2> operator-() const {
            return zero()-*this;
        }
        TSIMD_INLINE vec<double,2>& operator&=(const vec<double,2> rhs){
            data = _mm_and_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,2>& operator|=(const vec<double,2> rhs){
            data = _mm_or_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,2>& operator^=(const vec<double,2> rhs){
            data = _mm_xor_pd(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<double,2> operator&(const vec<double,2> rhs) const {
            return vec<double,2>(_mm_and_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,2> operator|(const vec<double,2> rhs) const {
            return vec<double,2>(_mm_or_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,2> operator^(const vec<double,2> rhs) const {
            return vec<double,2>(_mm_xor_pd(data,rhs.data));
        }
        TSIMD_INLINE vec<double,2> operator~() const {
            return vec<double,2>(_mm_xor_pd(data,_mm_castsi128_pd(_mm_set1_epi32(-1))));
        }
        TSIMD_INLINE masktype operator==(const vec<double,2> a) const {
            return _mm_cmpeq_pd(data,a.data);
        }
        TSIMD_INLINE masktype operator!=(const vec<double,2> a) const {
            return _mm_cmpneq_pd(data,a.data);
        }
        TSIMD_INLINE masktype operator>(const vec<double,2> a) const {
            return _mm_cmpgt_pd(data,a.data);
        }
        TSIMD_INLINE masktype operator>=(const vec<double,2> a) const {
            return _mm_cmpge_pd(data,a.data);
        }
        TSIMD_INLINE masktype operator<(const vec<double,2> a) const {
            return _mm_cmplt_pd(data,a.data);
        }
        TSIMD_INLINE masktype operator<=(const vec<double,2> a) const {
            return _mm_cmple_pd(data,a.data);
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
        TSIMD_INLINE vec<double,2> max(const vec<double,2> rhs) const {
            return _mm_max_pd(data,rhs.data);
        }
        TSIMD_INLINE vec<double,2> min(const vec<double,2> rhs) const {
            return _mm_min_pd(data,rhs.data);
        }
        __m128d data;
        enum{ size = 2 };
        enum{ bits = 128 };
        friend std::ostream& operator<<(std::ostream& out, vec<double,2> v){
            out<<v[0]<<" "<<v[1];
            return out;
        }
    };
}
#endif

#endif //TSIMD_VEC2D_H
