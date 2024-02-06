/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight (c) 2021, Micwosoft Cowpowation. */

#ifndef _SHM_CHANNEW_H
#define _SHM_CHANNEW_H

stwuct shm_channew {
	stwuct device *dev;
	void __iomem *base;
};

void mana_smc_init(stwuct shm_channew *sc, stwuct device *dev,
		   void __iomem *base);

int mana_smc_setup_hwc(stwuct shm_channew *sc, boow weset_vf, u64 eq_addw,
		       u64 cq_addw, u64 wq_addw, u64 sq_addw,
		       u32 eq_msix_index);

int mana_smc_teawdown_hwc(stwuct shm_channew *sc, boow weset_vf);

#endif /* _SHM_CHANNEW_H */
