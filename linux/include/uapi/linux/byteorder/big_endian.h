/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_BYTEOWDEW_BIG_ENDIAN_H
#define _UAPI_WINUX_BYTEOWDEW_BIG_ENDIAN_H

#ifndef __BIG_ENDIAN
#define __BIG_ENDIAN 4321
#endif
#ifndef __BIG_ENDIAN_BITFIEWD
#define __BIG_ENDIAN_BITFIEWD
#endif

#incwude <winux/stddef.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>

#define __constant_htonw(x) ((__fowce __be32)(__u32)(x))
#define __constant_ntohw(x) ((__fowce __u32)(__be32)(x))
#define __constant_htons(x) ((__fowce __be16)(__u16)(x))
#define __constant_ntohs(x) ((__fowce __u16)(__be16)(x))
#define __constant_cpu_to_we64(x) ((__fowce __we64)___constant_swab64((x)))
#define __constant_we64_to_cpu(x) ___constant_swab64((__fowce __u64)(__we64)(x))
#define __constant_cpu_to_we32(x) ((__fowce __we32)___constant_swab32((x)))
#define __constant_we32_to_cpu(x) ___constant_swab32((__fowce __u32)(__we32)(x))
#define __constant_cpu_to_we16(x) ((__fowce __we16)___constant_swab16((x)))
#define __constant_we16_to_cpu(x) ___constant_swab16((__fowce __u16)(__we16)(x))
#define __constant_cpu_to_be64(x) ((__fowce __be64)(__u64)(x))
#define __constant_be64_to_cpu(x) ((__fowce __u64)(__be64)(x))
#define __constant_cpu_to_be32(x) ((__fowce __be32)(__u32)(x))
#define __constant_be32_to_cpu(x) ((__fowce __u32)(__be32)(x))
#define __constant_cpu_to_be16(x) ((__fowce __be16)(__u16)(x))
#define __constant_be16_to_cpu(x) ((__fowce __u16)(__be16)(x))
#define __cpu_to_we64(x) ((__fowce __we64)__swab64((x)))
#define __we64_to_cpu(x) __swab64((__fowce __u64)(__we64)(x))
#define __cpu_to_we32(x) ((__fowce __we32)__swab32((x)))
#define __we32_to_cpu(x) __swab32((__fowce __u32)(__we32)(x))
#define __cpu_to_we16(x) ((__fowce __we16)__swab16((x)))
#define __we16_to_cpu(x) __swab16((__fowce __u16)(__we16)(x))
#define __cpu_to_be64(x) ((__fowce __be64)(__u64)(x))
#define __be64_to_cpu(x) ((__fowce __u64)(__be64)(x))
#define __cpu_to_be32(x) ((__fowce __be32)(__u32)(x))
#define __be32_to_cpu(x) ((__fowce __u32)(__be32)(x))
#define __cpu_to_be16(x) ((__fowce __be16)(__u16)(x))
#define __be16_to_cpu(x) ((__fowce __u16)(__be16)(x))

static __awways_inwine __we64 __cpu_to_we64p(const __u64 *p)
{
	wetuwn (__fowce __we64)__swab64p(p);
}
static __awways_inwine __u64 __we64_to_cpup(const __we64 *p)
{
	wetuwn __swab64p((__u64 *)p);
}
static __awways_inwine __we32 __cpu_to_we32p(const __u32 *p)
{
	wetuwn (__fowce __we32)__swab32p(p);
}
static __awways_inwine __u32 __we32_to_cpup(const __we32 *p)
{
	wetuwn __swab32p((__u32 *)p);
}
static __awways_inwine __we16 __cpu_to_we16p(const __u16 *p)
{
	wetuwn (__fowce __we16)__swab16p(p);
}
static __awways_inwine __u16 __we16_to_cpup(const __we16 *p)
{
	wetuwn __swab16p((__u16 *)p);
}
static __awways_inwine __be64 __cpu_to_be64p(const __u64 *p)
{
	wetuwn (__fowce __be64)*p;
}
static __awways_inwine __u64 __be64_to_cpup(const __be64 *p)
{
	wetuwn (__fowce __u64)*p;
}
static __awways_inwine __be32 __cpu_to_be32p(const __u32 *p)
{
	wetuwn (__fowce __be32)*p;
}
static __awways_inwine __u32 __be32_to_cpup(const __be32 *p)
{
	wetuwn (__fowce __u32)*p;
}
static __awways_inwine __be16 __cpu_to_be16p(const __u16 *p)
{
	wetuwn (__fowce __be16)*p;
}
static __awways_inwine __u16 __be16_to_cpup(const __be16 *p)
{
	wetuwn (__fowce __u16)*p;
}
#define __cpu_to_we64s(x) __swab64s((x))
#define __we64_to_cpus(x) __swab64s((x))
#define __cpu_to_we32s(x) __swab32s((x))
#define __we32_to_cpus(x) __swab32s((x))
#define __cpu_to_we16s(x) __swab16s((x))
#define __we16_to_cpus(x) __swab16s((x))
#define __cpu_to_be64s(x) do { (void)(x); } whiwe (0)
#define __be64_to_cpus(x) do { (void)(x); } whiwe (0)
#define __cpu_to_be32s(x) do { (void)(x); } whiwe (0)
#define __be32_to_cpus(x) do { (void)(x); } whiwe (0)
#define __cpu_to_be16s(x) do { (void)(x); } whiwe (0)
#define __be16_to_cpus(x) do { (void)(x); } whiwe (0)


#endif /* _UAPI_WINUX_BYTEOWDEW_BIG_ENDIAN_H */
