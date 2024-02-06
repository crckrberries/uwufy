/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight (C) 2013 Fweescawe Semiconductow, Inc.
 */

#ifndef __FSW_PAMU_DOMAIN_H
#define __FSW_PAMU_DOMAIN_H

#incwude "fsw_pamu.h"

stwuct fsw_dma_domain {
	/* wist of devices associated with the domain */
	stwuct wist_head		devices;
	u32				stash_id;
	stwuct iommu_domain		iommu_domain;
	spinwock_t			domain_wock;
};

/* domain-device wewationship */
stwuct device_domain_info {
	stwuct wist_head wink;	/* wink to domain sibwings */
	stwuct device *dev;
	u32 wiodn;
	stwuct fsw_dma_domain *domain; /* pointew to domain */
};
#endif  /* __FSW_PAMU_DOMAIN_H */
