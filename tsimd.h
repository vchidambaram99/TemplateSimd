#ifndef TSIMD_H
#define TSIMD_H

#include <immintrin.h>
#include <ostream>
#include <cstdint>
#include <climits>

//if this fails, then you probably need a newer compiler
#if _MSC_VER >= 1400 || __ICC || __ICL
    #define TSIMD_INLINE __forceinline
#elif __GNUC__ > 4 || (__GNUC__== 4 && __GNUC_MINOR__> 1)
    #define TSIMD_INLINE inline __attribute__((always_inline))
#else
    #define TSIMD_INLINE inline
#endif

#if(!defined(TSIMD_USE_SIGNED_CHARS)&&!defined(TSIMD_USE_UNSIGNED_CHARS))
    #if(CHAR_MIN<0)
        #define TSIMD_USE_SIGNED_CHARS
    #else
        #define TSIMD_USE_UNSIGNED_CHARS
    #endif
#endif

namespace TSimd{
    template<typename T, int N> class vec{};
    template<typename T> class vec<T,1>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(T a){ data = a; }
        TSIMD_INLINE vec(T* a){ data = *a; }
        TSIMD_INLINE void store(T* a){ *a = data; }
        TSIMD_INLINE T& operator[](int idx){ return data; } //for api consistency
        TSIMD_INLINE const T& operator[](int idx) const { return data; } //for api consistency
        TSIMD_INLINE vec<T,1>& operator+=(const vec<T,1>& rhs){
            data += rhs.data;
            return *this;
        }
        TSIMD_INLINE vec<T,1>& operator-=(const vec<T,1>& rhs){
            data -= rhs.data;
            return *this;
        }
        TSIMD_INLINE vec<T,1>& operator*=(const vec<T,1>& rhs){
            data *= rhs.data;
            return *this;
        }
        TSIMD_INLINE vec<T,1>& operator/=(const vec<T,1>& rhs){
            data /= rhs.data;
            return *this;
        }
        TSIMD_INLINE vec<T,1> operator+(const vec<T,1>& rhs) const {
            return vec<T,1>(data+rhs.data);
        }
        TSIMD_INLINE vec<T,1> operator-(const vec<T,1>& rhs) const {
            return vec<T,1>(data-rhs.data);
        }
        TSIMD_INLINE vec<T,1> operator*(const vec<T,1>& rhs) const {
            return vec<T,1>(data*rhs.data);
        }
        TSIMD_INLINE vec<T,1> operator/(const vec<T,1>& rhs) const {
            return vec<T,1>(data/rhs.data);
        }
        TSIMD_INLINE vec<T,1>& operator&=(const vec<T,1>& rhs){
            data &= rhs.data;
            return *this;
        }
        TSIMD_INLINE vec<T,1>& operator|=(const vec<T,1>& rhs){
            data |= rhs.data;
            return *this;
        }
        TSIMD_INLINE vec<T,1>& operator^=(const vec<T,1>& rhs){
            data ^= rhs.data;
            return *this;
        }
        TSIMD_INLINE vec<T,1> operator&(const vec<T,1>& rhs) const {
            return vec<T,1>(data&rhs.data);
        }
        TSIMD_INLINE vec<T,1> operator|(const vec<T,1>& rhs) const {
            return vec<T,1>(data|rhs.data);
        }
        TSIMD_INLINE vec<T,1> operator^(const vec<T,1>& rhs) const {
            return vec<T,1>(data^rhs.data);
        }
        TSIMD_INLINE vec<T,1> operator~() const {
            return vec<T,1>(~data);
        }
        template<typename V>
        TSIMD_INLINE operator vec<V,1>(){ //cast to other vec types of the same size
            return vec<V,1>((V)data);
        }
        TSIMD_INLINE bool operator==(const vec<T,1>& a) const {
            return data==a;
        }
        TSIMD_INLINE bool operator!=(const vec<T,1>& a) const {
            return data!=a;
        }
        TSIMD_INLINE bool operator>(const vec<T,1>& a) const {
            return data>a;
        }
        TSIMD_INLINE bool operator>=(const vec<T,1>& a) const {
            return data>=a;
        }
        TSIMD_INLINE bool operator<(const vec<T,1>& a) const {
            return data>a;
        }
        TSIMD_INLINE bool operator<=(const vec<T,1>& a) const {
            return data>=a;
        }
        T data;
        enum{ size = 1 };
        enum{ bits = sizeof(T) };
        friend std::ostream& operator<<(std::ostream& out, vec<T,1> v){
            out<<v.data;
            return out;
        }
    };
}
#include "src/reinterpret.h"
namespace TSimd{ //equivalent of ternary operator
/*
Note: On my computer, microbenchmarking shows that this method is pretty much as fast as a blend
*/
    template<typename T>
    TSIMD_INLINE T select(const T& cond, const T& a, const T& b){
        return (a&cond)|(b&~cond);
    }
    template<typename T>
    TSIMD_INLINE vec<T,1> select(const bool& cond, const vec<T,1>& a, const vec<T,1>& b){
        return (cond)?a:b;
    }
}
//FLOATS
#include "src/float/vec4f.h"
#include "src/float/vec8f.h"
//DOUBLES
#include "src/double/vec2d.h"
#include "src/double/vec4d.h"
//INTS
#include "src/int/vec4i.h"
#include "src/int/vec8i.h"
//UINTS
#include "src/uint/vec4ui.h"
#include "src/uint/vec8ui.h"
//CHARS
#ifdef TSIMD_USE_SIGNED_CHARS
    #include "src/char/vec16c.h"
    #include "src/char/vec32c.h"
#endif
#include "src/char/vec16int8.h"
#include "src/char/vec32int8.h"
//UCHARS
#ifdef TSIMD_USE_UNSIGNED_CHARS
    #include "src/uchar/vec16uc.h"
    #include "src/uchar/vec32uc.h"
#endif
#include "src/uchar/vec16uint8.h"
#include "src/uchar/vec32uint8.h"
//SHORTS
#include "src/short/vec8s.h"
#include "src/short/vec16s.h"
//USHORTS
#include "src/ushort/vec8us.h"
#include "src/ushort/vec16us.h"
//LONGS
#include "src/long/vec2l.h"
#include "src/long/vec4l.h"
//ULONGS
#include "src/ulong/vec2ul.h"
#include "src/ulong/vec4ul.h"

#endif //TSIMD_H
