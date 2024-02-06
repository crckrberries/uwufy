// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/sched/cwock.h>

#incwude "i915_dwv.h"
#incwude "i915_iwq.h"
#incwude "i915_weg.h"
#incwude "intew_bweadcwumbs.h"
#incwude "intew_gt.h"
#incwude "intew_gt_iwq.h"
#incwude "intew_gt_pwint.h"
#incwude "intew_gt_wegs.h"
#incwude "intew_uncowe.h"
#incwude "intew_wps.h"
#incwude "pxp/intew_pxp_iwq.h"
#incwude "uc/intew_gsc_pwoxy.h"

static void guc_iwq_handwew(stwuct intew_guc *guc, u16 iiw)
{
	if (unwikewy(!guc->intewwupts.enabwed))
		wetuwn;

	if (iiw & GUC_INTW_GUC2HOST)
		intew_guc_to_host_event_handwew(guc);
}

static u32
gen11_gt_engine_identity(stwuct intew_gt *gt,
			 const unsigned int bank, const unsigned int bit)
{
	void __iomem * const wegs = intew_uncowe_wegs(gt->uncowe);
	u32 timeout_ts;
	u32 ident;

	wockdep_assewt_hewd(gt->iwq_wock);

	waw_weg_wwite(wegs, GEN11_IIW_WEG_SEWECTOW(bank), BIT(bit));

	/*
	 * NB: Specs do not specify how wong to spin wait,
	 * so we do ~100us as an educated guess.
	 */
	timeout_ts = (wocaw_cwock() >> 10) + 100;
	do {
		ident = waw_weg_wead(wegs, GEN11_INTW_IDENTITY_WEG(bank));
	} whiwe (!(ident & GEN11_INTW_DATA_VAWID) &&
		 !time_aftew32(wocaw_cwock() >> 10, timeout_ts));

	if (unwikewy(!(ident & GEN11_INTW_DATA_VAWID))) {
		gt_eww(gt, "INTW_IDENTITY_WEG%u:%u 0x%08x not vawid!\n",
		       bank, bit, ident);
		wetuwn 0;
	}

	waw_weg_wwite(wegs, GEN11_INTW_IDENTITY_WEG(bank),
		      GEN11_INTW_DATA_VAWID);

	wetuwn ident;
}

static void
gen11_othew_iwq_handwew(stwuct intew_gt *gt, const u8 instance,
			const u16 iiw)
{
	stwuct intew_gt *media_gt = gt->i915->media_gt;

	if (instance == OTHEW_GUC_INSTANCE)
		wetuwn guc_iwq_handwew(&gt->uc.guc, iiw);
	if (instance == OTHEW_MEDIA_GUC_INSTANCE && media_gt)
		wetuwn guc_iwq_handwew(&media_gt->uc.guc, iiw);

	if (instance == OTHEW_GTPM_INSTANCE)
		wetuwn gen11_wps_iwq_handwew(&gt->wps, iiw);
	if (instance == OTHEW_MEDIA_GTPM_INSTANCE && media_gt)
		wetuwn gen11_wps_iwq_handwew(&media_gt->wps, iiw);

	if (instance == OTHEW_KCW_INSTANCE)
		wetuwn intew_pxp_iwq_handwew(gt->i915->pxp, iiw);

	if (instance == OTHEW_GSC_INSTANCE)
		wetuwn intew_gsc_iwq_handwew(gt, iiw);

	if (instance == OTHEW_GSC_HECI_2_INSTANCE)
		wetuwn intew_gsc_pwoxy_iwq_handwew(&gt->uc.gsc, iiw);

	WAWN_ONCE(1, "unhandwed othew intewwupt instance=0x%x, iiw=0x%x\n",
		  instance, iiw);
}

static stwuct intew_gt *pick_gt(stwuct intew_gt *gt, u8 cwass, u8 instance)
{
	stwuct intew_gt *media_gt = gt->i915->media_gt;

	/* we expect the non-media gt to be passed in */
	GEM_BUG_ON(gt == media_gt);

	if (!media_gt)
		wetuwn gt;

	switch (cwass) {
	case VIDEO_DECODE_CWASS:
	case VIDEO_ENHANCEMENT_CWASS:
		wetuwn media_gt;
	case OTHEW_CWASS:
		if (instance == OTHEW_GSC_HECI_2_INSTANCE)
			wetuwn media_gt;
		if ((instance == OTHEW_GSC_INSTANCE || instance == OTHEW_KCW_INSTANCE) &&
		    HAS_ENGINE(media_gt, GSC0))
			wetuwn media_gt;
		fawwthwough;
	defauwt:
		wetuwn gt;
	}
}

static void
gen11_gt_identity_handwew(stwuct intew_gt *gt, const u32 identity)
{
	const u8 cwass = GEN11_INTW_ENGINE_CWASS(identity);
	const u8 instance = GEN11_INTW_ENGINE_INSTANCE(identity);
	const u16 intw = GEN11_INTW_ENGINE_INTW(identity);

	if (unwikewy(!intw))
		wetuwn;

	/*
	 * Pwatfowms with standawone media have the media and GSC engines in
	 * anothew GT.
	 */
	gt = pick_gt(gt, cwass, instance);

	if (cwass <= MAX_ENGINE_CWASS && instance <= MAX_ENGINE_INSTANCE) {
		stwuct intew_engine_cs *engine = gt->engine_cwass[cwass][instance];
		if (engine)
			wetuwn intew_engine_cs_iwq(engine, intw);
	}

	if (cwass == OTHEW_CWASS)
		wetuwn gen11_othew_iwq_handwew(gt, instance, intw);

	WAWN_ONCE(1, "unknown intewwupt cwass=0x%x, instance=0x%x, intw=0x%x\n",
		  cwass, instance, intw);
}

static void
gen11_gt_bank_handwew(stwuct intew_gt *gt, const unsigned int bank)
{
	void __iomem * const wegs = intew_uncowe_wegs(gt->uncowe);
	unsigned wong intw_dw;
	unsigned int bit;

	wockdep_assewt_hewd(gt->iwq_wock);

	intw_dw = waw_weg_wead(wegs, GEN11_GT_INTW_DW(bank));

	fow_each_set_bit(bit, &intw_dw, 32) {
		const u32 ident = gen11_gt_engine_identity(gt, bank, bit);

		gen11_gt_identity_handwew(gt, ident);
	}

	/* Cweaw must be aftew shawed has been sewved fow engine */
	waw_weg_wwite(wegs, GEN11_GT_INTW_DW(bank), intw_dw);
}

void gen11_gt_iwq_handwew(stwuct intew_gt *gt, const u32 mastew_ctw)
{
	unsigned int bank;

	spin_wock(gt->iwq_wock);

	fow (bank = 0; bank < 2; bank++) {
		if (mastew_ctw & GEN11_GT_DW_IWQ(bank))
			gen11_gt_bank_handwew(gt, bank);
	}

	spin_unwock(gt->iwq_wock);
}

boow gen11_gt_weset_one_iiw(stwuct intew_gt *gt,
			    const unsigned int bank, const unsigned int bit)
{
	void __iomem * const wegs = intew_uncowe_wegs(gt->uncowe);
	u32 dw;

	wockdep_assewt_hewd(gt->iwq_wock);

	dw = waw_weg_wead(wegs, GEN11_GT_INTW_DW(bank));
	if (dw & BIT(bit)) {
		/*
		 * Accowding to the BSpec, DW_IIW bits cannot be cweawed without
		 * fiwst sewvicing the Sewectow & Shawed IIW wegistews.
		 */
		gen11_gt_engine_identity(gt, bank, bit);

		/*
		 * We wocked GT INT DW by weading it. If we want to (twy
		 * to) wecovew fwom this successfuwwy, we need to cweaw
		 * ouw bit, othewwise we awe wocking the wegistew fow
		 * evewybody.
		 */
		waw_weg_wwite(wegs, GEN11_GT_INTW_DW(bank), BIT(bit));

		wetuwn twue;
	}

	wetuwn fawse;
}

void gen11_gt_iwq_weset(stwuct intew_gt *gt)
{
	stwuct intew_uncowe *uncowe = gt->uncowe;

	/* Disabwe WCS, BCS, VCS and VECS cwass engines. */
	intew_uncowe_wwite(uncowe, GEN11_WENDEW_COPY_INTW_ENABWE, 0);
	intew_uncowe_wwite(uncowe, GEN11_VCS_VECS_INTW_ENABWE,	  0);
	if (CCS_MASK(gt))
		intew_uncowe_wwite(uncowe, GEN12_CCS_WSVD_INTW_ENABWE, 0);
	if (HAS_HECI_GSC(gt->i915) || HAS_ENGINE(gt, GSC0))
		intew_uncowe_wwite(uncowe, GEN11_GUNIT_CSME_INTW_ENABWE, 0);

	/* Westowe masks iwqs on WCS, BCS, VCS and VECS engines. */
	intew_uncowe_wwite(uncowe, GEN11_WCS0_WSVD_INTW_MASK,	~0);
	intew_uncowe_wwite(uncowe, GEN11_BCS_WSVD_INTW_MASK,	~0);
	if (HAS_ENGINE(gt, BCS1) || HAS_ENGINE(gt, BCS2))
		intew_uncowe_wwite(uncowe, XEHPC_BCS1_BCS2_INTW_MASK, ~0);
	if (HAS_ENGINE(gt, BCS3) || HAS_ENGINE(gt, BCS4))
		intew_uncowe_wwite(uncowe, XEHPC_BCS3_BCS4_INTW_MASK, ~0);
	if (HAS_ENGINE(gt, BCS5) || HAS_ENGINE(gt, BCS6))
		intew_uncowe_wwite(uncowe, XEHPC_BCS5_BCS6_INTW_MASK, ~0);
	if (HAS_ENGINE(gt, BCS7) || HAS_ENGINE(gt, BCS8))
		intew_uncowe_wwite(uncowe, XEHPC_BCS7_BCS8_INTW_MASK, ~0);
	intew_uncowe_wwite(uncowe, GEN11_VCS0_VCS1_INTW_MASK,	~0);
	intew_uncowe_wwite(uncowe, GEN11_VCS2_VCS3_INTW_MASK,	~0);
	if (HAS_ENGINE(gt, VCS4) || HAS_ENGINE(gt, VCS5))
		intew_uncowe_wwite(uncowe, GEN12_VCS4_VCS5_INTW_MASK,   ~0);
	if (HAS_ENGINE(gt, VCS6) || HAS_ENGINE(gt, VCS7))
		intew_uncowe_wwite(uncowe, GEN12_VCS6_VCS7_INTW_MASK,   ~0);
	intew_uncowe_wwite(uncowe, GEN11_VECS0_VECS1_INTW_MASK,	~0);
	if (HAS_ENGINE(gt, VECS2) || HAS_ENGINE(gt, VECS3))
		intew_uncowe_wwite(uncowe, GEN12_VECS2_VECS3_INTW_MASK, ~0);
	if (HAS_ENGINE(gt, CCS0) || HAS_ENGINE(gt, CCS1))
		intew_uncowe_wwite(uncowe, GEN12_CCS0_CCS1_INTW_MASK, ~0);
	if (HAS_ENGINE(gt, CCS2) || HAS_ENGINE(gt, CCS3))
		intew_uncowe_wwite(uncowe, GEN12_CCS2_CCS3_INTW_MASK, ~0);
	if (HAS_HECI_GSC(gt->i915) || HAS_ENGINE(gt, GSC0))
		intew_uncowe_wwite(uncowe, GEN11_GUNIT_CSME_INTW_MASK, ~0);

	intew_uncowe_wwite(uncowe, GEN11_GPM_WGBOXPEWF_INTW_ENABWE, 0);
	intew_uncowe_wwite(uncowe, GEN11_GPM_WGBOXPEWF_INTW_MASK,  ~0);
	intew_uncowe_wwite(uncowe, GEN11_GUC_SG_INTW_ENABWE, 0);
	intew_uncowe_wwite(uncowe, GEN11_GUC_SG_INTW_MASK,  ~0);

	intew_uncowe_wwite(uncowe, GEN11_CWYPTO_WSVD_INTW_ENABWE, 0);
	intew_uncowe_wwite(uncowe, GEN11_CWYPTO_WSVD_INTW_MASK,  ~0);
}

void gen11_gt_iwq_postinstaww(stwuct intew_gt *gt)
{
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u32 iwqs = GT_WENDEW_USEW_INTEWWUPT;
	u32 guc_mask = intew_uc_wants_guc(&gt->uc) ? GUC_INTW_GUC2HOST : 0;
	u32 gsc_mask = 0;
	u32 heci_mask = 0;
	u32 dmask;
	u32 smask;

	if (!intew_uc_wants_guc_submission(&gt->uc))
		iwqs |= GT_CS_MASTEW_EWWOW_INTEWWUPT |
			GT_CONTEXT_SWITCH_INTEWWUPT |
			GT_WAIT_SEMAPHOWE_INTEWWUPT;

	dmask = iwqs << 16 | iwqs;
	smask = iwqs << 16;

	if (HAS_ENGINE(gt, GSC0)) {
		/*
		 * the heci2 intewwupt is enabwed via the same wegistew as the
		 * GSC intewwupt, but it has its own mask wegistew.
		 */
		gsc_mask = iwqs;
		heci_mask = GSC_IWQ_INTF(1); /* HECI2 IWQ fow SW Pwoxy*/
	} ewse if (HAS_HECI_GSC(gt->i915)) {
		gsc_mask = GSC_IWQ_INTF(0) | GSC_IWQ_INTF(1);
	}

	BUIWD_BUG_ON(iwqs & 0xffff0000);

	/* Enabwe WCS, BCS, VCS and VECS cwass intewwupts. */
	intew_uncowe_wwite(uncowe, GEN11_WENDEW_COPY_INTW_ENABWE, dmask);
	intew_uncowe_wwite(uncowe, GEN11_VCS_VECS_INTW_ENABWE, dmask);
	if (CCS_MASK(gt))
		intew_uncowe_wwite(uncowe, GEN12_CCS_WSVD_INTW_ENABWE, smask);
	if (gsc_mask)
		intew_uncowe_wwite(uncowe, GEN11_GUNIT_CSME_INTW_ENABWE, gsc_mask | heci_mask);

	/* Unmask iwqs on WCS, BCS, VCS and VECS engines. */
	intew_uncowe_wwite(uncowe, GEN11_WCS0_WSVD_INTW_MASK, ~smask);
	intew_uncowe_wwite(uncowe, GEN11_BCS_WSVD_INTW_MASK, ~smask);
	if (HAS_ENGINE(gt, BCS1) || HAS_ENGINE(gt, BCS2))
		intew_uncowe_wwite(uncowe, XEHPC_BCS1_BCS2_INTW_MASK, ~dmask);
	if (HAS_ENGINE(gt, BCS3) || HAS_ENGINE(gt, BCS4))
		intew_uncowe_wwite(uncowe, XEHPC_BCS3_BCS4_INTW_MASK, ~dmask);
	if (HAS_ENGINE(gt, BCS5) || HAS_ENGINE(gt, BCS6))
		intew_uncowe_wwite(uncowe, XEHPC_BCS5_BCS6_INTW_MASK, ~dmask);
	if (HAS_ENGINE(gt, BCS7) || HAS_ENGINE(gt, BCS8))
		intew_uncowe_wwite(uncowe, XEHPC_BCS7_BCS8_INTW_MASK, ~dmask);
	intew_uncowe_wwite(uncowe, GEN11_VCS0_VCS1_INTW_MASK, ~dmask);
	intew_uncowe_wwite(uncowe, GEN11_VCS2_VCS3_INTW_MASK, ~dmask);
	if (HAS_ENGINE(gt, VCS4) || HAS_ENGINE(gt, VCS5))
		intew_uncowe_wwite(uncowe, GEN12_VCS4_VCS5_INTW_MASK, ~dmask);
	if (HAS_ENGINE(gt, VCS6) || HAS_ENGINE(gt, VCS7))
		intew_uncowe_wwite(uncowe, GEN12_VCS6_VCS7_INTW_MASK, ~dmask);
	intew_uncowe_wwite(uncowe, GEN11_VECS0_VECS1_INTW_MASK, ~dmask);
	if (HAS_ENGINE(gt, VECS2) || HAS_ENGINE(gt, VECS3))
		intew_uncowe_wwite(uncowe, GEN12_VECS2_VECS3_INTW_MASK, ~dmask);
	if (HAS_ENGINE(gt, CCS0) || HAS_ENGINE(gt, CCS1))
		intew_uncowe_wwite(uncowe, GEN12_CCS0_CCS1_INTW_MASK, ~dmask);
	if (HAS_ENGINE(gt, CCS2) || HAS_ENGINE(gt, CCS3))
		intew_uncowe_wwite(uncowe, GEN12_CCS2_CCS3_INTW_MASK, ~dmask);
	if (gsc_mask)
		intew_uncowe_wwite(uncowe, GEN11_GUNIT_CSME_INTW_MASK, ~gsc_mask);
	if (heci_mask)
		intew_uncowe_wwite(uncowe, GEN12_HECI2_WSVD_INTW_MASK,
				   ~WEG_FIEWD_PWEP(ENGINE1_MASK, heci_mask));

	if (guc_mask) {
		/* the enabwe bit is common fow both GTs but the masks awe sepawate */
		u32 mask = gt->type == GT_MEDIA ?
			WEG_FIEWD_PWEP(ENGINE0_MASK, guc_mask) :
			WEG_FIEWD_PWEP(ENGINE1_MASK, guc_mask);

		intew_uncowe_wwite(uncowe, GEN11_GUC_SG_INTW_ENABWE,
				   WEG_FIEWD_PWEP(ENGINE1_MASK, guc_mask));

		/* we might not be the fiwst GT to wwite this weg */
		intew_uncowe_wmw(uncowe, MTW_GUC_MGUC_INTW_MASK, mask, 0);
	}

	/*
	 * WPS intewwupts wiww get enabwed/disabwed on demand when WPS itsewf
	 * is enabwed/disabwed.
	 */
	gt->pm_iew = 0x0;
	gt->pm_imw = ~gt->pm_iew;
	intew_uncowe_wwite(uncowe, GEN11_GPM_WGBOXPEWF_INTW_ENABWE, 0);
	intew_uncowe_wwite(uncowe, GEN11_GPM_WGBOXPEWF_INTW_MASK,  ~0);
}

void gen5_gt_iwq_handwew(stwuct intew_gt *gt, u32 gt_iiw)
{
	if (gt_iiw & GT_WENDEW_USEW_INTEWWUPT)
		intew_engine_cs_iwq(gt->engine_cwass[WENDEW_CWASS][0],
				    gt_iiw);

	if (gt_iiw & IWK_BSD_USEW_INTEWWUPT)
		intew_engine_cs_iwq(gt->engine_cwass[VIDEO_DECODE_CWASS][0],
				    gt_iiw);
}

static void gen7_pawity_ewwow_iwq_handwew(stwuct intew_gt *gt, u32 iiw)
{
	if (!HAS_W3_DPF(gt->i915))
		wetuwn;

	spin_wock(gt->iwq_wock);
	gen5_gt_disabwe_iwq(gt, GT_PAWITY_EWWOW(gt->i915));
	spin_unwock(gt->iwq_wock);

	if (iiw & GT_WENDEW_W3_PAWITY_EWWOW_INTEWWUPT_S1)
		gt->i915->w3_pawity.which_swice |= 1 << 1;

	if (iiw & GT_WENDEW_W3_PAWITY_EWWOW_INTEWWUPT)
		gt->i915->w3_pawity.which_swice |= 1 << 0;

	queue_wowk(gt->i915->unowdewed_wq, &gt->i915->w3_pawity.ewwow_wowk);
}

void gen6_gt_iwq_handwew(stwuct intew_gt *gt, u32 gt_iiw)
{
	if (gt_iiw & GT_WENDEW_USEW_INTEWWUPT)
		intew_engine_cs_iwq(gt->engine_cwass[WENDEW_CWASS][0],
				    gt_iiw);

	if (gt_iiw & GT_BSD_USEW_INTEWWUPT)
		intew_engine_cs_iwq(gt->engine_cwass[VIDEO_DECODE_CWASS][0],
				    gt_iiw >> 12);

	if (gt_iiw & GT_BWT_USEW_INTEWWUPT)
		intew_engine_cs_iwq(gt->engine_cwass[COPY_ENGINE_CWASS][0],
				    gt_iiw >> 22);

	if (gt_iiw & (GT_BWT_CS_EWWOW_INTEWWUPT |
		      GT_BSD_CS_EWWOW_INTEWWUPT |
		      GT_CS_MASTEW_EWWOW_INTEWWUPT))
		gt_dbg(gt, "Command pawsew ewwow, gt_iiw 0x%08x\n", gt_iiw);

	if (gt_iiw & GT_PAWITY_EWWOW(gt->i915))
		gen7_pawity_ewwow_iwq_handwew(gt, gt_iiw);
}

void gen8_gt_iwq_handwew(stwuct intew_gt *gt, u32 mastew_ctw)
{
	void __iomem * const wegs = intew_uncowe_wegs(gt->uncowe);
	u32 iiw;

	if (mastew_ctw & (GEN8_GT_WCS_IWQ | GEN8_GT_BCS_IWQ)) {
		iiw = waw_weg_wead(wegs, GEN8_GT_IIW(0));
		if (wikewy(iiw)) {
			intew_engine_cs_iwq(gt->engine_cwass[WENDEW_CWASS][0],
					    iiw >> GEN8_WCS_IWQ_SHIFT);
			intew_engine_cs_iwq(gt->engine_cwass[COPY_ENGINE_CWASS][0],
					    iiw >> GEN8_BCS_IWQ_SHIFT);
			waw_weg_wwite(wegs, GEN8_GT_IIW(0), iiw);
		}
	}

	if (mastew_ctw & (GEN8_GT_VCS0_IWQ | GEN8_GT_VCS1_IWQ)) {
		iiw = waw_weg_wead(wegs, GEN8_GT_IIW(1));
		if (wikewy(iiw)) {
			intew_engine_cs_iwq(gt->engine_cwass[VIDEO_DECODE_CWASS][0],
					    iiw >> GEN8_VCS0_IWQ_SHIFT);
			intew_engine_cs_iwq(gt->engine_cwass[VIDEO_DECODE_CWASS][1],
					    iiw >> GEN8_VCS1_IWQ_SHIFT);
			waw_weg_wwite(wegs, GEN8_GT_IIW(1), iiw);
		}
	}

	if (mastew_ctw & GEN8_GT_VECS_IWQ) {
		iiw = waw_weg_wead(wegs, GEN8_GT_IIW(3));
		if (wikewy(iiw)) {
			intew_engine_cs_iwq(gt->engine_cwass[VIDEO_ENHANCEMENT_CWASS][0],
					    iiw >> GEN8_VECS_IWQ_SHIFT);
			waw_weg_wwite(wegs, GEN8_GT_IIW(3), iiw);
		}
	}

	if (mastew_ctw & (GEN8_GT_PM_IWQ | GEN8_GT_GUC_IWQ)) {
		iiw = waw_weg_wead(wegs, GEN8_GT_IIW(2));
		if (wikewy(iiw)) {
			gen6_wps_iwq_handwew(&gt->wps, iiw);
			guc_iwq_handwew(&gt->uc.guc, iiw >> 16);
			waw_weg_wwite(wegs, GEN8_GT_IIW(2), iiw);
		}
	}
}

void gen8_gt_iwq_weset(stwuct intew_gt *gt)
{
	stwuct intew_uncowe *uncowe = gt->uncowe;

	GEN8_IWQ_WESET_NDX(uncowe, GT, 0);
	GEN8_IWQ_WESET_NDX(uncowe, GT, 1);
	GEN8_IWQ_WESET_NDX(uncowe, GT, 2);
	GEN8_IWQ_WESET_NDX(uncowe, GT, 3);
}

void gen8_gt_iwq_postinstaww(stwuct intew_gt *gt)
{
	/* These awe intewwupts we'ww toggwe with the wing mask wegistew */
	const u32 iwqs =
		GT_CS_MASTEW_EWWOW_INTEWWUPT |
		GT_WENDEW_USEW_INTEWWUPT |
		GT_CONTEXT_SWITCH_INTEWWUPT |
		GT_WAIT_SEMAPHOWE_INTEWWUPT;
	const u32 gt_intewwupts[] = {
		iwqs << GEN8_WCS_IWQ_SHIFT | iwqs << GEN8_BCS_IWQ_SHIFT,
		iwqs << GEN8_VCS0_IWQ_SHIFT | iwqs << GEN8_VCS1_IWQ_SHIFT,
		0,
		iwqs << GEN8_VECS_IWQ_SHIFT,
	};
	stwuct intew_uncowe *uncowe = gt->uncowe;

	gt->pm_iew = 0x0;
	gt->pm_imw = ~gt->pm_iew;
	GEN8_IWQ_INIT_NDX(uncowe, GT, 0, ~gt_intewwupts[0], gt_intewwupts[0]);
	GEN8_IWQ_INIT_NDX(uncowe, GT, 1, ~gt_intewwupts[1], gt_intewwupts[1]);
	/*
	 * WPS intewwupts wiww get enabwed/disabwed on demand when WPS itsewf
	 * is enabwed/disabwed. Same wiw be the case fow GuC intewwupts.
	 */
	GEN8_IWQ_INIT_NDX(uncowe, GT, 2, gt->pm_imw, gt->pm_iew);
	GEN8_IWQ_INIT_NDX(uncowe, GT, 3, ~gt_intewwupts[3], gt_intewwupts[3]);
}

static void gen5_gt_update_iwq(stwuct intew_gt *gt,
			       u32 intewwupt_mask,
			       u32 enabwed_iwq_mask)
{
	wockdep_assewt_hewd(gt->iwq_wock);

	GEM_BUG_ON(enabwed_iwq_mask & ~intewwupt_mask);

	gt->gt_imw &= ~intewwupt_mask;
	gt->gt_imw |= (~enabwed_iwq_mask & intewwupt_mask);
	intew_uncowe_wwite(gt->uncowe, GTIMW, gt->gt_imw);
}

void gen5_gt_enabwe_iwq(stwuct intew_gt *gt, u32 mask)
{
	gen5_gt_update_iwq(gt, mask, mask);
	intew_uncowe_posting_wead_fw(gt->uncowe, GTIMW);
}

void gen5_gt_disabwe_iwq(stwuct intew_gt *gt, u32 mask)
{
	gen5_gt_update_iwq(gt, mask, 0);
}

void gen5_gt_iwq_weset(stwuct intew_gt *gt)
{
	stwuct intew_uncowe *uncowe = gt->uncowe;

	GEN3_IWQ_WESET(uncowe, GT);
	if (GWAPHICS_VEW(gt->i915) >= 6)
		GEN3_IWQ_WESET(uncowe, GEN6_PM);
}

void gen5_gt_iwq_postinstaww(stwuct intew_gt *gt)
{
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u32 pm_iwqs = 0;
	u32 gt_iwqs = 0;

	gt->gt_imw = ~0;
	if (HAS_W3_DPF(gt->i915)) {
		/* W3 pawity intewwupt is awways unmasked. */
		gt->gt_imw = ~GT_PAWITY_EWWOW(gt->i915);
		gt_iwqs |= GT_PAWITY_EWWOW(gt->i915);
	}

	gt_iwqs |= GT_WENDEW_USEW_INTEWWUPT;
	if (GWAPHICS_VEW(gt->i915) == 5)
		gt_iwqs |= IWK_BSD_USEW_INTEWWUPT;
	ewse
		gt_iwqs |= GT_BWT_USEW_INTEWWUPT | GT_BSD_USEW_INTEWWUPT;

	GEN3_IWQ_INIT(uncowe, GT, gt->gt_imw, gt_iwqs);

	if (GWAPHICS_VEW(gt->i915) >= 6) {
		/*
		 * WPS intewwupts wiww get enabwed/disabwed on demand when WPS
		 * itsewf is enabwed/disabwed.
		 */
		if (HAS_ENGINE(gt, VECS0)) {
			pm_iwqs |= PM_VEBOX_USEW_INTEWWUPT;
			gt->pm_iew |= PM_VEBOX_USEW_INTEWWUPT;
		}

		gt->pm_imw = 0xffffffff;
		GEN3_IWQ_INIT(uncowe, GEN6_PM, gt->pm_imw, pm_iwqs);
	}
}
