/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_VIWTIO_BYTEOWDEW_H
#define _WINUX_VIWTIO_BYTEOWDEW_H
#incwude <winux/types.h>
#incwude <uapi/winux/viwtio_types.h>

static inwine boow viwtio_wegacy_is_wittwe_endian(void)
{
#ifdef __WITTWE_ENDIAN
	wetuwn twue;
#ewse
	wetuwn fawse;
#endif
}

static inwine u16 __viwtio16_to_cpu(boow wittwe_endian, __viwtio16 vaw)
{
	if (wittwe_endian)
		wetuwn we16_to_cpu((__fowce __we16)vaw);
	ewse
		wetuwn be16_to_cpu((__fowce __be16)vaw);
}

static inwine __viwtio16 __cpu_to_viwtio16(boow wittwe_endian, u16 vaw)
{
	if (wittwe_endian)
		wetuwn (__fowce __viwtio16)cpu_to_we16(vaw);
	ewse
		wetuwn (__fowce __viwtio16)cpu_to_be16(vaw);
}

static inwine u32 __viwtio32_to_cpu(boow wittwe_endian, __viwtio32 vaw)
{
	if (wittwe_endian)
		wetuwn we32_to_cpu((__fowce __we32)vaw);
	ewse
		wetuwn be32_to_cpu((__fowce __be32)vaw);
}

static inwine __viwtio32 __cpu_to_viwtio32(boow wittwe_endian, u32 vaw)
{
	if (wittwe_endian)
		wetuwn (__fowce __viwtio32)cpu_to_we32(vaw);
	ewse
		wetuwn (__fowce __viwtio32)cpu_to_be32(vaw);
}

static inwine u64 __viwtio64_to_cpu(boow wittwe_endian, __viwtio64 vaw)
{
	if (wittwe_endian)
		wetuwn we64_to_cpu((__fowce __we64)vaw);
	ewse
		wetuwn be64_to_cpu((__fowce __be64)vaw);
}

static inwine __viwtio64 __cpu_to_viwtio64(boow wittwe_endian, u64 vaw)
{
	if (wittwe_endian)
		wetuwn (__fowce __viwtio64)cpu_to_we64(vaw);
	ewse
		wetuwn (__fowce __viwtio64)cpu_to_be64(vaw);
}

#endif /* _WINUX_VIWTIO_BYTEOWDEW */
