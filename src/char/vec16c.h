#ifndef VEC16C_H
#define VEC16C_H

#ifdef __SSE2__
namespace TSimd{
    template<> class vec<char,16>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(char a){ data = _mm_set1_epi8(a); }
        TSIMD_INLINE vec(char* a){ data = _mm_loadu_si128((__m128i*)a); }
        TSIMD_INLINE vec(__m128i a){ data = a; }
        TSIMD_INLINE vec(char a, char b, char c, char d, char e, char f, char g, char h, char i, char j, char k, char l, char m, char n, char o, char p){
            data = _mm_set_epi8(p,o,n,m,l,k,j,i,h,g,f,e,d,c,b,a);
        }
        TSIMD_INLINE void store(char* a){ _mm_storeu_si128((__m128i*)a,data); }
        TSIMD_INLINE char& operator[](int idx){ return ((char*)(&data))[idx]; }
        TSIMD_INLINE const char& operator[](int idx) const { return ((char*)(&data))[idx]; }
        TSIMD_INLINE vec<char,16>& operator+=(const vec<char,16>& rhs){
            data = _mm_add_epi8(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<char,16>& operator-=(const vec<char,16>& rhs){
            data = _mm_sub_epi8(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<char,16>& operator*=(const vec<char,16>& rhs){
            __m128i a = _mm_mullo_epi16(data,rhs.data);
            __m128i b = _mm_mullo_epi16(_mm_srli_epi16(data,8),_mm_srli_epi16(rhs.data,8));
            a = _mm_srli_epi16(_mm_slli_epi16(a,8),8);
            b = _mm_slli_epi16(b,8);
            data = _mm_or_si128(a,b);
            return *this;
        }
        inline vec<char,16>& operator/=(const vec<char,16>& rhs){ //TODO find simd integer division algorithm
            (*this)[0]/=rhs[0];
            (*this)[1]/=rhs[1];
            (*this)[2]/=rhs[2];
            (*this)[3]/=rhs[3];
            (*this)[4]/=rhs[4];
            (*this)[5]/=rhs[5];
            (*this)[6]/=rhs[6];
            (*this)[7]/=rhs[7];
            (*this)[8]/=rhs[8];
            (*this)[9]/=rhs[9];
            (*this)[10]/=rhs[10];
            (*this)[11]/=rhs[11];
            (*this)[12]/=rhs[12];
            (*this)[13]/=rhs[13];
            (*this)[14]/=rhs[14];
            (*this)[15]/=rhs[15];
            return *this;
        }
        TSIMD_INLINE vec<char,16> operator+(const vec<char,16>& rhs) const {
            return vec<char,16>(_mm_add_epi8(data,rhs.data));
        }
        TSIMD_INLINE vec<char,16> operator-(const vec<char,16>& rhs) const {
            return vec<char,16>(_mm_sub_epi8(data,rhs.data));
        }
        TSIMD_INLINE vec<char,16> operator*(const vec<char,16>& rhs) const {
            __m128i a = _mm_mullo_epi16(data,rhs.data);
            __m128i b = _mm_mullo_epi16(_mm_srli_epi16(data,8),_mm_srli_epi16(rhs.data,8));
            a = _mm_srli_epi16(_mm_slli_epi16(a,8),8);
            b = _mm_slli_epi16(b,8);
            return vec<char,16>(_mm_or_si128(a,b));
        }
        TSIMD_INLINE vec<char,16> operator/(const vec<char,16>& rhs) const { //TODO find simd integer division algorithm
            vec<char,16> r(data);
            r/=rhs;
            return r;
        }
        TSIMD_INLINE vec<char,16> operator&=(const vec<char,16>& rhs){
            data = _mm_and_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<char,16> operator|=(const vec<char,16>& rhs){
            data = _mm_or_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<char,16> operator^=(const vec<char,16>& rhs){
            data = _mm_xor_si128(data,rhs.data);
            return *this;
        }
        TSIMD_INLINE vec<char,16> operator&(const vec<char,16>& rhs) const {
            return vec<char,16>(_mm_and_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<char,16> operator|(const vec<char,16>& rhs) const {
            return vec<char,16>(_mm_or_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<char,16> operator^(const vec<char,16>& rhs) const {
            return vec<char,16>(_mm_xor_si128(data,rhs.data));
        }
        TSIMD_INLINE vec<char,16> operator~() const {
            return vec<char,16>(_mm_xor_si128(data,_mm_set1_epi32(-1)));
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

#endif //VEC16C_H
