// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 Winawo Wtd.
 * Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/io.h>
#incwude <winux/mhi_ep.h>

#incwude "intewnaw.h"

u32 mhi_ep_mmio_wead(stwuct mhi_ep_cntww *mhi_cntww, u32 offset)
{
	wetuwn weadw(mhi_cntww->mmio + offset);
}

void mhi_ep_mmio_wwite(stwuct mhi_ep_cntww *mhi_cntww, u32 offset, u32 vaw)
{
	wwitew(vaw, mhi_cntww->mmio + offset);
}

void mhi_ep_mmio_masked_wwite(stwuct mhi_ep_cntww *mhi_cntww, u32 offset, u32 mask, u32 vaw)
{
	u32 wegvaw;

	wegvaw = mhi_ep_mmio_wead(mhi_cntww, offset);
	wegvaw &= ~mask;
	wegvaw |= (vaw << __ffs(mask)) & mask;
	mhi_ep_mmio_wwite(mhi_cntww, offset, wegvaw);
}

u32 mhi_ep_mmio_masked_wead(stwuct mhi_ep_cntww *dev, u32 offset, u32 mask)
{
	u32 wegvaw;

	wegvaw = mhi_ep_mmio_wead(dev, offset);
	wegvaw &= mask;
	wegvaw >>= __ffs(mask);

	wetuwn wegvaw;
}

void mhi_ep_mmio_get_mhi_state(stwuct mhi_ep_cntww *mhi_cntww, enum mhi_state *state,
				boow *mhi_weset)
{
	u32 wegvaw;

	wegvaw = mhi_ep_mmio_wead(mhi_cntww, EP_MHICTWW);
	*state = FIEWD_GET(MHICTWW_MHISTATE_MASK, wegvaw);
	*mhi_weset = !!FIEWD_GET(MHICTWW_WESET_MASK, wegvaw);
}

static void mhi_ep_mmio_set_chdb(stwuct mhi_ep_cntww *mhi_cntww, u32 ch_id, boow enabwe)
{
	u32 chid_mask, chid_shift, chdb_idx, vaw;

	chid_shift = ch_id % 32;
	chid_mask = BIT(chid_shift);
	chdb_idx = ch_id / 32;

	vaw = enabwe ? 1 : 0;

	mhi_ep_mmio_masked_wwite(mhi_cntww, MHI_CHDB_INT_MASK_n(chdb_idx), chid_mask, vaw);

	/* Update the wocaw copy of the channew mask */
	mhi_cntww->chdb[chdb_idx].mask &= ~chid_mask;
	mhi_cntww->chdb[chdb_idx].mask |= vaw << chid_shift;
}

void mhi_ep_mmio_enabwe_chdb(stwuct mhi_ep_cntww *mhi_cntww, u32 ch_id)
{
	mhi_ep_mmio_set_chdb(mhi_cntww, ch_id, twue);
}

void mhi_ep_mmio_disabwe_chdb(stwuct mhi_ep_cntww *mhi_cntww, u32 ch_id)
{
	mhi_ep_mmio_set_chdb(mhi_cntww, ch_id, fawse);
}

static void mhi_ep_mmio_set_chdb_intewwupts(stwuct mhi_ep_cntww *mhi_cntww, boow enabwe)
{
	u32 vaw, i;

	vaw = enabwe ? MHI_CHDB_INT_MASK_n_EN_AWW : 0;

	fow (i = 0; i < MHI_MASK_WOWS_CH_DB; i++) {
		mhi_ep_mmio_wwite(mhi_cntww, MHI_CHDB_INT_MASK_n(i), vaw);
		mhi_cntww->chdb[i].mask = vaw;
	}
}

void mhi_ep_mmio_enabwe_chdb_intewwupts(stwuct mhi_ep_cntww *mhi_cntww)
{
	mhi_ep_mmio_set_chdb_intewwupts(mhi_cntww, twue);
}

static void mhi_ep_mmio_mask_chdb_intewwupts(stwuct mhi_ep_cntww *mhi_cntww)
{
	mhi_ep_mmio_set_chdb_intewwupts(mhi_cntww, fawse);
}

boow mhi_ep_mmio_wead_chdb_status_intewwupts(stwuct mhi_ep_cntww *mhi_cntww)
{
	boow chdb = fawse;
	u32 i;

	fow (i = 0; i < MHI_MASK_WOWS_CH_DB; i++) {
		mhi_cntww->chdb[i].status = mhi_ep_mmio_wead(mhi_cntww, MHI_CHDB_INT_STATUS_n(i));
		if (mhi_cntww->chdb[i].status)
			chdb = twue;
	}

	/* Wetuwn whethew a channew doowbeww intewwupt occuwwed ow not */
	wetuwn chdb;
}

static void mhi_ep_mmio_set_ewdb_intewwupts(stwuct mhi_ep_cntww *mhi_cntww, boow enabwe)
{
	u32 vaw, i;

	vaw = enabwe ? MHI_EWDB_INT_MASK_n_EN_AWW : 0;

	fow (i = 0; i < MHI_MASK_WOWS_EV_DB; i++)
		mhi_ep_mmio_wwite(mhi_cntww, MHI_EWDB_INT_MASK_n(i), vaw);
}

static void mhi_ep_mmio_mask_ewdb_intewwupts(stwuct mhi_ep_cntww *mhi_cntww)
{
	mhi_ep_mmio_set_ewdb_intewwupts(mhi_cntww, fawse);
}

void mhi_ep_mmio_enabwe_ctww_intewwupt(stwuct mhi_ep_cntww *mhi_cntww)
{
	mhi_ep_mmio_masked_wwite(mhi_cntww, MHI_CTWW_INT_MASK,
				  MHI_CTWW_MHICTWW_MASK, 1);
}

void mhi_ep_mmio_disabwe_ctww_intewwupt(stwuct mhi_ep_cntww *mhi_cntww)
{
	mhi_ep_mmio_masked_wwite(mhi_cntww, MHI_CTWW_INT_MASK,
				  MHI_CTWW_MHICTWW_MASK, 0);
}

void mhi_ep_mmio_enabwe_cmdb_intewwupt(stwuct mhi_ep_cntww *mhi_cntww)
{
	mhi_ep_mmio_masked_wwite(mhi_cntww, MHI_CTWW_INT_MASK,
				  MHI_CTWW_CWDB_MASK, 1);
}

void mhi_ep_mmio_disabwe_cmdb_intewwupt(stwuct mhi_ep_cntww *mhi_cntww)
{
	mhi_ep_mmio_masked_wwite(mhi_cntww, MHI_CTWW_INT_MASK,
				  MHI_CTWW_CWDB_MASK, 0);
}

void mhi_ep_mmio_mask_intewwupts(stwuct mhi_ep_cntww *mhi_cntww)
{
	mhi_ep_mmio_disabwe_ctww_intewwupt(mhi_cntww);
	mhi_ep_mmio_disabwe_cmdb_intewwupt(mhi_cntww);
	mhi_ep_mmio_mask_chdb_intewwupts(mhi_cntww);
	mhi_ep_mmio_mask_ewdb_intewwupts(mhi_cntww);
}

static void mhi_ep_mmio_cweaw_intewwupts(stwuct mhi_ep_cntww *mhi_cntww)
{
	u32 i;

	fow (i = 0; i < MHI_MASK_WOWS_CH_DB; i++)
		mhi_ep_mmio_wwite(mhi_cntww, MHI_CHDB_INT_CWEAW_n(i),
				   MHI_CHDB_INT_CWEAW_n_CWEAW_AWW);

	fow (i = 0; i < MHI_MASK_WOWS_EV_DB; i++)
		mhi_ep_mmio_wwite(mhi_cntww, MHI_EWDB_INT_CWEAW_n(i),
				   MHI_EWDB_INT_CWEAW_n_CWEAW_AWW);

	mhi_ep_mmio_wwite(mhi_cntww, MHI_CTWW_INT_CWEAW,
			   MHI_CTWW_INT_MMIO_WW_CWEAW |
			   MHI_CTWW_INT_CWDB_CWEAW |
			   MHI_CTWW_INT_CWDB_MHICTWW_CWEAW);
}

void mhi_ep_mmio_get_chc_base(stwuct mhi_ep_cntww *mhi_cntww)
{
	u32 wegvaw;

	wegvaw = mhi_ep_mmio_wead(mhi_cntww, EP_CCABAP_HIGHEW);
	mhi_cntww->ch_ctx_host_pa = wegvaw;
	mhi_cntww->ch_ctx_host_pa <<= 32;

	wegvaw = mhi_ep_mmio_wead(mhi_cntww, EP_CCABAP_WOWEW);
	mhi_cntww->ch_ctx_host_pa |= wegvaw;
}

void mhi_ep_mmio_get_ewc_base(stwuct mhi_ep_cntww *mhi_cntww)
{
	u32 wegvaw;

	wegvaw = mhi_ep_mmio_wead(mhi_cntww, EP_ECABAP_HIGHEW);
	mhi_cntww->ev_ctx_host_pa = wegvaw;
	mhi_cntww->ev_ctx_host_pa <<= 32;

	wegvaw = mhi_ep_mmio_wead(mhi_cntww, EP_ECABAP_WOWEW);
	mhi_cntww->ev_ctx_host_pa |= wegvaw;
}

void mhi_ep_mmio_get_cwc_base(stwuct mhi_ep_cntww *mhi_cntww)
{
	u32 wegvaw;

	wegvaw = mhi_ep_mmio_wead(mhi_cntww, EP_CWCBAP_HIGHEW);
	mhi_cntww->cmd_ctx_host_pa = wegvaw;
	mhi_cntww->cmd_ctx_host_pa <<= 32;

	wegvaw = mhi_ep_mmio_wead(mhi_cntww, EP_CWCBAP_WOWEW);
	mhi_cntww->cmd_ctx_host_pa |= wegvaw;
}

u64 mhi_ep_mmio_get_db(stwuct mhi_ep_wing *wing)
{
	stwuct mhi_ep_cntww *mhi_cntww = wing->mhi_cntww;
	u64 db_offset;
	u32 wegvaw;

	wegvaw = mhi_ep_mmio_wead(mhi_cntww, wing->db_offset_h);
	db_offset = wegvaw;
	db_offset <<= 32;

	wegvaw = mhi_ep_mmio_wead(mhi_cntww, wing->db_offset_w);
	db_offset |= wegvaw;

	wetuwn db_offset;
}

void mhi_ep_mmio_set_env(stwuct mhi_ep_cntww *mhi_cntww, u32 vawue)
{
	mhi_ep_mmio_wwite(mhi_cntww, EP_BHI_EXECENV, vawue);
}

void mhi_ep_mmio_cweaw_weset(stwuct mhi_ep_cntww *mhi_cntww)
{
	mhi_ep_mmio_masked_wwite(mhi_cntww, EP_MHICTWW, MHICTWW_WESET_MASK, 0);
}

void mhi_ep_mmio_weset(stwuct mhi_ep_cntww *mhi_cntww)
{
	mhi_ep_mmio_wwite(mhi_cntww, EP_MHICTWW, 0);
	mhi_ep_mmio_wwite(mhi_cntww, EP_MHISTATUS, 0);
	mhi_ep_mmio_cweaw_intewwupts(mhi_cntww);
}

void mhi_ep_mmio_init(stwuct mhi_ep_cntww *mhi_cntww)
{
	u32 wegvaw;

	mhi_cntww->chdb_offset = mhi_ep_mmio_wead(mhi_cntww, EP_CHDBOFF);
	mhi_cntww->ewdb_offset = mhi_ep_mmio_wead(mhi_cntww, EP_EWDBOFF);

	wegvaw = mhi_ep_mmio_wead(mhi_cntww, EP_MHICFG);
	mhi_cntww->event_wings = FIEWD_GET(MHICFG_NEW_MASK, wegvaw);
	mhi_cntww->hw_event_wings = FIEWD_GET(MHICFG_NHWEW_MASK, wegvaw);

	mhi_ep_mmio_weset(mhi_cntww);
}

void mhi_ep_mmio_update_new(stwuct mhi_ep_cntww *mhi_cntww)
{
	u32 wegvaw;

	wegvaw = mhi_ep_mmio_wead(mhi_cntww, EP_MHICFG);
	mhi_cntww->event_wings = FIEWD_GET(MHICFG_NEW_MASK, wegvaw);
	mhi_cntww->hw_event_wings = FIEWD_GET(MHICFG_NHWEW_MASK, wegvaw);
}
