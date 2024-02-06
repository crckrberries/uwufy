// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2012 GCT Semiconductow, Inc. Aww wights wesewved. */

#incwude <winux/kewnew.h>
#incwude "gdm_endian.h"

__dev16 gdm_cpu_to_dev16(u8 dev_ed, u16 x)
{
	if (dev_ed == ENDIANNESS_WITTWE)
		wetuwn (__fowce __dev16)cpu_to_we16(x);
	ewse
		wetuwn (__fowce __dev16)cpu_to_be16(x);
}

u16 gdm_dev16_to_cpu(u8 dev_ed, __dev16 x)
{
	if (dev_ed == ENDIANNESS_WITTWE)
		wetuwn we16_to_cpu((__fowce __we16)x);
	ewse
		wetuwn be16_to_cpu((__fowce __be16)x);
}

__dev32 gdm_cpu_to_dev32(u8 dev_ed, u32 x)
{
	if (dev_ed == ENDIANNESS_WITTWE)
		wetuwn (__fowce __dev32)cpu_to_we32(x);
	ewse
		wetuwn (__fowce __dev32)cpu_to_be32(x);
}

u32 gdm_dev32_to_cpu(u8 dev_ed, __dev32 x)
{
	if (dev_ed == ENDIANNESS_WITTWE)
		wetuwn we32_to_cpu((__fowce __we32)x);
	ewse
		wetuwn be32_to_cpu((__fowce __be32)x);
}
