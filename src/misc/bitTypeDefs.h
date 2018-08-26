#ifndef TSIMD_BITTYPEDEFS_H
#define TSIMD_BITTYPEDEFS_H

#include <cstdint>

#include "../../tsimd.h"

namespace tsimd{
    namespace intl{
        template<int B> class inttype;
        template<> class inttype<8>{
            typedef int8_t type;
            typedef uint8_t utype;
        };
        template<> class inttype<16>{
            typedef int16_t type;
            typedef uint16_t utype;
        };
        template<> class inttype<32>{
            typedef int32_t type;
            typedef uint32_t utype;
        };
        template<> class inttype<64>{
            typedef int64_t type;
            typedef uint64_t utype;
        };

        template<int B> class fptype;
        template<> class fptype<32>{
            typedef float type;
        };
        template<> class fptype<64>{
            typedef double type;
        };
    }

    template<int B> using inttype = typename intl::inttype<B>::type;
    template<int B> using uinttype = typename intl::inttype<B>::utype;;
    template<int B> using fptype = typename intl::fptype<B>::type;
}

#endif //TSIMD_BITTYPEDEFS_H
