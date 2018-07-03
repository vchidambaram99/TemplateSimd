#ifndef VEC8S_H
#define VEC8S_H

#ifdef __SSE2__
namespace TSimd{
    template<> class vec<short,8>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(short a){ data = _mm_set1_epi16(a); }
        TSIMD_INLINE vec(short* a){ data = _mm_loadu_si128((__m128i*)a); }
        TSIMD_INLINE vec(__m128i a){ data = a; }
        TSIMD_INLINE vec(short a, short b, short c, short d, short e, short f, short g, short h){
            data = _mm_set_epi16(h,g,f,e,d,c,b,a);
        }
        TSIMD_INLINE void store(short* a){ _mm_storeu_si128((__m128i*)a,data); }
        TSIMD_INLINE short& operator[](int idx){ return ((short*)(&data))[idx]; }
        TSIMD_INLINE const short& operator[](int idx) const { return ((short*)(&data))[idx]; }
        TSIMD_INLINE vec<short,8>& operator+=(const vec<short,8>& rhs){
            data = _mm_add_epi16(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<short,8>& operator-=(const vec<short,8>& rhs){
            data = _mm_sub_epi16(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<short,8>& operator*=(const vec<short,8>& rhs){
            data = _mm_mullo_epi16(data,rhs.data);
            return *this;
        }
        inline vec<short,8>& operator/=(const vec<short,8>& rhs){ //TODO find simd integer division algorithm
            (*this)[0]/=rhs[0];
            (*this)[1]/=rhs[1];
            (*this)[2]/=rhs[2];
            (*this)[3]/=rhs[3];
            (*this)[4]/=rhs[4];
            (*this)[5]/=rhs[5];
            (*this)[6]/=rhs[6];
            (*this)[7]/=rhs[7];
            return *this;
        }
        TSIMD_INLINE vec<short,8> operator+(const vec<short,8>& rhs) const {
            return vec<short,8>(_mm_add_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<short,8> operator-(const vec<short,8>& rhs) const {
            return vec<short,8>(_mm_sub_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<short,8> operator*(const vec<short,8>& rhs) const {
            return vec<short,8>(_mm_mullo_epi16(data,rhs.data));
        }
        TSIMD_INLINE vec<short,8> operator/(const vec<short,8>& rhs) const { //TODO find simd integer division algorithm
            vec<short,8> r(data);
            r/=rhs;
            return r;
        }
        __m128i data;
        enum{ size = 8 };
        friend std::ostream& operator<<(std::ostream& out, vec<short,8> v){
            out<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3];
            out<<" "<<v[4]<<" "<<v[5]<<" "<<v[6]<<" "<<v[7];
            return out;
        }
    };
}
#endif

#endif //VEC8S_H
