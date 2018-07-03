#ifndef TSIMD_H
#define TSIMD_H

#include <immintrin.h>
#include <ostream>

//if this fails, then you probably need a newer compiler
#if _MSC_VER >= 1400 || __ICC || __ICL
    #define TSIMD_INLINE __forceinline
#elif __GNUC__ > 4 || (__GNUC__== 4 && __GNUC_MINOR__> 1)
    #define TSIMD_INLINE inline __attribute__((always_inline))
#else
    #define TSIMD_INLINE inline
#endif

namespace TSimd{
    template<typename T, int N> class vec{};
    template<typename T> class vec<T,1>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(T a){ data = a; }
        TSIMD_INLINE vec(T* a){ data = *a; }
        TSIMD_INLINE void store(T* a){ *a = data; }
        TSIMD_INLINE vec<T,1>& operator+=(const vec<T,1>& rhs){
            data += rhs;
            return *this;
        }
        TSIMD_INLINE vec<T,1>& operator-=(const vec<T,1>& rhs){
            data -= rhs;
            return *this;
        }
        TSIMD_INLINE vec<T,1>& operator*=(const vec<T,1>& rhs){
            data *= rhs;
            return *this;
        }
        TSIMD_INLINE vec<T,1>& operator/=(const vec<T,1>& rhs){
            data /= rhs;
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
        template<typename V>
        TSIMD_INLINE operator vec<V,1>(){ //cast to other vec types of the same size
            return vec<V,1>((V)data);
        }
        T data;
        enum{ size = 1 };
        friend std::ostream& operator<<(std::ostream& out, vec<T,1> v){
            out<<v.data;
            return out;
        }
    };
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
#include "src/char/vec16c.h"
#include "src/char/vec32c.h"
//UCHARS
#include "src/uchar/vec16uc.h"
#include "src/uchar/vec32uc.h"
//SHORTS
#include "src/short/vec8s.h"
#include "src/short/vec16s.h"
//USHORTS
#include "src/ushort/vec8us.h"
#include "src/ushort/vec16us.h"
//LONGS
//ULONGS

#endif //TSIMD_H
