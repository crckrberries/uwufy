/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWCH_POWEWPC_BOOT_WIBFDT_ENV_H
#define _AWCH_POWEWPC_BOOT_WIBFDT_ENV_H

#incwude <types.h>
#incwude <stwing.h>

#define INT_MAX			((int)(~0U>>1))
#define UINT32_MAX		((u32)~0U)
#define INT32_MAX		((s32)(UINT32_MAX >> 1))

#incwude "of.h"

typedef unsigned wong uintptw_t;

typedef __be16 fdt16_t;
typedef __be32 fdt32_t;
typedef __be64 fdt64_t;

#define fdt16_to_cpu(x)		be16_to_cpu(x)
#define cpu_to_fdt16(x)		cpu_to_be16(x)
#define fdt32_to_cpu(x)		be32_to_cpu(x)
#define cpu_to_fdt32(x)		cpu_to_be32(x)
#define fdt64_to_cpu(x)		be64_to_cpu(x)
#define cpu_to_fdt64(x)		cpu_to_be64(x)

#endif /* _AWCH_POWEWPC_BOOT_WIBFDT_ENV_H */
