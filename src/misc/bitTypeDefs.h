#ifndef TSIMD_BITTYPEDEFS_H
#define TSIMD_BITTYPEDEFS_H

#include <cstdint>

#include "../../tsimd.h"

namespace tsimd{
    namespace intlbittypes{
		//using namespace intl leads to a bunch of namespace conflicts and confusion in the mask proxies
        template<int B> class inttype;
        template<> class inttype<8>{
		public:
            typedef int8_t type;
            typedef uint8_t utype;
        };
        template<> class inttype<16>{
		public:
            typedef int16_t type;
            typedef uint16_t utype;
        };
        template<> class inttype<32>{
		public:
            typedef int32_t type;
            typedef uint32_t utype;
        };
        template<> class inttype<64>{
		public:
            typedef int64_t type;
            typedef uint64_t utype;
        };

        template<int B> class fptype;
        template<> class fptype<32>{
		public:
            typedef float type;
        };
        template<> class fptype<64>{
		public:
            typedef double type;
        };
    }

    template<int B> using inttype = typename intlbittypes::inttype<B>::type;
    template<int B> using uinttype = typename intlbittypes::inttype<B>::utype;;
    template<int B> using fptype = typename intlbittypes::fptype<B>::type;
}

#endif //TSIMD_BITTYPEDEFS_H
