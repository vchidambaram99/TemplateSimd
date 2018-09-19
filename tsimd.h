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

//if left unspecified, tsimd will use whatever your system usually uses
#if(!defined(TSIMD_USE_SIGNED_CHARS)&&!defined(TSIMD_USE_UNSIGNED_CHARS))
    #if(CHAR_MIN<0)
        #define TSIMD_USE_SIGNED_CHARS
    #else
        #define TSIMD_USE_UNSIGNED_CHARS
    #endif
#endif

namespace tsimd{
    template<typename T, int N> class vec{};
}

#include "src/misc/reinterpret.h"
#include "src/misc/bitTypeDefs.h"
#include "src/misc/mask.h"
#include "src/misc/proxies.h"

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
