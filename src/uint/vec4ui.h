#ifndef VEC4UI_H
#define VEC4UI_H

#ifdef __SSE2__
namespace TSimd{
    template<> class vec<unsigned int,4>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(unsigned int a){ data = _mm_set1_epi32(a); }
        TSIMD_INLINE vec(unsigned int* a){ data = _mm_loadu_si128((__m128i*)a); }
        TSIMD_INLINE vec(__m128i a){ data = a; }
        TSIMD_INLINE vec(unsigned int a, unsigned int b, unsigned int c, unsigned int d){ data = _mm_set_epi32(d,c,b,a); }
        TSIMD_INLINE void store(unsigned int* a){ _mm_storeu_si128((__m128i*)a,data); }
        TSIMD_INLINE unsigned int& operator[](int idx){ return ((unsigned int*)(&data))[idx]; }
        TSIMD_INLINE const unsigned int& operator[](int idx) const { return ((unsigned int*)(&data))[idx]; }
        TSIMD_INLINE vec<unsigned int,4>& operator+=(const vec<unsigned int,4>& rhs){
            data = _mm_add_epi32(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned int,4>& operator-=(const vec<unsigned int,4>& rhs){
            data = _mm_sub_epi32(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<unsigned int,4>& operator*=(const vec<unsigned int,4>& rhs){
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
        inline vec<unsigned int,4>& operator/=(const vec<unsigned int,4>& rhs){ //TODO find simd unsigned integer division algorithm
            (*this)[0]/=rhs[0];
            (*this)[1]/=rhs[1];
            (*this)[2]/=rhs[2];
            (*this)[3]/=rhs[3];
            return *this;
        }
        TSIMD_INLINE vec<unsigned int,4> operator+(const vec<unsigned int,4>& rhs) const {
            return vec<unsigned int,4>(_mm_add_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned int,4> operator-(const vec<unsigned int,4>& rhs) const {
            return vec<unsigned int,4>(_mm_sub_epi32(data,rhs.data));
        }
        TSIMD_INLINE vec<unsigned int,4> operator*(const vec<unsigned int,4>& rhs) const {
            #ifdef __SSE4_1__
                return vec<unsigned int,4>(_mm_mullo_epi32(data,rhs.data));
            #else
                __m128i a = _mm_mul_epu32(data,rhs.data);
                __m128i b = _mm_mul_epu32(_mm_shuffle_epi32(data,_MM_SHUFFLE(3,3,1,1)),_mm_shuffle_epi32(rhs.data,_MM_SHUFFLE(3,3,1,1)));
                a = _mm_shuffle_epi32(a,_MM_SHUFFLE(3,2,2,0));
                b = _mm_shuffle_epi32(b,_MM_SHUFFLE(3,2,2,0));
                return vec<unsigned int,4>(_mm_unpacklo_epi32(a,b));
            #endif
        }
        TSIMD_INLINE vec<unsigned int,4> operator/(const vec<unsigned int,4>& rhs) const { //TODO find simd unsigned integer division algorithm
            vec<unsigned int,4> r(data);
            r/=rhs;
            return r;
        }
        __m128i data;
        enum{ size = 4 };
        friend std::ostream& operator<<(std::ostream& out, vec<unsigned int, 4> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            return out;
        }
    };
}
#endif

#endif //VEC4UI_H
