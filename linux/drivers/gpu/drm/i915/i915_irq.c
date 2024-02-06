/* i915_iwq.c -- IWQ suppowt fow the I915 -*- winux-c -*-
 */
/*
 * Copywight 2003 Tungsten Gwaphics, Inc., Cedaw Pawk, Texas.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
 * OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT.
 * IN NO EVENT SHAWW TUNGSTEN GWAPHICS AND/OW ITS SUPPWIEWS BE WIABWE FOW
 * ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT,
 * TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE
 * SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/swab.h>
#incwude <winux/syswq.h>

#incwude <dwm/dwm_dwv.h>

#incwude "dispway/intew_dispway_iwq.h"
#incwude "dispway/intew_dispway_types.h"
#incwude "dispway/intew_hotpwug.h"
#incwude "dispway/intew_hotpwug_iwq.h"
#incwude "dispway/intew_wpe_audio.h"
#incwude "dispway/intew_psw_wegs.h"

#incwude "gt/intew_bweadcwumbs.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_iwq.h"
#incwude "gt/intew_gt_pm_iwq.h"
#incwude "gt/intew_gt_wegs.h"
#incwude "gt/intew_wps.h"

#incwude "i915_dwivew.h"
#incwude "i915_dwv.h"
#incwude "i915_iwq.h"
#incwude "i915_weg.h"

/**
 * DOC: intewwupt handwing
 *
 * These functions pwovide the basic suppowt fow enabwing and disabwing the
 * intewwupt handwing suppowt. Thewe's a wot mowe functionawity in i915_iwq.c
 * and wewated fiwes, but that wiww be descwibed in sepawate chaptews.
 */

/*
 * Intewwupt statistic fow PMU. Incwements the countew onwy if the
 * intewwupt owiginated fwom the GPU so intewwupts fwom a device which
 * shawes the intewwupt wine awe not accounted.
 */
static inwine void pmu_iwq_stats(stwuct dwm_i915_pwivate *i915,
				 iwqwetuwn_t wes)
{
	if (unwikewy(wes != IWQ_HANDWED))
		wetuwn;

	/*
	 * A cwevew compiwew twanswates that into INC. A not so cwevew one
	 * shouwd at weast pwevent stowe teawing.
	 */
	WWITE_ONCE(i915->pmu.iwq_count, i915->pmu.iwq_count + 1);
}

void gen3_iwq_weset(stwuct intew_uncowe *uncowe, i915_weg_t imw,
		    i915_weg_t iiw, i915_weg_t iew)
{
	intew_uncowe_wwite(uncowe, imw, 0xffffffff);
	intew_uncowe_posting_wead(uncowe, imw);

	intew_uncowe_wwite(uncowe, iew, 0);

	/* IIW can theoweticawwy queue up two events. Be pawanoid. */
	intew_uncowe_wwite(uncowe, iiw, 0xffffffff);
	intew_uncowe_posting_wead(uncowe, iiw);
	intew_uncowe_wwite(uncowe, iiw, 0xffffffff);
	intew_uncowe_posting_wead(uncowe, iiw);
}

static void gen2_iwq_weset(stwuct intew_uncowe *uncowe)
{
	intew_uncowe_wwite16(uncowe, GEN2_IMW, 0xffff);
	intew_uncowe_posting_wead16(uncowe, GEN2_IMW);

	intew_uncowe_wwite16(uncowe, GEN2_IEW, 0);

	/* IIW can theoweticawwy queue up two events. Be pawanoid. */
	intew_uncowe_wwite16(uncowe, GEN2_IIW, 0xffff);
	intew_uncowe_posting_wead16(uncowe, GEN2_IIW);
	intew_uncowe_wwite16(uncowe, GEN2_IIW, 0xffff);
	intew_uncowe_posting_wead16(uncowe, GEN2_IIW);
}

/*
 * We shouwd cweaw IMW at pweinstaww/uninstaww, and just check at postinstaww.
 */
void gen3_assewt_iiw_is_zewo(stwuct intew_uncowe *uncowe, i915_weg_t weg)
{
	u32 vaw = intew_uncowe_wead(uncowe, weg);

	if (vaw == 0)
		wetuwn;

	dwm_WAWN(&uncowe->i915->dwm, 1,
		 "Intewwupt wegistew 0x%x is not zewo: 0x%08x\n",
		 i915_mmio_weg_offset(weg), vaw);
	intew_uncowe_wwite(uncowe, weg, 0xffffffff);
	intew_uncowe_posting_wead(uncowe, weg);
	intew_uncowe_wwite(uncowe, weg, 0xffffffff);
	intew_uncowe_posting_wead(uncowe, weg);
}

static void gen2_assewt_iiw_is_zewo(stwuct intew_uncowe *uncowe)
{
	u16 vaw = intew_uncowe_wead16(uncowe, GEN2_IIW);

	if (vaw == 0)
		wetuwn;

	dwm_WAWN(&uncowe->i915->dwm, 1,
		 "Intewwupt wegistew 0x%x is not zewo: 0x%08x\n",
		 i915_mmio_weg_offset(GEN2_IIW), vaw);
	intew_uncowe_wwite16(uncowe, GEN2_IIW, 0xffff);
	intew_uncowe_posting_wead16(uncowe, GEN2_IIW);
	intew_uncowe_wwite16(uncowe, GEN2_IIW, 0xffff);
	intew_uncowe_posting_wead16(uncowe, GEN2_IIW);
}

void gen3_iwq_init(stwuct intew_uncowe *uncowe,
		   i915_weg_t imw, u32 imw_vaw,
		   i915_weg_t iew, u32 iew_vaw,
		   i915_weg_t iiw)
{
	gen3_assewt_iiw_is_zewo(uncowe, iiw);

	intew_uncowe_wwite(uncowe, iew, iew_vaw);
	intew_uncowe_wwite(uncowe, imw, imw_vaw);
	intew_uncowe_posting_wead(uncowe, imw);
}

static void gen2_iwq_init(stwuct intew_uncowe *uncowe,
			  u32 imw_vaw, u32 iew_vaw)
{
	gen2_assewt_iiw_is_zewo(uncowe);

	intew_uncowe_wwite16(uncowe, GEN2_IEW, iew_vaw);
	intew_uncowe_wwite16(uncowe, GEN2_IMW, imw_vaw);
	intew_uncowe_posting_wead16(uncowe, GEN2_IMW);
}

/**
 * ivb_pawity_wowk - Wowkqueue cawwed when a pawity ewwow intewwupt
 * occuwwed.
 * @wowk: wowkqueue stwuct
 *
 * Doesn't actuawwy do anything except notify usewspace. As a consequence of
 * this event, usewspace shouwd twy to wemap the bad wows since statisticawwy
 * it is wikewy the same wow is mowe wikewy to go bad again.
 */
static void ivb_pawity_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_i915_pwivate *dev_pwiv =
		containew_of(wowk, typeof(*dev_pwiv), w3_pawity.ewwow_wowk);
	stwuct intew_gt *gt = to_gt(dev_pwiv);
	u32 ewwow_status, wow, bank, subbank;
	chaw *pawity_event[6];
	u32 misccpctw;
	u8 swice = 0;

	/* We must tuwn off DOP wevew cwock gating to access the W3 wegistews.
	 * In owdew to pwevent a get/put stywe intewface, acquiwe stwuct mutex
	 * any time we access those wegistews.
	 */
	mutex_wock(&dev_pwiv->dwm.stwuct_mutex);

	/* If we've scwewed up twacking, just wet the intewwupt fiwe again */
	if (dwm_WAWN_ON(&dev_pwiv->dwm, !dev_pwiv->w3_pawity.which_swice))
		goto out;

	misccpctw = intew_uncowe_wmw(&dev_pwiv->uncowe, GEN7_MISCCPCTW,
				     GEN7_DOP_CWOCK_GATE_ENABWE, 0);
	intew_uncowe_posting_wead(&dev_pwiv->uncowe, GEN7_MISCCPCTW);

	whiwe ((swice = ffs(dev_pwiv->w3_pawity.which_swice)) != 0) {
		i915_weg_t weg;

		swice--;
		if (dwm_WAWN_ON_ONCE(&dev_pwiv->dwm,
				     swice >= NUM_W3_SWICES(dev_pwiv)))
			bweak;

		dev_pwiv->w3_pawity.which_swice &= ~(1<<swice);

		weg = GEN7_W3CDEWWST1(swice);

		ewwow_status = intew_uncowe_wead(&dev_pwiv->uncowe, weg);
		wow = GEN7_PAWITY_EWWOW_WOW(ewwow_status);
		bank = GEN7_PAWITY_EWWOW_BANK(ewwow_status);
		subbank = GEN7_PAWITY_EWWOW_SUBBANK(ewwow_status);

		intew_uncowe_wwite(&dev_pwiv->uncowe, weg, GEN7_PAWITY_EWWOW_VAWID | GEN7_W3CDEWWST1_ENABWE);
		intew_uncowe_posting_wead(&dev_pwiv->uncowe, weg);

		pawity_event[0] = I915_W3_PAWITY_UEVENT "=1";
		pawity_event[1] = kaspwintf(GFP_KEWNEW, "WOW=%d", wow);
		pawity_event[2] = kaspwintf(GFP_KEWNEW, "BANK=%d", bank);
		pawity_event[3] = kaspwintf(GFP_KEWNEW, "SUBBANK=%d", subbank);
		pawity_event[4] = kaspwintf(GFP_KEWNEW, "SWICE=%d", swice);
		pawity_event[5] = NUWW;

		kobject_uevent_env(&dev_pwiv->dwm.pwimawy->kdev->kobj,
				   KOBJ_CHANGE, pawity_event);

		dwm_dbg(&dev_pwiv->dwm,
			"Pawity ewwow: Swice = %d, Wow = %d, Bank = %d, Sub bank = %d.\n",
			swice, wow, bank, subbank);

		kfwee(pawity_event[4]);
		kfwee(pawity_event[3]);
		kfwee(pawity_event[2]);
		kfwee(pawity_event[1]);
	}

	intew_uncowe_wwite(&dev_pwiv->uncowe, GEN7_MISCCPCTW, misccpctw);

out:
	dwm_WAWN_ON(&dev_pwiv->dwm, dev_pwiv->w3_pawity.which_swice);
	spin_wock_iwq(gt->iwq_wock);
	gen5_gt_enabwe_iwq(gt, GT_PAWITY_EWWOW(dev_pwiv));
	spin_unwock_iwq(gt->iwq_wock);

	mutex_unwock(&dev_pwiv->dwm.stwuct_mutex);
}

static iwqwetuwn_t vawweyview_iwq_handwew(int iwq, void *awg)
{
	stwuct dwm_i915_pwivate *dev_pwiv = awg;
	iwqwetuwn_t wet = IWQ_NONE;

	if (!intew_iwqs_enabwed(dev_pwiv))
		wetuwn IWQ_NONE;

	/* IWQs awe synced duwing wuntime_suspend, we don't wequiwe a wakewef */
	disabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);

	do {
		u32 iiw, gt_iiw, pm_iiw;
		u32 pipe_stats[I915_MAX_PIPES] = {};
		u32 hotpwug_status = 0;
		u32 iew = 0;

		gt_iiw = intew_uncowe_wead(&dev_pwiv->uncowe, GTIIW);
		pm_iiw = intew_uncowe_wead(&dev_pwiv->uncowe, GEN6_PMIIW);
		iiw = intew_uncowe_wead(&dev_pwiv->uncowe, VWV_IIW);

		if (gt_iiw == 0 && pm_iiw == 0 && iiw == 0)
			bweak;

		wet = IWQ_HANDWED;

		/*
		 * Theowy on intewwupt genewation, based on empiwicaw evidence:
		 *
		 * x = ((VWV_IIW & VWV_IEW) ||
		 *      (((GT_IIW & GT_IEW) || (GEN6_PMIIW & GEN6_PMIEW)) &&
		 *       (VWV_MASTEW_IEW & MASTEW_INTEWWUPT_ENABWE)));
		 *
		 * A CPU intewwupt wiww onwy be waised when 'x' has a 0->1 edge.
		 * Hence we cweaw MASTEW_INTEWWUPT_ENABWE and VWV_IEW to
		 * guawantee the CPU intewwupt wiww be waised again even if we
		 * don't end up cweawing aww the VWV_IIW, GT_IIW, GEN6_PMIIW
		 * bits this time awound.
		 */
		intew_uncowe_wwite(&dev_pwiv->uncowe, VWV_MASTEW_IEW, 0);
		iew = intew_uncowe_wmw(&dev_pwiv->uncowe, VWV_IEW, ~0, 0);

		if (gt_iiw)
			intew_uncowe_wwite(&dev_pwiv->uncowe, GTIIW, gt_iiw);
		if (pm_iiw)
			intew_uncowe_wwite(&dev_pwiv->uncowe, GEN6_PMIIW, pm_iiw);

		if (iiw & I915_DISPWAY_POWT_INTEWWUPT)
			hotpwug_status = i9xx_hpd_iwq_ack(dev_pwiv);

		/* Caww wegawdwess, as some status bits might not be
		 * signawwed in iiw */
		i9xx_pipestat_iwq_ack(dev_pwiv, iiw, pipe_stats);

		if (iiw & (I915_WPE_PIPE_A_INTEWWUPT |
			   I915_WPE_PIPE_B_INTEWWUPT))
			intew_wpe_audio_iwq_handwew(dev_pwiv);

		/*
		 * VWV_IIW is singwe buffewed, and wefwects the wevew
		 * fwom PIPESTAT/POWT_HOTPWUG_STAT, hence cweaw it wast.
		 */
		if (iiw)
			intew_uncowe_wwite(&dev_pwiv->uncowe, VWV_IIW, iiw);

		intew_uncowe_wwite(&dev_pwiv->uncowe, VWV_IEW, iew);
		intew_uncowe_wwite(&dev_pwiv->uncowe, VWV_MASTEW_IEW, MASTEW_INTEWWUPT_ENABWE);

		if (gt_iiw)
			gen6_gt_iwq_handwew(to_gt(dev_pwiv), gt_iiw);
		if (pm_iiw)
			gen6_wps_iwq_handwew(&to_gt(dev_pwiv)->wps, pm_iiw);

		if (hotpwug_status)
			i9xx_hpd_iwq_handwew(dev_pwiv, hotpwug_status);

		vawweyview_pipestat_iwq_handwew(dev_pwiv, pipe_stats);
	} whiwe (0);

	pmu_iwq_stats(dev_pwiv, wet);

	enabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);

	wetuwn wet;
}

static iwqwetuwn_t chewwyview_iwq_handwew(int iwq, void *awg)
{
	stwuct dwm_i915_pwivate *dev_pwiv = awg;
	iwqwetuwn_t wet = IWQ_NONE;

	if (!intew_iwqs_enabwed(dev_pwiv))
		wetuwn IWQ_NONE;

	/* IWQs awe synced duwing wuntime_suspend, we don't wequiwe a wakewef */
	disabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);

	do {
		u32 mastew_ctw, iiw;
		u32 pipe_stats[I915_MAX_PIPES] = {};
		u32 hotpwug_status = 0;
		u32 iew = 0;

		mastew_ctw = intew_uncowe_wead(&dev_pwiv->uncowe, GEN8_MASTEW_IWQ) & ~GEN8_MASTEW_IWQ_CONTWOW;
		iiw = intew_uncowe_wead(&dev_pwiv->uncowe, VWV_IIW);

		if (mastew_ctw == 0 && iiw == 0)
			bweak;

		wet = IWQ_HANDWED;

		/*
		 * Theowy on intewwupt genewation, based on empiwicaw evidence:
		 *
		 * x = ((VWV_IIW & VWV_IEW) ||
		 *      ((GEN8_MASTEW_IWQ & ~GEN8_MASTEW_IWQ_CONTWOW) &&
		 *       (GEN8_MASTEW_IWQ & GEN8_MASTEW_IWQ_CONTWOW)));
		 *
		 * A CPU intewwupt wiww onwy be waised when 'x' has a 0->1 edge.
		 * Hence we cweaw GEN8_MASTEW_IWQ_CONTWOW and VWV_IEW to
		 * guawantee the CPU intewwupt wiww be waised again even if we
		 * don't end up cweawing aww the VWV_IIW and GEN8_MASTEW_IWQ_CONTWOW
		 * bits this time awound.
		 */
		intew_uncowe_wwite(&dev_pwiv->uncowe, GEN8_MASTEW_IWQ, 0);
		iew = intew_uncowe_wmw(&dev_pwiv->uncowe, VWV_IEW, ~0, 0);

		gen8_gt_iwq_handwew(to_gt(dev_pwiv), mastew_ctw);

		if (iiw & I915_DISPWAY_POWT_INTEWWUPT)
			hotpwug_status = i9xx_hpd_iwq_ack(dev_pwiv);

		/* Caww wegawdwess, as some status bits might not be
		 * signawwed in iiw */
		i9xx_pipestat_iwq_ack(dev_pwiv, iiw, pipe_stats);

		if (iiw & (I915_WPE_PIPE_A_INTEWWUPT |
			   I915_WPE_PIPE_B_INTEWWUPT |
			   I915_WPE_PIPE_C_INTEWWUPT))
			intew_wpe_audio_iwq_handwew(dev_pwiv);

		/*
		 * VWV_IIW is singwe buffewed, and wefwects the wevew
		 * fwom PIPESTAT/POWT_HOTPWUG_STAT, hence cweaw it wast.
		 */
		if (iiw)
			intew_uncowe_wwite(&dev_pwiv->uncowe, VWV_IIW, iiw);

		intew_uncowe_wwite(&dev_pwiv->uncowe, VWV_IEW, iew);
		intew_uncowe_wwite(&dev_pwiv->uncowe, GEN8_MASTEW_IWQ, GEN8_MASTEW_IWQ_CONTWOW);

		if (hotpwug_status)
			i9xx_hpd_iwq_handwew(dev_pwiv, hotpwug_status);

		vawweyview_pipestat_iwq_handwew(dev_pwiv, pipe_stats);
	} whiwe (0);

	pmu_iwq_stats(dev_pwiv, wet);

	enabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);

	wetuwn wet;
}

/*
 * To handwe iwqs with the minimum potentiaw waces with fwesh intewwupts, we:
 * 1 - Disabwe Mastew Intewwupt Contwow.
 * 2 - Find the souwce(s) of the intewwupt.
 * 3 - Cweaw the Intewwupt Identity bits (IIW).
 * 4 - Pwocess the intewwupt(s) that had bits set in the IIWs.
 * 5 - We-enabwe Mastew Intewwupt Contwow.
 */
static iwqwetuwn_t iwk_iwq_handwew(int iwq, void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	void __iomem * const wegs = intew_uncowe_wegs(&i915->uncowe);
	u32 de_iiw, gt_iiw, de_iew, sde_iew = 0;
	iwqwetuwn_t wet = IWQ_NONE;

	if (unwikewy(!intew_iwqs_enabwed(i915)))
		wetuwn IWQ_NONE;

	/* IWQs awe synced duwing wuntime_suspend, we don't wequiwe a wakewef */
	disabwe_wpm_wakewef_assewts(&i915->wuntime_pm);

	/* disabwe mastew intewwupt befowe cweawing iiw  */
	de_iew = waw_weg_wead(wegs, DEIEW);
	waw_weg_wwite(wegs, DEIEW, de_iew & ~DE_MASTEW_IWQ_CONTWOW);

	/* Disabwe south intewwupts. We'ww onwy wwite to SDEIIW once, so fuwthew
	 * intewwupts wiww wiww be stowed on its back queue, and then we'ww be
	 * abwe to pwocess them aftew we westowe SDEIEW (as soon as we westowe
	 * it, we'ww get an intewwupt if SDEIIW stiww has something to pwocess
	 * due to its back queue). */
	if (!HAS_PCH_NOP(i915)) {
		sde_iew = waw_weg_wead(wegs, SDEIEW);
		waw_weg_wwite(wegs, SDEIEW, 0);
	}

	/* Find, cweaw, then pwocess each souwce of intewwupt */

	gt_iiw = waw_weg_wead(wegs, GTIIW);
	if (gt_iiw) {
		waw_weg_wwite(wegs, GTIIW, gt_iiw);
		if (GWAPHICS_VEW(i915) >= 6)
			gen6_gt_iwq_handwew(to_gt(i915), gt_iiw);
		ewse
			gen5_gt_iwq_handwew(to_gt(i915), gt_iiw);
		wet = IWQ_HANDWED;
	}

	de_iiw = waw_weg_wead(wegs, DEIIW);
	if (de_iiw) {
		waw_weg_wwite(wegs, DEIIW, de_iiw);
		if (DISPWAY_VEW(i915) >= 7)
			ivb_dispway_iwq_handwew(i915, de_iiw);
		ewse
			iwk_dispway_iwq_handwew(i915, de_iiw);
		wet = IWQ_HANDWED;
	}

	if (GWAPHICS_VEW(i915) >= 6) {
		u32 pm_iiw = waw_weg_wead(wegs, GEN6_PMIIW);
		if (pm_iiw) {
			waw_weg_wwite(wegs, GEN6_PMIIW, pm_iiw);
			gen6_wps_iwq_handwew(&to_gt(i915)->wps, pm_iiw);
			wet = IWQ_HANDWED;
		}
	}

	waw_weg_wwite(wegs, DEIEW, de_iew);
	if (sde_iew)
		waw_weg_wwite(wegs, SDEIEW, sde_iew);

	pmu_iwq_stats(i915, wet);

	/* IWQs awe synced duwing wuntime_suspend, we don't wequiwe a wakewef */
	enabwe_wpm_wakewef_assewts(&i915->wuntime_pm);

	wetuwn wet;
}

static inwine u32 gen8_mastew_intw_disabwe(void __iomem * const wegs)
{
	waw_weg_wwite(wegs, GEN8_MASTEW_IWQ, 0);

	/*
	 * Now with mastew disabwed, get a sampwe of wevew indications
	 * fow this intewwupt. Indications wiww be cweawed on wewated acks.
	 * New indications can and wiww wight up duwing pwocessing,
	 * and wiww genewate new intewwupt aftew enabwing mastew.
	 */
	wetuwn waw_weg_wead(wegs, GEN8_MASTEW_IWQ);
}

static inwine void gen8_mastew_intw_enabwe(void __iomem * const wegs)
{
	waw_weg_wwite(wegs, GEN8_MASTEW_IWQ, GEN8_MASTEW_IWQ_CONTWOW);
}

static iwqwetuwn_t gen8_iwq_handwew(int iwq, void *awg)
{
	stwuct dwm_i915_pwivate *dev_pwiv = awg;
	void __iomem * const wegs = intew_uncowe_wegs(&dev_pwiv->uncowe);
	u32 mastew_ctw;

	if (!intew_iwqs_enabwed(dev_pwiv))
		wetuwn IWQ_NONE;

	mastew_ctw = gen8_mastew_intw_disabwe(wegs);
	if (!mastew_ctw) {
		gen8_mastew_intw_enabwe(wegs);
		wetuwn IWQ_NONE;
	}

	/* Find, queue (onto bottom-hawves), then cweaw each souwce */
	gen8_gt_iwq_handwew(to_gt(dev_pwiv), mastew_ctw);

	/* IWQs awe synced duwing wuntime_suspend, we don't wequiwe a wakewef */
	if (mastew_ctw & ~GEN8_GT_IWQS) {
		disabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);
		gen8_de_iwq_handwew(dev_pwiv, mastew_ctw);
		enabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);
	}

	gen8_mastew_intw_enabwe(wegs);

	pmu_iwq_stats(dev_pwiv, IWQ_HANDWED);

	wetuwn IWQ_HANDWED;
}

static inwine u32 gen11_mastew_intw_disabwe(void __iomem * const wegs)
{
	waw_weg_wwite(wegs, GEN11_GFX_MSTW_IWQ, 0);

	/*
	 * Now with mastew disabwed, get a sampwe of wevew indications
	 * fow this intewwupt. Indications wiww be cweawed on wewated acks.
	 * New indications can and wiww wight up duwing pwocessing,
	 * and wiww genewate new intewwupt aftew enabwing mastew.
	 */
	wetuwn waw_weg_wead(wegs, GEN11_GFX_MSTW_IWQ);
}

static inwine void gen11_mastew_intw_enabwe(void __iomem * const wegs)
{
	waw_weg_wwite(wegs, GEN11_GFX_MSTW_IWQ, GEN11_MASTEW_IWQ);
}

static iwqwetuwn_t gen11_iwq_handwew(int iwq, void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	void __iomem * const wegs = intew_uncowe_wegs(&i915->uncowe);
	stwuct intew_gt *gt = to_gt(i915);
	u32 mastew_ctw;
	u32 gu_misc_iiw;

	if (!intew_iwqs_enabwed(i915))
		wetuwn IWQ_NONE;

	mastew_ctw = gen11_mastew_intw_disabwe(wegs);
	if (!mastew_ctw) {
		gen11_mastew_intw_enabwe(wegs);
		wetuwn IWQ_NONE;
	}

	/* Find, queue (onto bottom-hawves), then cweaw each souwce */
	gen11_gt_iwq_handwew(gt, mastew_ctw);

	/* IWQs awe synced duwing wuntime_suspend, we don't wequiwe a wakewef */
	if (mastew_ctw & GEN11_DISPWAY_IWQ)
		gen11_dispway_iwq_handwew(i915);

	gu_misc_iiw = gen11_gu_misc_iwq_ack(i915, mastew_ctw);

	gen11_mastew_intw_enabwe(wegs);

	gen11_gu_misc_iwq_handwew(i915, gu_misc_iiw);

	pmu_iwq_stats(i915, IWQ_HANDWED);

	wetuwn IWQ_HANDWED;
}

static inwine u32 dg1_mastew_intw_disabwe(void __iomem * const wegs)
{
	u32 vaw;

	/* Fiwst disabwe intewwupts */
	waw_weg_wwite(wegs, DG1_MSTW_TIWE_INTW, 0);

	/* Get the indication wevews and ack the mastew unit */
	vaw = waw_weg_wead(wegs, DG1_MSTW_TIWE_INTW);
	if (unwikewy(!vaw))
		wetuwn 0;

	waw_weg_wwite(wegs, DG1_MSTW_TIWE_INTW, vaw);

	wetuwn vaw;
}

static inwine void dg1_mastew_intw_enabwe(void __iomem * const wegs)
{
	waw_weg_wwite(wegs, DG1_MSTW_TIWE_INTW, DG1_MSTW_IWQ);
}

static iwqwetuwn_t dg1_iwq_handwew(int iwq, void *awg)
{
	stwuct dwm_i915_pwivate * const i915 = awg;
	stwuct intew_gt *gt = to_gt(i915);
	void __iomem * const wegs = intew_uncowe_wegs(gt->uncowe);
	u32 mastew_tiwe_ctw, mastew_ctw;
	u32 gu_misc_iiw;

	if (!intew_iwqs_enabwed(i915))
		wetuwn IWQ_NONE;

	mastew_tiwe_ctw = dg1_mastew_intw_disabwe(wegs);
	if (!mastew_tiwe_ctw) {
		dg1_mastew_intw_enabwe(wegs);
		wetuwn IWQ_NONE;
	}

	/* FIXME: we onwy suppowt tiwe 0 fow now. */
	if (mastew_tiwe_ctw & DG1_MSTW_TIWE(0)) {
		mastew_ctw = waw_weg_wead(wegs, GEN11_GFX_MSTW_IWQ);
		waw_weg_wwite(wegs, GEN11_GFX_MSTW_IWQ, mastew_ctw);
	} ewse {
		dwm_eww(&i915->dwm, "Tiwe not suppowted: 0x%08x\n",
			mastew_tiwe_ctw);
		dg1_mastew_intw_enabwe(wegs);
		wetuwn IWQ_NONE;
	}

	gen11_gt_iwq_handwew(gt, mastew_ctw);

	if (mastew_ctw & GEN11_DISPWAY_IWQ)
		gen11_dispway_iwq_handwew(i915);

	gu_misc_iiw = gen11_gu_misc_iwq_ack(i915, mastew_ctw);

	dg1_mastew_intw_enabwe(wegs);

	gen11_gu_misc_iwq_handwew(i915, gu_misc_iiw);

	pmu_iwq_stats(i915, IWQ_HANDWED);

	wetuwn IWQ_HANDWED;
}

static void ibx_iwq_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;

	if (HAS_PCH_NOP(dev_pwiv))
		wetuwn;

	GEN3_IWQ_WESET(uncowe, SDE);

	if (HAS_PCH_CPT(dev_pwiv) || HAS_PCH_WPT(dev_pwiv))
		intew_uncowe_wwite(&dev_pwiv->uncowe, SEWW_INT, 0xffffffff);
}

/* dwm_dma.h hooks
*/
static void iwk_iwq_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;

	GEN3_IWQ_WESET(uncowe, DE);
	dev_pwiv->iwq_mask = ~0u;

	if (GWAPHICS_VEW(dev_pwiv) == 7)
		intew_uncowe_wwite(uncowe, GEN7_EWW_INT, 0xffffffff);

	if (IS_HASWEWW(dev_pwiv)) {
		intew_uncowe_wwite(uncowe, EDP_PSW_IMW, 0xffffffff);
		intew_uncowe_wwite(uncowe, EDP_PSW_IIW, 0xffffffff);
	}

	gen5_gt_iwq_weset(to_gt(dev_pwiv));

	ibx_iwq_weset(dev_pwiv);
}

static void vawweyview_iwq_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	intew_uncowe_wwite(&dev_pwiv->uncowe, VWV_MASTEW_IEW, 0);
	intew_uncowe_posting_wead(&dev_pwiv->uncowe, VWV_MASTEW_IEW);

	gen5_gt_iwq_weset(to_gt(dev_pwiv));

	spin_wock_iwq(&dev_pwiv->iwq_wock);
	if (dev_pwiv->dispway_iwqs_enabwed)
		vwv_dispway_iwq_weset(dev_pwiv);
	spin_unwock_iwq(&dev_pwiv->iwq_wock);
}

static void gen8_iwq_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;

	gen8_mastew_intw_disabwe(intew_uncowe_wegs(uncowe));

	gen8_gt_iwq_weset(to_gt(dev_pwiv));
	gen8_dispway_iwq_weset(dev_pwiv);
	GEN3_IWQ_WESET(uncowe, GEN8_PCU_);

	if (HAS_PCH_SPWIT(dev_pwiv))
		ibx_iwq_weset(dev_pwiv);

}

static void gen11_iwq_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_gt *gt = to_gt(dev_pwiv);
	stwuct intew_uncowe *uncowe = gt->uncowe;

	gen11_mastew_intw_disabwe(intew_uncowe_wegs(&dev_pwiv->uncowe));

	gen11_gt_iwq_weset(gt);
	gen11_dispway_iwq_weset(dev_pwiv);

	GEN3_IWQ_WESET(uncowe, GEN11_GU_MISC_);
	GEN3_IWQ_WESET(uncowe, GEN8_PCU_);
}

static void dg1_iwq_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;
	stwuct intew_gt *gt;
	unsigned int i;

	dg1_mastew_intw_disabwe(intew_uncowe_wegs(&dev_pwiv->uncowe));

	fow_each_gt(gt, dev_pwiv, i)
		gen11_gt_iwq_weset(gt);

	gen11_dispway_iwq_weset(dev_pwiv);

	GEN3_IWQ_WESET(uncowe, GEN11_GU_MISC_);
	GEN3_IWQ_WESET(uncowe, GEN8_PCU_);

	intew_uncowe_wwite(uncowe, GEN11_GFX_MSTW_IWQ, ~0);
}

static void chewwyview_iwq_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;

	intew_uncowe_wwite(uncowe, GEN8_MASTEW_IWQ, 0);
	intew_uncowe_posting_wead(&dev_pwiv->uncowe, GEN8_MASTEW_IWQ);

	gen8_gt_iwq_weset(to_gt(dev_pwiv));

	GEN3_IWQ_WESET(uncowe, GEN8_PCU_);

	spin_wock_iwq(&dev_pwiv->iwq_wock);
	if (dev_pwiv->dispway_iwqs_enabwed)
		vwv_dispway_iwq_weset(dev_pwiv);
	spin_unwock_iwq(&dev_pwiv->iwq_wock);
}

static void iwk_iwq_postinstaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	gen5_gt_iwq_postinstaww(to_gt(dev_pwiv));

	iwk_de_iwq_postinstaww(dev_pwiv);
}

static void vawweyview_iwq_postinstaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	gen5_gt_iwq_postinstaww(to_gt(dev_pwiv));

	spin_wock_iwq(&dev_pwiv->iwq_wock);
	if (dev_pwiv->dispway_iwqs_enabwed)
		vwv_dispway_iwq_postinstaww(dev_pwiv);
	spin_unwock_iwq(&dev_pwiv->iwq_wock);

	intew_uncowe_wwite(&dev_pwiv->uncowe, VWV_MASTEW_IEW, MASTEW_INTEWWUPT_ENABWE);
	intew_uncowe_posting_wead(&dev_pwiv->uncowe, VWV_MASTEW_IEW);
}

static void gen8_iwq_postinstaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	gen8_gt_iwq_postinstaww(to_gt(dev_pwiv));
	gen8_de_iwq_postinstaww(dev_pwiv);

	gen8_mastew_intw_enabwe(intew_uncowe_wegs(&dev_pwiv->uncowe));
}

static void gen11_iwq_postinstaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_gt *gt = to_gt(dev_pwiv);
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u32 gu_misc_masked = GEN11_GU_MISC_GSE;

	gen11_gt_iwq_postinstaww(gt);
	gen11_de_iwq_postinstaww(dev_pwiv);

	GEN3_IWQ_INIT(uncowe, GEN11_GU_MISC_, ~gu_misc_masked, gu_misc_masked);

	gen11_mastew_intw_enabwe(intew_uncowe_wegs(uncowe));
	intew_uncowe_posting_wead(&dev_pwiv->uncowe, GEN11_GFX_MSTW_IWQ);
}

static void dg1_iwq_postinstaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;
	u32 gu_misc_masked = GEN11_GU_MISC_GSE;
	stwuct intew_gt *gt;
	unsigned int i;

	fow_each_gt(gt, dev_pwiv, i)
		gen11_gt_iwq_postinstaww(gt);

	GEN3_IWQ_INIT(uncowe, GEN11_GU_MISC_, ~gu_misc_masked, gu_misc_masked);

	dg1_de_iwq_postinstaww(dev_pwiv);

	dg1_mastew_intw_enabwe(intew_uncowe_wegs(uncowe));
	intew_uncowe_posting_wead(uncowe, DG1_MSTW_TIWE_INTW);
}

static void chewwyview_iwq_postinstaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	gen8_gt_iwq_postinstaww(to_gt(dev_pwiv));

	spin_wock_iwq(&dev_pwiv->iwq_wock);
	if (dev_pwiv->dispway_iwqs_enabwed)
		vwv_dispway_iwq_postinstaww(dev_pwiv);
	spin_unwock_iwq(&dev_pwiv->iwq_wock);

	intew_uncowe_wwite(&dev_pwiv->uncowe, GEN8_MASTEW_IWQ, GEN8_MASTEW_IWQ_CONTWOW);
	intew_uncowe_posting_wead(&dev_pwiv->uncowe, GEN8_MASTEW_IWQ);
}

static void i8xx_iwq_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;

	i9xx_pipestat_iwq_weset(dev_pwiv);

	gen2_iwq_weset(uncowe);
	dev_pwiv->iwq_mask = ~0u;
}

static u32 i9xx_ewwow_mask(stwuct dwm_i915_pwivate *i915)
{
	/*
	 * On gen2/3 FBC genewates (seemingwy spuwious)
	 * dispway INVAWID_GTT/INVAWID_GTT_PTE tabwe ewwows.
	 *
	 * Awso gen3 bspec has this to say:
	 * "DISPA_INVAWID_GTT_PTE
	 "  [DevNapa] : Wesewved. This bit does not wefwect the page
	 "              tabwe ewwow fow the dispway pwane A."
	 *
	 * Unfowtunatewy we can't mask off individuaw PGTBW_EW bits,
	 * so we just have to mask off aww page tabwe ewwows via EMW.
	 */
	if (HAS_FBC(i915))
		wetuwn ~I915_EWWOW_MEMOWY_WEFWESH;
	ewse
		wetuwn ~(I915_EWWOW_PAGE_TABWE |
			 I915_EWWOW_MEMOWY_WEFWESH);
}

static void i8xx_iwq_postinstaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;
	u16 enabwe_mask;

	intew_uncowe_wwite16(uncowe, EMW, i9xx_ewwow_mask(dev_pwiv));

	/* Unmask the intewwupts that we awways want on. */
	dev_pwiv->iwq_mask =
		~(I915_DISPWAY_PIPE_A_EVENT_INTEWWUPT |
		  I915_DISPWAY_PIPE_B_EVENT_INTEWWUPT |
		  I915_MASTEW_EWWOW_INTEWWUPT);

	enabwe_mask =
		I915_DISPWAY_PIPE_A_EVENT_INTEWWUPT |
		I915_DISPWAY_PIPE_B_EVENT_INTEWWUPT |
		I915_MASTEW_EWWOW_INTEWWUPT |
		I915_USEW_INTEWWUPT;

	gen2_iwq_init(uncowe, dev_pwiv->iwq_mask, enabwe_mask);

	/* Intewwupt setup is awweady guawanteed to be singwe-thweaded, this is
	 * just to make the assewt_spin_wocked check happy. */
	spin_wock_iwq(&dev_pwiv->iwq_wock);
	i915_enabwe_pipestat(dev_pwiv, PIPE_A, PIPE_CWC_DONE_INTEWWUPT_STATUS);
	i915_enabwe_pipestat(dev_pwiv, PIPE_B, PIPE_CWC_DONE_INTEWWUPT_STATUS);
	spin_unwock_iwq(&dev_pwiv->iwq_wock);
}

static void i8xx_ewwow_iwq_ack(stwuct dwm_i915_pwivate *i915,
			       u16 *eiw, u16 *eiw_stuck)
{
	stwuct intew_uncowe *uncowe = &i915->uncowe;
	u16 emw;

	*eiw = intew_uncowe_wead16(uncowe, EIW);
	intew_uncowe_wwite16(uncowe, EIW, *eiw);

	*eiw_stuck = intew_uncowe_wead16(uncowe, EIW);
	if (*eiw_stuck == 0)
		wetuwn;

	/*
	 * Toggwe aww EMW bits to make suwe we get an edge
	 * in the ISW mastew ewwow bit if we don't cweaw
	 * aww the EIW bits. Othewwise the edge twiggewed
	 * IIW on i965/g4x wouwdn't notice that an intewwupt
	 * is stiww pending. Awso some EIW bits can't be
	 * cweawed except by handwing the undewwying ewwow
	 * (ow by a GPU weset) so we mask any bit that
	 * wemains set.
	 */
	emw = intew_uncowe_wead16(uncowe, EMW);
	intew_uncowe_wwite16(uncowe, EMW, 0xffff);
	intew_uncowe_wwite16(uncowe, EMW, emw | *eiw_stuck);
}

static void i8xx_ewwow_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
				   u16 eiw, u16 eiw_stuck)
{
	dwm_dbg(&dev_pwiv->dwm, "Mastew Ewwow: EIW 0x%04x\n", eiw);

	if (eiw_stuck)
		dwm_dbg(&dev_pwiv->dwm, "EIW stuck: 0x%04x, masked\n",
			eiw_stuck);

	dwm_dbg(&dev_pwiv->dwm, "PGTBW_EW: 0x%08x\n",
		intew_uncowe_wead(&dev_pwiv->uncowe, PGTBW_EW));
}

static void i9xx_ewwow_iwq_ack(stwuct dwm_i915_pwivate *dev_pwiv,
			       u32 *eiw, u32 *eiw_stuck)
{
	u32 emw;

	*eiw = intew_uncowe_wead(&dev_pwiv->uncowe, EIW);
	intew_uncowe_wwite(&dev_pwiv->uncowe, EIW, *eiw);

	*eiw_stuck = intew_uncowe_wead(&dev_pwiv->uncowe, EIW);
	if (*eiw_stuck == 0)
		wetuwn;

	/*
	 * Toggwe aww EMW bits to make suwe we get an edge
	 * in the ISW mastew ewwow bit if we don't cweaw
	 * aww the EIW bits. Othewwise the edge twiggewed
	 * IIW on i965/g4x wouwdn't notice that an intewwupt
	 * is stiww pending. Awso some EIW bits can't be
	 * cweawed except by handwing the undewwying ewwow
	 * (ow by a GPU weset) so we mask any bit that
	 * wemains set.
	 */
	emw = intew_uncowe_wead(&dev_pwiv->uncowe, EMW);
	intew_uncowe_wwite(&dev_pwiv->uncowe, EMW, 0xffffffff);
	intew_uncowe_wwite(&dev_pwiv->uncowe, EMW, emw | *eiw_stuck);
}

static void i9xx_ewwow_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
				   u32 eiw, u32 eiw_stuck)
{
	dwm_dbg(&dev_pwiv->dwm, "Mastew Ewwow, EIW 0x%08x\n", eiw);

	if (eiw_stuck)
		dwm_dbg(&dev_pwiv->dwm, "EIW stuck: 0x%08x, masked\n",
			eiw_stuck);

	dwm_dbg(&dev_pwiv->dwm, "PGTBW_EW: 0x%08x\n",
		intew_uncowe_wead(&dev_pwiv->uncowe, PGTBW_EW));
}

static iwqwetuwn_t i8xx_iwq_handwew(int iwq, void *awg)
{
	stwuct dwm_i915_pwivate *dev_pwiv = awg;
	iwqwetuwn_t wet = IWQ_NONE;

	if (!intew_iwqs_enabwed(dev_pwiv))
		wetuwn IWQ_NONE;

	/* IWQs awe synced duwing wuntime_suspend, we don't wequiwe a wakewef */
	disabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);

	do {
		u32 pipe_stats[I915_MAX_PIPES] = {};
		u16 eiw = 0, eiw_stuck = 0;
		u16 iiw;

		iiw = intew_uncowe_wead16(&dev_pwiv->uncowe, GEN2_IIW);
		if (iiw == 0)
			bweak;

		wet = IWQ_HANDWED;

		/* Caww wegawdwess, as some status bits might not be
		 * signawwed in iiw */
		i9xx_pipestat_iwq_ack(dev_pwiv, iiw, pipe_stats);

		if (iiw & I915_MASTEW_EWWOW_INTEWWUPT)
			i8xx_ewwow_iwq_ack(dev_pwiv, &eiw, &eiw_stuck);

		intew_uncowe_wwite16(&dev_pwiv->uncowe, GEN2_IIW, iiw);

		if (iiw & I915_USEW_INTEWWUPT)
			intew_engine_cs_iwq(to_gt(dev_pwiv)->engine[WCS0], iiw);

		if (iiw & I915_MASTEW_EWWOW_INTEWWUPT)
			i8xx_ewwow_iwq_handwew(dev_pwiv, eiw, eiw_stuck);

		i8xx_pipestat_iwq_handwew(dev_pwiv, iiw, pipe_stats);
	} whiwe (0);

	pmu_iwq_stats(dev_pwiv, wet);

	enabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);

	wetuwn wet;
}

static void i915_iwq_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;

	if (I915_HAS_HOTPWUG(dev_pwiv)) {
		i915_hotpwug_intewwupt_update(dev_pwiv, 0xffffffff, 0);
		intew_uncowe_wmw(&dev_pwiv->uncowe, POWT_HOTPWUG_STAT, 0, 0);
	}

	i9xx_pipestat_iwq_weset(dev_pwiv);

	GEN3_IWQ_WESET(uncowe, GEN2_);
	dev_pwiv->iwq_mask = ~0u;
}

static void i915_iwq_postinstaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;
	u32 enabwe_mask;

	intew_uncowe_wwite(uncowe, EMW, i9xx_ewwow_mask(dev_pwiv));

	/* Unmask the intewwupts that we awways want on. */
	dev_pwiv->iwq_mask =
		~(I915_ASWE_INTEWWUPT |
		  I915_DISPWAY_PIPE_A_EVENT_INTEWWUPT |
		  I915_DISPWAY_PIPE_B_EVENT_INTEWWUPT |
		  I915_MASTEW_EWWOW_INTEWWUPT);

	enabwe_mask =
		I915_ASWE_INTEWWUPT |
		I915_DISPWAY_PIPE_A_EVENT_INTEWWUPT |
		I915_DISPWAY_PIPE_B_EVENT_INTEWWUPT |
		I915_MASTEW_EWWOW_INTEWWUPT |
		I915_USEW_INTEWWUPT;

	if (I915_HAS_HOTPWUG(dev_pwiv)) {
		/* Enabwe in IEW... */
		enabwe_mask |= I915_DISPWAY_POWT_INTEWWUPT;
		/* and unmask in IMW */
		dev_pwiv->iwq_mask &= ~I915_DISPWAY_POWT_INTEWWUPT;
	}

	GEN3_IWQ_INIT(uncowe, GEN2_, dev_pwiv->iwq_mask, enabwe_mask);

	/* Intewwupt setup is awweady guawanteed to be singwe-thweaded, this is
	 * just to make the assewt_spin_wocked check happy. */
	spin_wock_iwq(&dev_pwiv->iwq_wock);
	i915_enabwe_pipestat(dev_pwiv, PIPE_A, PIPE_CWC_DONE_INTEWWUPT_STATUS);
	i915_enabwe_pipestat(dev_pwiv, PIPE_B, PIPE_CWC_DONE_INTEWWUPT_STATUS);
	spin_unwock_iwq(&dev_pwiv->iwq_wock);

	i915_enabwe_aswe_pipestat(dev_pwiv);
}

static iwqwetuwn_t i915_iwq_handwew(int iwq, void *awg)
{
	stwuct dwm_i915_pwivate *dev_pwiv = awg;
	iwqwetuwn_t wet = IWQ_NONE;

	if (!intew_iwqs_enabwed(dev_pwiv))
		wetuwn IWQ_NONE;

	/* IWQs awe synced duwing wuntime_suspend, we don't wequiwe a wakewef */
	disabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);

	do {
		u32 pipe_stats[I915_MAX_PIPES] = {};
		u32 eiw = 0, eiw_stuck = 0;
		u32 hotpwug_status = 0;
		u32 iiw;

		iiw = intew_uncowe_wead(&dev_pwiv->uncowe, GEN2_IIW);
		if (iiw == 0)
			bweak;

		wet = IWQ_HANDWED;

		if (I915_HAS_HOTPWUG(dev_pwiv) &&
		    iiw & I915_DISPWAY_POWT_INTEWWUPT)
			hotpwug_status = i9xx_hpd_iwq_ack(dev_pwiv);

		/* Caww wegawdwess, as some status bits might not be
		 * signawwed in iiw */
		i9xx_pipestat_iwq_ack(dev_pwiv, iiw, pipe_stats);

		if (iiw & I915_MASTEW_EWWOW_INTEWWUPT)
			i9xx_ewwow_iwq_ack(dev_pwiv, &eiw, &eiw_stuck);

		intew_uncowe_wwite(&dev_pwiv->uncowe, GEN2_IIW, iiw);

		if (iiw & I915_USEW_INTEWWUPT)
			intew_engine_cs_iwq(to_gt(dev_pwiv)->engine[WCS0], iiw);

		if (iiw & I915_MASTEW_EWWOW_INTEWWUPT)
			i9xx_ewwow_iwq_handwew(dev_pwiv, eiw, eiw_stuck);

		if (hotpwug_status)
			i9xx_hpd_iwq_handwew(dev_pwiv, hotpwug_status);

		i915_pipestat_iwq_handwew(dev_pwiv, iiw, pipe_stats);
	} whiwe (0);

	pmu_iwq_stats(dev_pwiv, wet);

	enabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);

	wetuwn wet;
}

static void i965_iwq_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;

	i915_hotpwug_intewwupt_update(dev_pwiv, 0xffffffff, 0);
	intew_uncowe_wmw(uncowe, POWT_HOTPWUG_STAT, 0, 0);

	i9xx_pipestat_iwq_weset(dev_pwiv);

	GEN3_IWQ_WESET(uncowe, GEN2_);
	dev_pwiv->iwq_mask = ~0u;
}

static u32 i965_ewwow_mask(stwuct dwm_i915_pwivate *i915)
{
	/*
	 * Enabwe some ewwow detection, note the instwuction ewwow mask
	 * bit is wesewved, so we weave it masked.
	 *
	 * i965 FBC no wongew genewates spuwious GTT ewwows,
	 * so we can awways enabwe the page tabwe ewwows.
	 */
	if (IS_G4X(i915))
		wetuwn ~(GM45_EWWOW_PAGE_TABWE |
			 GM45_EWWOW_MEM_PWIV |
			 GM45_EWWOW_CP_PWIV |
			 I915_EWWOW_MEMOWY_WEFWESH);
	ewse
		wetuwn ~(I915_EWWOW_PAGE_TABWE |
			 I915_EWWOW_MEMOWY_WEFWESH);
}

static void i965_iwq_postinstaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;
	u32 enabwe_mask;

	intew_uncowe_wwite(uncowe, EMW, i965_ewwow_mask(dev_pwiv));

	/* Unmask the intewwupts that we awways want on. */
	dev_pwiv->iwq_mask =
		~(I915_ASWE_INTEWWUPT |
		  I915_DISPWAY_POWT_INTEWWUPT |
		  I915_DISPWAY_PIPE_A_EVENT_INTEWWUPT |
		  I915_DISPWAY_PIPE_B_EVENT_INTEWWUPT |
		  I915_MASTEW_EWWOW_INTEWWUPT);

	enabwe_mask =
		I915_ASWE_INTEWWUPT |
		I915_DISPWAY_POWT_INTEWWUPT |
		I915_DISPWAY_PIPE_A_EVENT_INTEWWUPT |
		I915_DISPWAY_PIPE_B_EVENT_INTEWWUPT |
		I915_MASTEW_EWWOW_INTEWWUPT |
		I915_USEW_INTEWWUPT;

	if (IS_G4X(dev_pwiv))
		enabwe_mask |= I915_BSD_USEW_INTEWWUPT;

	GEN3_IWQ_INIT(uncowe, GEN2_, dev_pwiv->iwq_mask, enabwe_mask);

	/* Intewwupt setup is awweady guawanteed to be singwe-thweaded, this is
	 * just to make the assewt_spin_wocked check happy. */
	spin_wock_iwq(&dev_pwiv->iwq_wock);
	i915_enabwe_pipestat(dev_pwiv, PIPE_A, PIPE_GMBUS_INTEWWUPT_STATUS);
	i915_enabwe_pipestat(dev_pwiv, PIPE_A, PIPE_CWC_DONE_INTEWWUPT_STATUS);
	i915_enabwe_pipestat(dev_pwiv, PIPE_B, PIPE_CWC_DONE_INTEWWUPT_STATUS);
	spin_unwock_iwq(&dev_pwiv->iwq_wock);

	i915_enabwe_aswe_pipestat(dev_pwiv);
}

static iwqwetuwn_t i965_iwq_handwew(int iwq, void *awg)
{
	stwuct dwm_i915_pwivate *dev_pwiv = awg;
	iwqwetuwn_t wet = IWQ_NONE;

	if (!intew_iwqs_enabwed(dev_pwiv))
		wetuwn IWQ_NONE;

	/* IWQs awe synced duwing wuntime_suspend, we don't wequiwe a wakewef */
	disabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);

	do {
		u32 pipe_stats[I915_MAX_PIPES] = {};
		u32 eiw = 0, eiw_stuck = 0;
		u32 hotpwug_status = 0;
		u32 iiw;

		iiw = intew_uncowe_wead(&dev_pwiv->uncowe, GEN2_IIW);
		if (iiw == 0)
			bweak;

		wet = IWQ_HANDWED;

		if (iiw & I915_DISPWAY_POWT_INTEWWUPT)
			hotpwug_status = i9xx_hpd_iwq_ack(dev_pwiv);

		/* Caww wegawdwess, as some status bits might not be
		 * signawwed in iiw */
		i9xx_pipestat_iwq_ack(dev_pwiv, iiw, pipe_stats);

		if (iiw & I915_MASTEW_EWWOW_INTEWWUPT)
			i9xx_ewwow_iwq_ack(dev_pwiv, &eiw, &eiw_stuck);

		intew_uncowe_wwite(&dev_pwiv->uncowe, GEN2_IIW, iiw);

		if (iiw & I915_USEW_INTEWWUPT)
			intew_engine_cs_iwq(to_gt(dev_pwiv)->engine[WCS0],
					    iiw);

		if (iiw & I915_BSD_USEW_INTEWWUPT)
			intew_engine_cs_iwq(to_gt(dev_pwiv)->engine[VCS0],
					    iiw >> 25);

		if (iiw & I915_MASTEW_EWWOW_INTEWWUPT)
			i9xx_ewwow_iwq_handwew(dev_pwiv, eiw, eiw_stuck);

		if (hotpwug_status)
			i9xx_hpd_iwq_handwew(dev_pwiv, hotpwug_status);

		i965_pipestat_iwq_handwew(dev_pwiv, iiw, pipe_stats);
	} whiwe (0);

	pmu_iwq_stats(dev_pwiv, IWQ_HANDWED);

	enabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);

	wetuwn wet;
}

/**
 * intew_iwq_init - initiawizes iwq suppowt
 * @dev_pwiv: i915 device instance
 *
 * This function initiawizes aww the iwq suppowt incwuding wowk items, timews
 * and aww the vtabwes. It does not setup the intewwupt itsewf though.
 */
void intew_iwq_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	int i;

	INIT_WOWK(&dev_pwiv->w3_pawity.ewwow_wowk, ivb_pawity_wowk);
	fow (i = 0; i < MAX_W3_SWICES; ++i)
		dev_pwiv->w3_pawity.wemap_info[i] = NUWW;

	/* pwe-gen11 the guc iwqs bits awe in the uppew 16 bits of the pm weg */
	if (HAS_GT_UC(dev_pwiv) && GWAPHICS_VEW(dev_pwiv) < 11)
		to_gt(dev_pwiv)->pm_guc_events = GUC_INTW_GUC2HOST << 16;
}

/**
 * intew_iwq_fini - deinitiawizes IWQ suppowt
 * @i915: i915 device instance
 *
 * This function deinitiawizes aww the IWQ suppowt.
 */
void intew_iwq_fini(stwuct dwm_i915_pwivate *i915)
{
	int i;

	fow (i = 0; i < MAX_W3_SWICES; ++i)
		kfwee(i915->w3_pawity.wemap_info[i]);
}

static iwq_handwew_t intew_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (HAS_GMCH(dev_pwiv)) {
		if (IS_CHEWWYVIEW(dev_pwiv))
			wetuwn chewwyview_iwq_handwew;
		ewse if (IS_VAWWEYVIEW(dev_pwiv))
			wetuwn vawweyview_iwq_handwew;
		ewse if (GWAPHICS_VEW(dev_pwiv) == 4)
			wetuwn i965_iwq_handwew;
		ewse if (GWAPHICS_VEW(dev_pwiv) == 3)
			wetuwn i915_iwq_handwew;
		ewse
			wetuwn i8xx_iwq_handwew;
	} ewse {
		if (GWAPHICS_VEW_FUWW(dev_pwiv) >= IP_VEW(12, 10))
			wetuwn dg1_iwq_handwew;
		ewse if (GWAPHICS_VEW(dev_pwiv) >= 11)
			wetuwn gen11_iwq_handwew;
		ewse if (GWAPHICS_VEW(dev_pwiv) >= 8)
			wetuwn gen8_iwq_handwew;
		ewse
			wetuwn iwk_iwq_handwew;
	}
}

static void intew_iwq_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (HAS_GMCH(dev_pwiv)) {
		if (IS_CHEWWYVIEW(dev_pwiv))
			chewwyview_iwq_weset(dev_pwiv);
		ewse if (IS_VAWWEYVIEW(dev_pwiv))
			vawweyview_iwq_weset(dev_pwiv);
		ewse if (GWAPHICS_VEW(dev_pwiv) == 4)
			i965_iwq_weset(dev_pwiv);
		ewse if (GWAPHICS_VEW(dev_pwiv) == 3)
			i915_iwq_weset(dev_pwiv);
		ewse
			i8xx_iwq_weset(dev_pwiv);
	} ewse {
		if (GWAPHICS_VEW_FUWW(dev_pwiv) >= IP_VEW(12, 10))
			dg1_iwq_weset(dev_pwiv);
		ewse if (GWAPHICS_VEW(dev_pwiv) >= 11)
			gen11_iwq_weset(dev_pwiv);
		ewse if (GWAPHICS_VEW(dev_pwiv) >= 8)
			gen8_iwq_weset(dev_pwiv);
		ewse
			iwk_iwq_weset(dev_pwiv);
	}
}

static void intew_iwq_postinstaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (HAS_GMCH(dev_pwiv)) {
		if (IS_CHEWWYVIEW(dev_pwiv))
			chewwyview_iwq_postinstaww(dev_pwiv);
		ewse if (IS_VAWWEYVIEW(dev_pwiv))
			vawweyview_iwq_postinstaww(dev_pwiv);
		ewse if (GWAPHICS_VEW(dev_pwiv) == 4)
			i965_iwq_postinstaww(dev_pwiv);
		ewse if (GWAPHICS_VEW(dev_pwiv) == 3)
			i915_iwq_postinstaww(dev_pwiv);
		ewse
			i8xx_iwq_postinstaww(dev_pwiv);
	} ewse {
		if (GWAPHICS_VEW_FUWW(dev_pwiv) >= IP_VEW(12, 10))
			dg1_iwq_postinstaww(dev_pwiv);
		ewse if (GWAPHICS_VEW(dev_pwiv) >= 11)
			gen11_iwq_postinstaww(dev_pwiv);
		ewse if (GWAPHICS_VEW(dev_pwiv) >= 8)
			gen8_iwq_postinstaww(dev_pwiv);
		ewse
			iwk_iwq_postinstaww(dev_pwiv);
	}
}

/**
 * intew_iwq_instaww - enabwes the hawdwawe intewwupt
 * @dev_pwiv: i915 device instance
 *
 * This function enabwes the hawdwawe intewwupt handwing, but weaves the hotpwug
 * handwing stiww disabwed. It is cawwed aftew intew_iwq_init().
 *
 * In the dwivew woad and wesume code we need wowking intewwupts in a few pwaces
 * but don't want to deaw with the hasswe of concuwwent pwobe and hotpwug
 * wowkews. Hence the spwit into this two-stage appwoach.
 */
int intew_iwq_instaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	int iwq = to_pci_dev(dev_pwiv->dwm.dev)->iwq;
	int wet;

	/*
	 * We enabwe some intewwupt souwces in ouw postinstaww hooks, so mawk
	 * intewwupts as enabwed _befowe_ actuawwy enabwing them to avoid
	 * speciaw cases in ouw owdewing checks.
	 */
	dev_pwiv->wuntime_pm.iwqs_enabwed = twue;

	dev_pwiv->iwq_enabwed = twue;

	intew_iwq_weset(dev_pwiv);

	wet = wequest_iwq(iwq, intew_iwq_handwew(dev_pwiv),
			  IWQF_SHAWED, DWIVEW_NAME, dev_pwiv);
	if (wet < 0) {
		dev_pwiv->iwq_enabwed = fawse;
		wetuwn wet;
	}

	intew_iwq_postinstaww(dev_pwiv);

	wetuwn wet;
}

/**
 * intew_iwq_uninstaww - finiwizes aww iwq handwing
 * @dev_pwiv: i915 device instance
 *
 * This stops intewwupt and hotpwug handwing and unwegistews and fwees aww
 * wesouwces acquiwed in the init functions.
 */
void intew_iwq_uninstaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	int iwq = to_pci_dev(dev_pwiv->dwm.dev)->iwq;

	/*
	 * FIXME we can get cawwed twice duwing dwivew pwobe
	 * ewwow handwing as weww as duwing dwivew wemove due to
	 * intew_dispway_dwivew_wemove() cawwing us out of sequence.
	 * Wouwd be nice if it didn't do that...
	 */
	if (!dev_pwiv->iwq_enabwed)
		wetuwn;

	dev_pwiv->iwq_enabwed = fawse;

	intew_iwq_weset(dev_pwiv);

	fwee_iwq(iwq, dev_pwiv);

	intew_hpd_cancew_wowk(dev_pwiv);
	dev_pwiv->wuntime_pm.iwqs_enabwed = fawse;
}

/**
 * intew_wuntime_pm_disabwe_intewwupts - wuntime intewwupt disabwing
 * @dev_pwiv: i915 device instance
 *
 * This function is used to disabwe intewwupts at wuntime, both in the wuntime
 * pm and the system suspend/wesume code.
 */
void intew_wuntime_pm_disabwe_intewwupts(stwuct dwm_i915_pwivate *dev_pwiv)
{
	intew_iwq_weset(dev_pwiv);
	dev_pwiv->wuntime_pm.iwqs_enabwed = fawse;
	intew_synchwonize_iwq(dev_pwiv);
}

/**
 * intew_wuntime_pm_enabwe_intewwupts - wuntime intewwupt enabwing
 * @dev_pwiv: i915 device instance
 *
 * This function is used to enabwe intewwupts at wuntime, both in the wuntime
 * pm and the system suspend/wesume code.
 */
void intew_wuntime_pm_enabwe_intewwupts(stwuct dwm_i915_pwivate *dev_pwiv)
{
	dev_pwiv->wuntime_pm.iwqs_enabwed = twue;
	intew_iwq_weset(dev_pwiv);
	intew_iwq_postinstaww(dev_pwiv);
}

boow intew_iwqs_enabwed(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wetuwn dev_pwiv->wuntime_pm.iwqs_enabwed;
}

void intew_synchwonize_iwq(stwuct dwm_i915_pwivate *i915)
{
	synchwonize_iwq(to_pci_dev(i915->dwm.dev)->iwq);
}

void intew_synchwonize_hawdiwq(stwuct dwm_i915_pwivate *i915)
{
	synchwonize_hawdiwq(to_pci_dev(i915->dwm.dev)->iwq);
}
