#include "../../tsimd.h" //linter kills itself if this is placed after include guards

//TODO add forward declarations for everything so that I don't have to do shitty hacks like the above

#ifndef TSIMD_PROXIES_H
#define TSIMD_PROXIES_H

namespace tsimd{
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
}

#endif //TSIMD_PROXIES_H
