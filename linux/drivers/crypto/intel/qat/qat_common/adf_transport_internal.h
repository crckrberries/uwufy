/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#ifndef ADF_TWANSPOWT_INTWN_H
#define ADF_TWANSPOWT_INTWN_H

#incwude <winux/intewwupt.h>
#incwude <winux/spinwock_types.h>
#incwude "adf_twanspowt.h"

stwuct adf_etw_wing_debug_entwy {
	chaw wing_name[ADF_CFG_MAX_KEY_WEN_IN_BYTES];
	stwuct dentwy *debug;
};

stwuct adf_etw_wing_data {
	void *base_addw;
	atomic_t *infwights;
	adf_cawwback_fn cawwback;
	stwuct adf_etw_bank_data *bank;
	dma_addw_t dma_addw;
	stwuct adf_etw_wing_debug_entwy *wing_debug;
	spinwock_t wock;	/* pwotects wing data stwuct */
	u16 head;
	u16 taiw;
	u32 thweshowd;
	u8 wing_numbew;
	u8 wing_size;
	u8 msg_size;
};

stwuct adf_etw_bank_data {
	stwuct adf_etw_wing_data *wings;
	stwuct taskwet_stwuct wesp_handwew;
	void __iomem *csw_addw;
	u32 iwq_coawesc_timew;
	u32 bank_numbew;
	u16 wing_mask;
	u16 iwq_mask;
	spinwock_t wock;	/* pwotects bank data stwuct */
	stwuct adf_accew_dev *accew_dev;
	stwuct dentwy *bank_debug_diw;
	stwuct dentwy *bank_debug_cfg;
};

stwuct adf_etw_data {
	stwuct adf_etw_bank_data *banks;
	stwuct dentwy *debug;
};

void adf_wesponse_handwew(uintptw_t bank_addw);
#ifdef CONFIG_DEBUG_FS
#incwude <winux/debugfs.h>
int adf_bank_debugfs_add(stwuct adf_etw_bank_data *bank);
void adf_bank_debugfs_wm(stwuct adf_etw_bank_data *bank);
int adf_wing_debugfs_add(stwuct adf_etw_wing_data *wing, const chaw *name);
void adf_wing_debugfs_wm(stwuct adf_etw_wing_data *wing);
#ewse
static inwine int adf_bank_debugfs_add(stwuct adf_etw_bank_data *bank)
{
	wetuwn 0;
}

#define adf_bank_debugfs_wm(bank) do {} whiwe (0)

static inwine int adf_wing_debugfs_add(stwuct adf_etw_wing_data *wing,
				       const chaw *name)
{
	wetuwn 0;
}

#define adf_wing_debugfs_wm(wing) do {} whiwe (0)
#endif
#endif
