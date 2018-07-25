#ifndef TSIMD_H
#define TSIMD_H

#include <immintrin.h>
#include <ostream>
#include <cstdint>
#include <climits>
#include <type_traits>

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
}
#include "src/misc/reinterpret.h"
#include "src/misc/mask.h"
namespace TSimd{
    namespace intl{
        template<typename T, int N> class ConstProxy{
        public:
            TSIMD_INLINE ConstProxy(const vec<T,N>& v, const std::size_t index) : ref(v), idx(index) {}
            TSIMD_INLINE operator T() const {
                T arr[N];
                ref.store(arr);
                return arr[idx];
            }
        private:
            const vec<T,N>& ref;
            const std::size_t idx;
        };
        template<typename T, int N> class AssignmentProxy{
        public:
            TSIMD_INLINE AssignmentProxy(vec<T,N>& v, const std::size_t index) : ref(v), idx(index) {}
            TSIMD_INLINE operator T() const {
                T arr[N];
                ref.store(arr);
                return arr[idx];
            }
            TSIMD_INLINE AssignmentProxy<T,N>& operator=(const T a){
                T arr[N];
                ref.store(arr);
                arr[idx] = a;
                ref = vec<T,N>(arr);
                return *this;
            }
            TSIMD_INLINE AssignmentProxy<T,N>& operator+=(const T a){
                T arr[N];
                ref.store(arr);
                arr[idx] += a;
                ref = vec<T,N>(arr);
                return *this;
            }
            TSIMD_INLINE AssignmentProxy<T,N>& operator-=(const T a){
                T arr[N];
                ref.store(arr);
                arr[idx] -= a;
                ref = vec<T,N>(arr);
                return *this;
            }
            TSIMD_INLINE AssignmentProxy<T,N>& operator*=(const T a){
                T arr[N];
                ref.store(arr);
                arr[idx] *= a;
                ref = vec<T,N>(arr);
                return *this;
            }
            TSIMD_INLINE AssignmentProxy<T,N>& operator/=(const T a){
                T arr[N];
                ref.store(arr);
                arr[idx] /= a;
                ref = vec<T,N>(arr);
                return *this;
            }
            TSIMD_INLINE AssignmentProxy<T,N>& operator%=(const T a){
                T arr[N];
                ref.store(arr);
                arr[idx] %= a;
                ref = vec<T,N>(arr);
                return *this;
            }
            TSIMD_INLINE AssignmentProxy<T,N>& operator&=(const T a){
                T arr[N];
                ref.store(arr);
                arr[idx] &= a;
                ref = vec<T,N>(arr);
                return *this;
            }
            TSIMD_INLINE AssignmentProxy<T,N>& operator|=(const T a){
                T arr[N];
                ref.store(arr);
                arr[idx] |= a;
                ref = vec<T,N>(arr);
                return *this;
            }
            TSIMD_INLINE AssignmentProxy<T,N>& operator^=(const T a){
                T arr[N];
                ref.store(arr);
                arr[idx] ^= a;
                ref = vec<T,N>(arr);
                return *this;
            }
            TSIMD_INLINE AssignmentProxy<T,N>& operator<<=(const T a){
                T arr[N];
                ref.store(arr);
                arr[idx] <<= a;
                ref = vec<T,N>(arr);
                return *this;
            }
            TSIMD_INLINE AssignmentProxy<T,N>& operator>>=(const T a){
                T arr[N];
                ref.store(arr);
                arr[idx] >>= a;
                ref = vec<T,N>(arr);
                return *this;
            }
            TSIMD_INLINE AssignmentProxy<T,N>& operator--(){
                T arr[N];
                ref.store(arr);
                arr[idx]--;
                ref = vec<T,N>(arr);
                return *this;
            }
            TSIMD_INLINE AssignmentProxy<T,N>& operator++(){
                T arr[N];
                ref.store(arr);
                arr[idx]++;
                ref = vec<T,N>(arr);
                return *this;
            }
            TSIMD_INLINE T operator--(int){
                T arr[N];
                ref.store(arr);
                T ret = arr[idx];
                arr[idx]--;
                ref = vec<T,N>(arr);
                return ret;
            }
            TSIMD_INLINE T operator++(int){
                T arr[N];
                ref.store(arr);
                T ret = arr[idx];
                arr[idx]++;
                ref = vec<T,N>(arr);
                return ret;
            }
        private:
            vec<T,N>& ref;
            const std::size_t idx;
        };
    }

    template<typename T> class vec<T,1>{
    public:
        TSIMD_INLINE vec(){}
        TSIMD_INLINE vec(T a){ data = a; }
        explicit TSIMD_INLINE vec(T* a){ data = *a; }
        TSIMD_INLINE void store(T* a){ *a = data; }
        TSIMD_INLINE intl::ConstProxy<T,1> operator[](const std::size_t idx) const { return intl::ConstProxy<T,1>(*this,idx); }
        TSIMD_INLINE intl::AssignmentProxy<T,1> operator[](const std::size_t idx){ return intl::AssignmentProxy<T,1>(*this,idx); }
        TSIMD_INLINE static vec<T,1> zero(){
            vec<T,1> r;
            r.data = 0;
            return r;
        }
        TSIMD_INLINE vec<T,1>& operator+=(const vec<T,1> rhs){
            data += rhs.data;
            return *this;
        }
        TSIMD_INLINE vec<T,1>& operator-=(const vec<T,1> rhs){
            data -= rhs.data;
            return *this;
        }
        TSIMD_INLINE vec<T,1>& operator*=(const vec<T,1> rhs){
            data *= rhs.data;
            return *this;
        }
        TSIMD_INLINE vec<T,1>& operator/=(const vec<T,1> rhs){
            data /= rhs.data;
            return *this;
        }
        TSIMD_INLINE vec<T,1> operator+(const vec<T,1> rhs) const {
            return vec<T,1>(data+rhs.data);
        }
        TSIMD_INLINE vec<T,1> operator-(const vec<T,1> rhs) const {
            return vec<T,1>(data-rhs.data);
        }
        TSIMD_INLINE vec<T,1> operator*(const vec<T,1> rhs) const {
            return vec<T,1>(data*rhs.data);
        }
        TSIMD_INLINE vec<T,1> operator/(const vec<T,1> rhs) const {
            return vec<T,1>(data/rhs.data);
        }
        TSIMD_INLINE vec<T,1> operator-() const {
            return -data;
        }
        TSIMD_INLINE vec<T,1>& operator&=(const vec<T,1> rhs){
            data &= rhs.data;
            return *this;
        }
        TSIMD_INLINE vec<T,1>& operator|=(const vec<T,1> rhs){
            data |= rhs.data;
            return *this;
        }
        TSIMD_INLINE vec<T,1>& operator^=(const vec<T,1> rhs){
            data ^= rhs.data;
            return *this;
        }
        TSIMD_INLINE vec<T,1> operator&(const vec<T,1> rhs) const {
            return vec<T,1>(data&rhs.data);
        }
        TSIMD_INLINE vec<T,1> operator|(const vec<T,1> rhs) const {
            return vec<T,1>(data|rhs.data);
        }
        TSIMD_INLINE vec<T,1> operator^(const vec<T,1> rhs) const {
            return vec<T,1>(data^rhs.data);
        }
        TSIMD_INLINE vec<T,1> operator~() const {
            return vec<T,1>(~data);
        }
        template<typename V>
        TSIMD_INLINE operator vec<V,1>(){ //cast to other vec types of the same size
            return vec<V,1>((V)data);
        }
        TSIMD_INLINE mask<1> operator==(const vec<T,1> a) const {
            return data==a;
        }
        TSIMD_INLINE mask<1> operator!=(const vec<T,1> a) const {
            return data!=a;
        }
        TSIMD_INLINE mask<1> operator>(const vec<T,1> a) const {
            return data>a;
        }
        TSIMD_INLINE mask<1> operator>=(const vec<T,1> a) const {
            return data>=a;
        }
        TSIMD_INLINE mask<1> operator<(const vec<T,1> a) const {
            return data>a;
        }
        TSIMD_INLINE mask<1> operator<=(const vec<T,1> a) const {
            return data>=a;
        }
        TSIMD_INLINE mask<1> operator!() const {
            return !data;
        }
        TSIMD_INLINE bool any() const {
            return data;
        }
        TSIMD_INLINE bool all() const {
            return data;
        }
        TSIMD_INLINE vec<T,1> max(const vec<T,1> rhs) const {
            return (data>rhs.data)?data:rhs.data;
        }
        TSIMD_INLINE vec<T,1> min(const vec<T,1> rhs) const {
            return (data<rhs.data)?data:rhs.data;
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
#include "src/float/vec4f.h"
#include "src/float/vec8f.h"
#include "src/double/vec2d.h"
#include "src/double/vec4d.h"
#include "src/int32/vec4int32.h"
#include "src/int32/vec8int32.h"
#include "src/uint32/vec4uint32.h"
#include "src/uint32/vec8uint32.h"
#ifdef TSIMD_USE_SIGNED_CHARS
    #include "src/int8/vec16c.h"
    #include "src/int8/vec32c.h"
#endif
#include "src/int8/vec16int8.h"
#include "src/int8/vec32int8.h"
#ifdef TSIMD_USE_UNSIGNED_CHARS
    #include "src/uint8/vec16uc.h"
    #include "src/uint8/vec32uc.h"
#endif
#include "src/uint8/vec16uint8.h"
#include "src/uint8/vec32uint8.h"
#include "src/int16/vec8int16.h"
#include "src/int16/vec16int16.h"
#include "src/uint16/vec8uint16.h"
#include "src/uint16/vec16uint16.h"
#include "src/int64/vec2int64.h"
#include "src/int64/vec4int64.h"
#include "src/uint64/vec2uint64.h"
#include "src/uint64/vec4uint64.h"

#endif //TSIMD_H
