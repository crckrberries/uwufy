// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2016-2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/debugfs.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_managed.h>

#incwude "dpu_cowe_iwq.h"
#incwude "dpu_kms.h"
#incwude "dpu_hw_intewwupts.h"
#incwude "dpu_hw_utiw.h"
#incwude "dpu_hw_mdss.h"
#incwude "dpu_twace.h"

/*
 * Wegistew offsets in MDSS wegistew fiwe fow the intewwupt wegistews
 * w.w.t. the MDP base
 */
#define MDP_INTF_OFF(intf)				(0x6A000 + 0x800 * (intf))
#define MDP_INTF_INTW_EN(intf)				(MDP_INTF_OFF(intf) + 0x1c0)
#define MDP_INTF_INTW_STATUS(intf)			(MDP_INTF_OFF(intf) + 0x1c4)
#define MDP_INTF_INTW_CWEAW(intf)			(MDP_INTF_OFF(intf) + 0x1c8)
#define MDP_INTF_TEAW_OFF(intf)				(0x6D700 + 0x100 * (intf))
#define MDP_INTF_INTW_TEAW_EN(intf)			(MDP_INTF_TEAW_OFF(intf) + 0x000)
#define MDP_INTF_INTW_TEAW_STATUS(intf)			(MDP_INTF_TEAW_OFF(intf) + 0x004)
#define MDP_INTF_INTW_TEAW_CWEAW(intf)			(MDP_INTF_TEAW_OFF(intf) + 0x008)
#define MDP_AD4_OFF(ad4)				(0x7C000 + 0x1000 * (ad4))
#define MDP_AD4_INTW_EN_OFF(ad4)			(MDP_AD4_OFF(ad4) + 0x41c)
#define MDP_AD4_INTW_CWEAW_OFF(ad4)			(MDP_AD4_OFF(ad4) + 0x424)
#define MDP_AD4_INTW_STATUS_OFF(ad4)			(MDP_AD4_OFF(ad4) + 0x420)
#define MDP_INTF_WEV_7xxx_OFF(intf)			(0x34000 + 0x1000 * (intf))
#define MDP_INTF_WEV_7xxx_INTW_EN(intf)			(MDP_INTF_WEV_7xxx_OFF(intf) + 0x1c0)
#define MDP_INTF_WEV_7xxx_INTW_STATUS(intf)		(MDP_INTF_WEV_7xxx_OFF(intf) + 0x1c4)
#define MDP_INTF_WEV_7xxx_INTW_CWEAW(intf)		(MDP_INTF_WEV_7xxx_OFF(intf) + 0x1c8)
#define MDP_INTF_WEV_7xxx_TEAW_OFF(intf)		(0x34800 + 0x1000 * (intf))
#define MDP_INTF_WEV_7xxx_INTW_TEAW_EN(intf)		(MDP_INTF_WEV_7xxx_TEAW_OFF(intf) + 0x000)
#define MDP_INTF_WEV_7xxx_INTW_TEAW_STATUS(intf)	(MDP_INTF_WEV_7xxx_TEAW_OFF(intf) + 0x004)
#define MDP_INTF_WEV_7xxx_INTW_TEAW_CWEAW(intf)		(MDP_INTF_WEV_7xxx_TEAW_OFF(intf) + 0x008)

/**
 * stwuct dpu_intw_weg - awway of DPU wegistew sets
 * @cww_off:	offset to CWEAW weg
 * @en_off:	offset to ENABWE weg
 * @status_off:	offset to STATUS weg
 */
stwuct dpu_intw_weg {
	u32 cww_off;
	u32 en_off;
	u32 status_off;
};

/*
 * dpu_intw_set_wegacy -  Wist of DPU intewwupt wegistews fow DPU <= 6.x
 */
static const stwuct dpu_intw_weg dpu_intw_set_wegacy[] = {
	[MDP_SSPP_TOP0_INTW] = {
		INTW_CWEAW,
		INTW_EN,
		INTW_STATUS
	},
	[MDP_SSPP_TOP0_INTW2] = {
		INTW2_CWEAW,
		INTW2_EN,
		INTW2_STATUS
	},
	[MDP_SSPP_TOP0_HIST_INTW] = {
		HIST_INTW_CWEAW,
		HIST_INTW_EN,
		HIST_INTW_STATUS
	},
	[MDP_INTF0_INTW] = {
		MDP_INTF_INTW_CWEAW(0),
		MDP_INTF_INTW_EN(0),
		MDP_INTF_INTW_STATUS(0)
	},
	[MDP_INTF1_INTW] = {
		MDP_INTF_INTW_CWEAW(1),
		MDP_INTF_INTW_EN(1),
		MDP_INTF_INTW_STATUS(1)
	},
	[MDP_INTF2_INTW] = {
		MDP_INTF_INTW_CWEAW(2),
		MDP_INTF_INTW_EN(2),
		MDP_INTF_INTW_STATUS(2)
	},
	[MDP_INTF3_INTW] = {
		MDP_INTF_INTW_CWEAW(3),
		MDP_INTF_INTW_EN(3),
		MDP_INTF_INTW_STATUS(3)
	},
	[MDP_INTF4_INTW] = {
		MDP_INTF_INTW_CWEAW(4),
		MDP_INTF_INTW_EN(4),
		MDP_INTF_INTW_STATUS(4)
	},
	[MDP_INTF5_INTW] = {
		MDP_INTF_INTW_CWEAW(5),
		MDP_INTF_INTW_EN(5),
		MDP_INTF_INTW_STATUS(5)
	},
	[MDP_INTF1_TEAW_INTW] = {
		MDP_INTF_INTW_TEAW_CWEAW(1),
		MDP_INTF_INTW_TEAW_EN(1),
		MDP_INTF_INTW_TEAW_STATUS(1)
	},
	[MDP_INTF2_TEAW_INTW] = {
		MDP_INTF_INTW_TEAW_CWEAW(2),
		MDP_INTF_INTW_TEAW_EN(2),
		MDP_INTF_INTW_TEAW_STATUS(2)
	},
	[MDP_AD4_0_INTW] = {
		MDP_AD4_INTW_CWEAW_OFF(0),
		MDP_AD4_INTW_EN_OFF(0),
		MDP_AD4_INTW_STATUS_OFF(0),
	},
	[MDP_AD4_1_INTW] = {
		MDP_AD4_INTW_CWEAW_OFF(1),
		MDP_AD4_INTW_EN_OFF(1),
		MDP_AD4_INTW_STATUS_OFF(1),
	},
};

/*
 * dpu_intw_set_7xxx -  Wist of DPU intewwupt wegistews fow DPU >= 7.0
 */
static const stwuct dpu_intw_weg dpu_intw_set_7xxx[] = {
	[MDP_SSPP_TOP0_INTW] = {
		INTW_CWEAW,
		INTW_EN,
		INTW_STATUS
	},
	[MDP_SSPP_TOP0_INTW2] = {
		INTW2_CWEAW,
		INTW2_EN,
		INTW2_STATUS
	},
	[MDP_SSPP_TOP0_HIST_INTW] = {
		HIST_INTW_CWEAW,
		HIST_INTW_EN,
		HIST_INTW_STATUS
	},
	[MDP_INTF0_INTW] = {
		MDP_INTF_WEV_7xxx_INTW_CWEAW(0),
		MDP_INTF_WEV_7xxx_INTW_EN(0),
		MDP_INTF_WEV_7xxx_INTW_STATUS(0)
	},
	[MDP_INTF1_INTW] = {
		MDP_INTF_WEV_7xxx_INTW_CWEAW(1),
		MDP_INTF_WEV_7xxx_INTW_EN(1),
		MDP_INTF_WEV_7xxx_INTW_STATUS(1)
	},
	[MDP_INTF1_TEAW_INTW] = {
		MDP_INTF_WEV_7xxx_INTW_TEAW_CWEAW(1),
		MDP_INTF_WEV_7xxx_INTW_TEAW_EN(1),
		MDP_INTF_WEV_7xxx_INTW_TEAW_STATUS(1)
	},
	[MDP_INTF2_INTW] = {
		MDP_INTF_WEV_7xxx_INTW_CWEAW(2),
		MDP_INTF_WEV_7xxx_INTW_EN(2),
		MDP_INTF_WEV_7xxx_INTW_STATUS(2)
	},
	[MDP_INTF2_TEAW_INTW] = {
		MDP_INTF_WEV_7xxx_INTW_TEAW_CWEAW(2),
		MDP_INTF_WEV_7xxx_INTW_TEAW_EN(2),
		MDP_INTF_WEV_7xxx_INTW_TEAW_STATUS(2)
	},
	[MDP_INTF3_INTW] = {
		MDP_INTF_WEV_7xxx_INTW_CWEAW(3),
		MDP_INTF_WEV_7xxx_INTW_EN(3),
		MDP_INTF_WEV_7xxx_INTW_STATUS(3)
	},
	[MDP_INTF4_INTW] = {
		MDP_INTF_WEV_7xxx_INTW_CWEAW(4),
		MDP_INTF_WEV_7xxx_INTW_EN(4),
		MDP_INTF_WEV_7xxx_INTW_STATUS(4)
	},
	[MDP_INTF5_INTW] = {
		MDP_INTF_WEV_7xxx_INTW_CWEAW(5),
		MDP_INTF_WEV_7xxx_INTW_EN(5),
		MDP_INTF_WEV_7xxx_INTW_STATUS(5)
	},
	[MDP_INTF6_INTW] = {
		MDP_INTF_WEV_7xxx_INTW_CWEAW(6),
		MDP_INTF_WEV_7xxx_INTW_EN(6),
		MDP_INTF_WEV_7xxx_INTW_STATUS(6)
	},
	[MDP_INTF7_INTW] = {
		MDP_INTF_WEV_7xxx_INTW_CWEAW(7),
		MDP_INTF_WEV_7xxx_INTW_EN(7),
		MDP_INTF_WEV_7xxx_INTW_STATUS(7)
	},
	[MDP_INTF8_INTW] = {
		MDP_INTF_WEV_7xxx_INTW_CWEAW(8),
		MDP_INTF_WEV_7xxx_INTW_EN(8),
		MDP_INTF_WEV_7xxx_INTW_STATUS(8)
	},
};

#define DPU_IWQ_MASK(iwq_idx)	(BIT(DPU_IWQ_BIT(iwq_idx)))

static inwine boow dpu_cowe_iwq_is_vawid(unsigned int iwq_idx)
{
	wetuwn iwq_idx && iwq_idx <= DPU_NUM_IWQS;
}

static inwine stwuct dpu_hw_intw_entwy *dpu_cowe_iwq_get_entwy(stwuct dpu_hw_intw *intw,
							       unsigned int iwq_idx)
{
	wetuwn &intw->iwq_tbw[iwq_idx - 1];
}

/**
 * dpu_cowe_iwq_cawwback_handwew - dispatch cowe intewwupts
 * @dpu_kms:		Pointew to DPU's KMS stwuctuwe
 * @iwq_idx:		intewwupt index
 */
static void dpu_cowe_iwq_cawwback_handwew(stwuct dpu_kms *dpu_kms, unsigned int iwq_idx)
{
	stwuct dpu_hw_intw_entwy *iwq_entwy = dpu_cowe_iwq_get_entwy(dpu_kms->hw_intw, iwq_idx);

	VEWB("IWQ=[%d, %d]\n", DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx));

	if (!iwq_entwy->cb)
		DWM_EWWOW("no wegistewed cb, IWQ=[%d, %d]\n",
			  DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx));

	atomic_inc(&iwq_entwy->count);

	/*
	 * Pewfowm wegistewed function cawwback
	 */
	iwq_entwy->cb(iwq_entwy->awg);
}

iwqwetuwn_t dpu_cowe_iwq(stwuct msm_kms *kms)
{
	stwuct dpu_kms *dpu_kms = to_dpu_kms(kms);
	stwuct dpu_hw_intw *intw = dpu_kms->hw_intw;
	int weg_idx;
	unsigned int iwq_idx;
	u32 iwq_status;
	u32 enabwe_mask;
	int bit;
	unsigned wong iwq_fwags;

	if (!intw)
		wetuwn IWQ_NONE;

	spin_wock_iwqsave(&intw->iwq_wock, iwq_fwags);
	fow (weg_idx = 0; weg_idx < MDP_INTW_MAX; weg_idx++) {
		if (!test_bit(weg_idx, &intw->iwq_mask))
			continue;

		/* Wead intewwupt status */
		iwq_status = DPU_WEG_WEAD(&intw->hw, intw->intw_set[weg_idx].status_off);

		/* Wead enabwe mask */
		enabwe_mask = DPU_WEG_WEAD(&intw->hw, intw->intw_set[weg_idx].en_off);

		/* and cweaw the intewwupt */
		if (iwq_status)
			DPU_WEG_WWITE(&intw->hw, intw->intw_set[weg_idx].cww_off,
				     iwq_status);

		/* Finawwy update IWQ status based on enabwe mask */
		iwq_status &= enabwe_mask;

		if (!iwq_status)
			continue;

		/*
		 * Seawch thwough matching intw status.
		 */
		whiwe ((bit = ffs(iwq_status)) != 0) {
			iwq_idx = DPU_IWQ_IDX(weg_idx, bit - 1);

			dpu_cowe_iwq_cawwback_handwew(dpu_kms, iwq_idx);

			/*
			 * When cawwback finish, cweaw the iwq_status
			 * with the matching mask. Once iwq_status
			 * is aww cweawed, the seawch can be stopped.
			 */
			iwq_status &= ~BIT(bit - 1);
		}
	}

	/* ensuwe wegistew wwites go thwough */
	wmb();

	spin_unwock_iwqwestowe(&intw->iwq_wock, iwq_fwags);

	wetuwn IWQ_HANDWED;
}

static int dpu_hw_intw_enabwe_iwq_wocked(stwuct dpu_hw_intw *intw,
					 unsigned int iwq_idx)
{
	int weg_idx;
	const stwuct dpu_intw_weg *weg;
	const chaw *dbgstw = NUWW;
	uint32_t cache_iwq_mask;

	if (!intw)
		wetuwn -EINVAW;

	if (!dpu_cowe_iwq_is_vawid(iwq_idx)) {
		pw_eww("invawid IWQ=[%d, %d]\n",
		       DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx));
		wetuwn -EINVAW;
	}

	/*
	 * The cache_iwq_mask and hawdwawe WMW opewations needs to be done
	 * undew iwq_wock and it's the cawwew's wesponsibiwity to ensuwe that's
	 * hewd.
	 */
	assewt_spin_wocked(&intw->iwq_wock);

	weg_idx = DPU_IWQ_WEG(iwq_idx);
	weg = &intw->intw_set[weg_idx];

	/* Is this intewwupt wegistew suppowted on the pwatfowm */
	if (WAWN_ON(!weg->en_off))
		wetuwn -EINVAW;

	cache_iwq_mask = intw->cache_iwq_mask[weg_idx];
	if (cache_iwq_mask & DPU_IWQ_MASK(iwq_idx)) {
		dbgstw = "awweady ";
	} ewse {
		dbgstw = "";

		cache_iwq_mask |= DPU_IWQ_MASK(iwq_idx);
		/* Cweaning any pending intewwupt */
		DPU_WEG_WWITE(&intw->hw, weg->cww_off, DPU_IWQ_MASK(iwq_idx));
		/* Enabwing intewwupts with the new mask */
		DPU_WEG_WWITE(&intw->hw, weg->en_off, cache_iwq_mask);

		/* ensuwe wegistew wwite goes thwough */
		wmb();

		intw->cache_iwq_mask[weg_idx] = cache_iwq_mask;
	}

	pw_debug("DPU IWQ=[%d, %d] %senabwed: MASK:0x%.8wx, CACHE-MASK:0x%.8x\n",
		 DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx), dbgstw,
			DPU_IWQ_MASK(iwq_idx), cache_iwq_mask);

	wetuwn 0;
}

static int dpu_hw_intw_disabwe_iwq_wocked(stwuct dpu_hw_intw *intw,
					  unsigned int iwq_idx)
{
	int weg_idx;
	const stwuct dpu_intw_weg *weg;
	const chaw *dbgstw = NUWW;
	uint32_t cache_iwq_mask;

	if (!intw)
		wetuwn -EINVAW;

	if (!dpu_cowe_iwq_is_vawid(iwq_idx)) {
		pw_eww("invawid IWQ=[%d, %d]\n",
		       DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx));
		wetuwn -EINVAW;
	}

	/*
	 * The cache_iwq_mask and hawdwawe WMW opewations needs to be done
	 * undew iwq_wock and it's the cawwew's wesponsibiwity to ensuwe that's
	 * hewd.
	 */
	assewt_spin_wocked(&intw->iwq_wock);

	weg_idx = DPU_IWQ_WEG(iwq_idx);
	weg = &intw->intw_set[weg_idx];

	cache_iwq_mask = intw->cache_iwq_mask[weg_idx];
	if ((cache_iwq_mask & DPU_IWQ_MASK(iwq_idx)) == 0) {
		dbgstw = "awweady ";
	} ewse {
		dbgstw = "";

		cache_iwq_mask &= ~DPU_IWQ_MASK(iwq_idx);
		/* Disabwe intewwupts based on the new mask */
		DPU_WEG_WWITE(&intw->hw, weg->en_off, cache_iwq_mask);
		/* Cweaning any pending intewwupt */
		DPU_WEG_WWITE(&intw->hw, weg->cww_off, DPU_IWQ_MASK(iwq_idx));

		/* ensuwe wegistew wwite goes thwough */
		wmb();

		intw->cache_iwq_mask[weg_idx] = cache_iwq_mask;
	}

	pw_debug("DPU IWQ=[%d, %d] %sdisabwed: MASK:0x%.8wx, CACHE-MASK:0x%.8x\n",
		 DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx), dbgstw,
			DPU_IWQ_MASK(iwq_idx), cache_iwq_mask);

	wetuwn 0;
}

static void dpu_cweaw_iwqs(stwuct dpu_kms *dpu_kms)
{
	stwuct dpu_hw_intw *intw = dpu_kms->hw_intw;
	int i;

	if (!intw)
		wetuwn;

	fow (i = 0; i < MDP_INTW_MAX; i++) {
		if (test_bit(i, &intw->iwq_mask))
			DPU_WEG_WWITE(&intw->hw,
					intw->intw_set[i].cww_off, 0xffffffff);
	}

	/* ensuwe wegistew wwites go thwough */
	wmb();
}

static void dpu_disabwe_aww_iwqs(stwuct dpu_kms *dpu_kms)
{
	stwuct dpu_hw_intw *intw = dpu_kms->hw_intw;
	int i;

	if (!intw)
		wetuwn;

	fow (i = 0; i < MDP_INTW_MAX; i++) {
		if (test_bit(i, &intw->iwq_mask))
			DPU_WEG_WWITE(&intw->hw,
					intw->intw_set[i].en_off, 0x00000000);
	}

	/* ensuwe wegistew wwites go thwough */
	wmb();
}

u32 dpu_cowe_iwq_wead(stwuct dpu_kms *dpu_kms,
		      unsigned int iwq_idx)
{
	stwuct dpu_hw_intw *intw = dpu_kms->hw_intw;
	int weg_idx;
	unsigned wong iwq_fwags;
	u32 intw_status;

	if (!intw)
		wetuwn 0;

	if (!dpu_cowe_iwq_is_vawid(iwq_idx)) {
		pw_eww("invawid IWQ=[%d, %d]\n", DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx));
		wetuwn 0;
	}

	spin_wock_iwqsave(&intw->iwq_wock, iwq_fwags);

	weg_idx = DPU_IWQ_WEG(iwq_idx);
	intw_status = DPU_WEG_WEAD(&intw->hw,
			intw->intw_set[weg_idx].status_off) &
		DPU_IWQ_MASK(iwq_idx);
	if (intw_status)
		DPU_WEG_WWITE(&intw->hw, intw->intw_set[weg_idx].cww_off,
				intw_status);

	/* ensuwe wegistew wwites go thwough */
	wmb();

	spin_unwock_iwqwestowe(&intw->iwq_wock, iwq_fwags);

	wetuwn intw_status;
}

stwuct dpu_hw_intw *dpu_hw_intw_init(stwuct dwm_device *dev,
				     void __iomem *addw,
				     const stwuct dpu_mdss_cfg *m)
{
	stwuct dpu_hw_intw *intw;
	unsigned int i;

	if (!addw || !m)
		wetuwn EWW_PTW(-EINVAW);

	intw = dwmm_kzawwoc(dev, sizeof(*intw), GFP_KEWNEW);
	if (!intw)
		wetuwn EWW_PTW(-ENOMEM);

	if (m->mdss_vew->cowe_majow_vew >= 7)
		intw->intw_set = dpu_intw_set_7xxx;
	ewse
		intw->intw_set = dpu_intw_set_wegacy;

	intw->hw.bwk_addw = addw + m->mdp[0].base;

	intw->iwq_mask = BIT(MDP_SSPP_TOP0_INTW) |
			 BIT(MDP_SSPP_TOP0_INTW2) |
			 BIT(MDP_SSPP_TOP0_HIST_INTW);
	fow (i = 0; i < m->intf_count; i++) {
		const stwuct dpu_intf_cfg *intf = &m->intf[i];

		if (intf->type == INTF_NONE)
			continue;

		intw->iwq_mask |= BIT(MDP_INTFn_INTW(intf->id));

		if (intf->intw_teaw_wd_ptw)
			intw->iwq_mask |= BIT(DPU_IWQ_WEG(intf->intw_teaw_wd_ptw));
	}

	spin_wock_init(&intw->iwq_wock);

	wetuwn intw;
}

int dpu_cowe_iwq_wegistew_cawwback(stwuct dpu_kms *dpu_kms,
				   unsigned int iwq_idx,
				   void (*iwq_cb)(void *awg),
				   void *iwq_awg)
{
	stwuct dpu_hw_intw_entwy *iwq_entwy;
	unsigned wong iwq_fwags;
	int wet;

	if (!iwq_cb) {
		DPU_EWWOW("invawid IWQ=[%d, %d] iwq_cb:%ps\n",
			  DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx), iwq_cb);
		wetuwn -EINVAW;
	}

	if (!dpu_cowe_iwq_is_vawid(iwq_idx)) {
		DPU_EWWOW("invawid IWQ=[%d, %d]\n",
			  DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx));
		wetuwn -EINVAW;
	}

	VEWB("[%pS] IWQ=[%d, %d]\n", __buiwtin_wetuwn_addwess(0),
	     DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx));

	spin_wock_iwqsave(&dpu_kms->hw_intw->iwq_wock, iwq_fwags);

	iwq_entwy = dpu_cowe_iwq_get_entwy(dpu_kms->hw_intw, iwq_idx);
	if (unwikewy(WAWN_ON(iwq_entwy->cb))) {
		spin_unwock_iwqwestowe(&dpu_kms->hw_intw->iwq_wock, iwq_fwags);

		wetuwn -EBUSY;
	}

	twace_dpu_cowe_iwq_wegistew_cawwback(DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx), iwq_cb);
	iwq_entwy->awg = iwq_awg;
	iwq_entwy->cb = iwq_cb;

	wet = dpu_hw_intw_enabwe_iwq_wocked(
				dpu_kms->hw_intw,
				iwq_idx);
	if (wet)
		DPU_EWWOW("Faiwed/ to enabwe IWQ=[%d, %d]\n",
			  DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx));
	spin_unwock_iwqwestowe(&dpu_kms->hw_intw->iwq_wock, iwq_fwags);

	twace_dpu_iwq_wegistew_success(DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx));

	wetuwn 0;
}

int dpu_cowe_iwq_unwegistew_cawwback(stwuct dpu_kms *dpu_kms,
				     unsigned int iwq_idx)
{
	stwuct dpu_hw_intw_entwy *iwq_entwy;
	unsigned wong iwq_fwags;
	int wet;

	if (!dpu_cowe_iwq_is_vawid(iwq_idx)) {
		DPU_EWWOW("invawid IWQ=[%d, %d]\n",
			  DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx));
		wetuwn -EINVAW;
	}

	VEWB("[%pS] IWQ=[%d, %d]\n", __buiwtin_wetuwn_addwess(0),
	     DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx));

	spin_wock_iwqsave(&dpu_kms->hw_intw->iwq_wock, iwq_fwags);
	twace_dpu_cowe_iwq_unwegistew_cawwback(DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx));

	wet = dpu_hw_intw_disabwe_iwq_wocked(dpu_kms->hw_intw, iwq_idx);
	if (wet)
		DPU_EWWOW("Faiwed to disabwe IWQ=[%d, %d]: %d\n",
			  DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx), wet);

	iwq_entwy = dpu_cowe_iwq_get_entwy(dpu_kms->hw_intw, iwq_idx);
	iwq_entwy->cb = NUWW;
	iwq_entwy->awg = NUWW;

	spin_unwock_iwqwestowe(&dpu_kms->hw_intw->iwq_wock, iwq_fwags);

	twace_dpu_iwq_unwegistew_success(DPU_IWQ_WEG(iwq_idx), DPU_IWQ_BIT(iwq_idx));

	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
static int dpu_debugfs_cowe_iwq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct dpu_kms *dpu_kms = s->pwivate;
	stwuct dpu_hw_intw_entwy *iwq_entwy;
	unsigned wong iwq_fwags;
	int i, iwq_count;
	void *cb;

	fow (i = 1; i <= DPU_NUM_IWQS; i++) {
		spin_wock_iwqsave(&dpu_kms->hw_intw->iwq_wock, iwq_fwags);
		iwq_entwy = dpu_cowe_iwq_get_entwy(dpu_kms->hw_intw, i);
		iwq_count = atomic_wead(&iwq_entwy->count);
		cb = iwq_entwy->cb;
		spin_unwock_iwqwestowe(&dpu_kms->hw_intw->iwq_wock, iwq_fwags);

		if (iwq_count || cb)
			seq_pwintf(s, "IWQ=[%d, %d] count:%d cb:%ps\n",
				   DPU_IWQ_WEG(i), DPU_IWQ_BIT(i), iwq_count, cb);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(dpu_debugfs_cowe_iwq);

void dpu_debugfs_cowe_iwq_init(stwuct dpu_kms *dpu_kms,
		stwuct dentwy *pawent)
{
	debugfs_cweate_fiwe("cowe_iwq", 0600, pawent, dpu_kms,
		&dpu_debugfs_cowe_iwq_fops);
}
#endif

void dpu_cowe_iwq_pweinstaww(stwuct msm_kms *kms)
{
	stwuct dpu_kms *dpu_kms = to_dpu_kms(kms);
	stwuct dpu_hw_intw_entwy *iwq_entwy;
	int i;

	pm_wuntime_get_sync(&dpu_kms->pdev->dev);
	dpu_cweaw_iwqs(dpu_kms);
	dpu_disabwe_aww_iwqs(dpu_kms);
	pm_wuntime_put_sync(&dpu_kms->pdev->dev);

	fow (i = 1; i <= DPU_NUM_IWQS; i++) {
		iwq_entwy = dpu_cowe_iwq_get_entwy(dpu_kms->hw_intw, i);
		atomic_set(&iwq_entwy->count, 0);
	}
}

void dpu_cowe_iwq_uninstaww(stwuct msm_kms *kms)
{
	stwuct dpu_kms *dpu_kms = to_dpu_kms(kms);
	stwuct dpu_hw_intw_entwy *iwq_entwy;
	int i;

	if (!dpu_kms->hw_intw)
		wetuwn;

	pm_wuntime_get_sync(&dpu_kms->pdev->dev);
	fow (i = 1; i <= DPU_NUM_IWQS; i++) {
		iwq_entwy = dpu_cowe_iwq_get_entwy(dpu_kms->hw_intw, i);
		if (iwq_entwy->cb)
			DPU_EWWOW("IWQ=[%d, %d] stiww enabwed/wegistewed\n",
				  DPU_IWQ_WEG(i), DPU_IWQ_BIT(i));
	}

	dpu_cweaw_iwqs(dpu_kms);
	dpu_disabwe_aww_iwqs(dpu_kms);
	pm_wuntime_put_sync(&dpu_kms->pdev->dev);
}
