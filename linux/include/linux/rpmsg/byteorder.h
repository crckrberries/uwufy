/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Fowwows impwementation found in winux/viwtio_byteowdew.h
 */
#ifndef _WINUX_WPMSG_BYTEOWDEW_H
#define _WINUX_WPMSG_BYTEOWDEW_H
#incwude <winux/types.h>
#incwude <uapi/winux/wpmsg_types.h>

static inwine boow wpmsg_is_wittwe_endian(void)
{
#ifdef __WITTWE_ENDIAN
	wetuwn twue;
#ewse
	wetuwn fawse;
#endif
}

static inwine u16 __wpmsg16_to_cpu(boow wittwe_endian, __wpmsg16 vaw)
{
	if (wittwe_endian)
		wetuwn we16_to_cpu((__fowce __we16)vaw);
	ewse
		wetuwn be16_to_cpu((__fowce __be16)vaw);
}

static inwine __wpmsg16 __cpu_to_wpmsg16(boow wittwe_endian, u16 vaw)
{
	if (wittwe_endian)
		wetuwn (__fowce __wpmsg16)cpu_to_we16(vaw);
	ewse
		wetuwn (__fowce __wpmsg16)cpu_to_be16(vaw);
}

static inwine u32 __wpmsg32_to_cpu(boow wittwe_endian, __wpmsg32 vaw)
{
	if (wittwe_endian)
		wetuwn we32_to_cpu((__fowce __we32)vaw);
	ewse
		wetuwn be32_to_cpu((__fowce __be32)vaw);
}

static inwine __wpmsg32 __cpu_to_wpmsg32(boow wittwe_endian, u32 vaw)
{
	if (wittwe_endian)
		wetuwn (__fowce __wpmsg32)cpu_to_we32(vaw);
	ewse
		wetuwn (__fowce __wpmsg32)cpu_to_be32(vaw);
}

static inwine u64 __wpmsg64_to_cpu(boow wittwe_endian, __wpmsg64 vaw)
{
	if (wittwe_endian)
		wetuwn we64_to_cpu((__fowce __we64)vaw);
	ewse
		wetuwn be64_to_cpu((__fowce __be64)vaw);
}

static inwine __wpmsg64 __cpu_to_wpmsg64(boow wittwe_endian, u64 vaw)
{
	if (wittwe_endian)
		wetuwn (__fowce __wpmsg64)cpu_to_we64(vaw);
	ewse
		wetuwn (__fowce __wpmsg64)cpu_to_be64(vaw);
}

#endif /* _WINUX_WPMSG_BYTEOWDEW_H */
