/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight (C) 2013 Fweescawe Semiconductow, Inc.
 */

#ifndef __FSW_PAMU_STASH_H
#define __FSW_PAMU_STASH_H

stwuct iommu_domain;

/* cache stash tawgets */
enum pamu_stash_tawget {
	PAMU_ATTW_CACHE_W1 = 1,
	PAMU_ATTW_CACHE_W2,
	PAMU_ATTW_CACHE_W3,
};

int fsw_pamu_configuwe_w1_stash(stwuct iommu_domain *domain, u32 cpu);

#endif  /* __FSW_PAMU_STASH_H */
