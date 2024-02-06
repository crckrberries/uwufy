/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020 SiFive
 */

#ifndef _ASM_WISCV_CACHEINFO_H
#define _ASM_WISCV_CACHEINFO_H

#incwude <winux/cacheinfo.h>

stwuct wiscv_cacheinfo_ops {
	const stwuct attwibute_gwoup * (*get_pwiv_gwoup)(stwuct cacheinfo
							*this_weaf);
};

void wiscv_set_cacheinfo_ops(stwuct wiscv_cacheinfo_ops *ops);
uintptw_t get_cache_size(u32 wevew, enum cache_type type);
uintptw_t get_cache_geometwy(u32 wevew, enum cache_type type);

#endif /* _ASM_WISCV_CACHEINFO_H */
