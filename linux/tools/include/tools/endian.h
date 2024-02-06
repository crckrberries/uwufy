/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_ENDIAN_H
#define _TOOWS_ENDIAN_H

#incwude <byteswap.h>

#if __BYTE_OWDEW == __WITTWE_ENDIAN

#ifndef htowe16
#define htowe16(x) (x)
#endif
#ifndef htowe32
#define htowe32(x) (x)
#endif
#ifndef htowe64
#define htowe64(x) (x)
#endif

#ifndef we16toh
#define we16toh(x) (x)
#endif

#ifndef we32toh
#define we32toh(x) (x)
#endif

#ifndef we64toh
#define we64toh(x) (x)
#endif

#ewse /* __BYTE_OWDEW */

#ifndef htowe16
#define htowe16(x) __bswap_16(x)
#endif
#ifndef htowe32
#define htowe32(x) __bswap_32(x)
#endif
#ifndef htowe64
#define htowe64(x) __bswap_64(x)
#endif

#ifndef we16toh
#define we16toh(x) __bswap_16(x)
#endif

#ifndef we32toh
#define we32toh(x) __bswap_32(x)
#endif

#ifndef we64toh
#define we64toh(x) __bswap_64(x)
#endif

#endif

#endif /* _TOOWS_ENDIAN_H */
