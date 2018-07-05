#ifndef VEC2UL_H
#define VEC2UL_H

#ifdef __SSE2__
namespace TSimd{
    template<> class vec<unsigned long,2>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(unsigned long a){ data = _mm_set1_epi64x(a); }
        TSIMD_INLINE vec(unsigned long* a){ data = _mm_loadu_si128((__m128i*)a); }
        TSIMD_INLINE vec(__m128i a){ data = a; }
        TSIMD_INLINE vec(unsigned long a, unsigned long b){ data = _mm_set_epi64x(b,a); }
        TSIMD_INLINE void store(unsigned long* a){ _mm_storeu_si128((__m128i*)a,data); }
        TSIMD_INLINE unsigned long& operator[](int idx){ return ((unsigned long*)(&data))[idx]; }
        TSIMD_INLINE const unsigned long& operator[](int idx) const { return ((unsigned long*)(&data))[idx]; }
        TSIMD_INLINE vec<unsigned long,2>& operator+=(const vec<unsigned long,2>& rhs){
            data = _mm_add_epi64(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned long,2>& operator-=(const vec<unsigned long,2>& rhs){
            data = _mm_sub_epi64(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned long,2>& operator*=(const vec<unsigned long,2>& rhs){
            __m128i a = _mm_mul_epu32(data,rhs.data);
            __m128i b = _mm_mul_epu32(_mm_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),rhs.data);
            __m128i c = _mm_mul_epu32(data,_mm_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
            b = _mm_slli_epi64(b,32);
            c = _mm_slli_epi64(c,32);
            data = _mm_add_epi64(a,_mm_add_epi64(b,c));
            return *this;
        }
        inline vec<unsigned long,2>& operator/=(const vec<unsigned long,2>& rhs){ //TODO find simd integer division algorithm
            (*this)[0]/=rhs[0];
            (*this)[1]/=rhs[1];
            return *this;
        }
        TSIMD_INLINE vec<unsigned long,2> operator+(const vec<unsigned long,2>& rhs) const {
            return vec<unsigned long,2>(_mm_add_epi64(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned long,2> operator-(const vec<unsigned long,2>& rhs) const {
            return vec<unsigned long,2>(_mm_sub_epi64(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned long,2> operator*(const vec<unsigned long,2>& rhs) const {
            __m128i a = _mm_mul_epu32(data,rhs.data);
            __m128i b = _mm_mul_epu32(_mm_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),rhs.data);
            __m128i c = _mm_mul_epu32(data,_mm_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
            b = _mm_slli_epi64(b,32);
            c = _mm_slli_epi64(c,32);
            return vec<unsigned long,2>(_mm_add_epi64(a,_mm_add_epi64(b,c)));
        }
        TSIMD_INLINE vec<unsigned long,2> operator/(const vec<unsigned long,2>& rhs) const { //TODO find simd integer division algorithm
            vec<unsigned long,2> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<unsigned long,2> operator&=(const vec<unsigned long,2>& rhs){
            data = _mm_and_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned long,2> operator|=(const vec<unsigned long,2>& rhs){
            data = _mm_or_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned long,2> operator^=(const vec<unsigned long,2>& rhs){
            data = _mm_xor_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned long,2> operator&(const vec<unsigned long,2>& rhs) const {
            return vec<unsigned long,2>(_mm_and_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned long,2> operator|(const vec<unsigned long,2>& rhs) const {
            return vec<unsigned long,2>(_mm_or_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned long,2> operator^(const vec<unsigned long,2>& rhs) const {
            return vec<unsigned long,2>(_mm_xor_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned long,2> operator~() const {
            return vec<unsigned long,2>(_mm_xor_si128(data,_mm_set1_epi32(-1)));
        }
        __m128i data;
        enum{ size = 2 };
        enum{ bits = 128 };
        friend std::ostream& operator<<(std::ostream& out, vec<unsigned long,2> v){
            out<<v[0]<<" "<<v[1];
            return out;
        }
    };
}
#endif

#endif //VEC2UL_H
