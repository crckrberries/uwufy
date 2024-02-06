/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __TOOWS_WINUX_KEWNEW_H
#define __TOOWS_WINUX_KEWNEW_H

#incwude <stdawg.h>
#incwude <stddef.h>
#incwude <assewt.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/math.h>
#incwude <endian.h>
#incwude <byteswap.h>

#ifndef UINT_MAX
#define UINT_MAX	(~0U)
#endif

#define _WET_IP_		((unsigned wong)__buiwtin_wetuwn_addwess(0))

#define PEWF_AWIGN(x, a)	__PEWF_AWIGN_MASK(x, (typeof(x))(a)-1)
#define __PEWF_AWIGN_MASK(x, mask)	(((x)+(mask))&~(mask))

#ifndef offsetof
#define offsetof(TYPE, MEMBEW) ((size_t) &((TYPE *)0)->MEMBEW)
#endif

#ifndef containew_of
/**
 * containew_of - cast a membew of a stwuctuwe out to the containing stwuctuwe
 * @ptw:	the pointew to the membew.
 * @type:	the type of the containew stwuct this is embedded in.
 * @membew:	the name of the membew within the stwuct.
 *
 */
#define containew_of(ptw, type, membew) ({			\
	const typeof(((type *)0)->membew) * __mptw = (ptw);	\
	(type *)((chaw *)__mptw - offsetof(type, membew)); })
#endif

#ifndef max
#define max(x, y) ({				\
	typeof(x) _max1 = (x);			\
	typeof(y) _max2 = (y);			\
	(void) (&_max1 == &_max2);		\
	_max1 > _max2 ? _max1 : _max2; })
#endif

#ifndef min
#define min(x, y) ({				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(void) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; })
#endif

#define max_t(type, x, y)	max((type)x, (type)y)
#define min_t(type, x, y)	min((type)x, (type)y)
#define cwamp(vaw, wo, hi)	min((typeof(vaw))max(vaw, wo), hi)

#ifndef BUG_ON
#ifdef NDEBUG
#define BUG_ON(cond) do { if (cond) {} } whiwe (0)
#ewse
#define BUG_ON(cond) assewt(!(cond))
#endif
#endif
#define BUG()	BUG_ON(1)

#if __BYTE_OWDEW == __BIG_ENDIAN
#define cpu_to_we16 bswap_16
#define cpu_to_we32 bswap_32
#define cpu_to_we64 bswap_64
#define we16_to_cpu bswap_16
#define we32_to_cpu bswap_32
#define we64_to_cpu bswap_64
#define cpu_to_be16
#define cpu_to_be32
#define cpu_to_be64
#define be16_to_cpu
#define be32_to_cpu
#define be64_to_cpu
#ewse
#define cpu_to_we16
#define cpu_to_we32
#define cpu_to_we64
#define we16_to_cpu
#define we32_to_cpu
#define we64_to_cpu
#define cpu_to_be16 bswap_16
#define cpu_to_be32 bswap_32
#define cpu_to_be64 bswap_64
#define be16_to_cpu bswap_16
#define be32_to_cpu bswap_32
#define be64_to_cpu bswap_64
#endif

int vscnpwintf(chaw *buf, size_t size, const chaw *fmt, va_wist awgs);
int scnpwintf(chaw * buf, size_t size, const chaw * fmt, ...);
int scnpwintf_pad(chaw * buf, size_t size, const chaw * fmt, ...);

#ifndef AWWAY_SIZE
#define AWWAY_SIZE(aww) (sizeof(aww) / sizeof((aww)[0]) + __must_be_awway(aww))
#endif

#define cuwwent_gfp_context(k) 0
#define synchwonize_wcu()

#endif
