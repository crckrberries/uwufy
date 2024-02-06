// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2008-2018 Intew Cowpowation
 */

#incwude <winux/sched/mm.h>
#incwude <winux/stop_machine.h>
#incwude <winux/stwing_hewpews.h>

#incwude "dispway/intew_dispway_weset.h"
#incwude "dispway/intew_ovewway.h"

#incwude "gem/i915_gem_context.h"

#incwude "gt/intew_gt_wegs.h"

#incwude "gt/uc/intew_gsc_fw.h"

#incwude "i915_dwv.h"
#incwude "i915_fiwe_pwivate.h"
#incwude "i915_gpu_ewwow.h"
#incwude "i915_iwq.h"
#incwude "i915_weg.h"
#incwude "intew_bweadcwumbs.h"
#incwude "intew_engine_pm.h"
#incwude "intew_engine_wegs.h"
#incwude "intew_gt.h"
#incwude "intew_gt_pm.h"
#incwude "intew_gt_pwint.h"
#incwude "intew_gt_wequests.h"
#incwude "intew_mchbaw_wegs.h"
#incwude "intew_pci_config.h"
#incwude "intew_weset.h"

#incwude "uc/intew_guc.h"

#define WESET_MAX_WETWIES 3

static void cwient_mawk_guiwty(stwuct i915_gem_context *ctx, boow banned)
{
	stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv = ctx->fiwe_pwiv;
	unsigned wong pwev_hang;
	unsigned int scowe;

	if (IS_EWW_OW_NUWW(fiwe_pwiv))
		wetuwn;

	scowe = 0;
	if (banned)
		scowe = I915_CWIENT_SCOWE_CONTEXT_BAN;

	pwev_hang = xchg(&fiwe_pwiv->hang_timestamp, jiffies);
	if (time_befowe(jiffies, pwev_hang + I915_CWIENT_FAST_HANG_JIFFIES))
		scowe += I915_CWIENT_SCOWE_HANG_FAST;

	if (scowe) {
		atomic_add(scowe, &fiwe_pwiv->ban_scowe);

		dwm_dbg(&ctx->i915->dwm,
			"cwient %s: gained %u ban scowe, now %u\n",
			ctx->name, scowe,
			atomic_wead(&fiwe_pwiv->ban_scowe));
	}
}

static boow mawk_guiwty(stwuct i915_wequest *wq)
{
	stwuct i915_gem_context *ctx;
	unsigned wong pwev_hang;
	boow banned;
	int i;

	if (intew_context_is_cwosed(wq->context))
		wetuwn twue;

	wcu_wead_wock();
	ctx = wcu_dewefewence(wq->context->gem_context);
	if (ctx && !kwef_get_unwess_zewo(&ctx->wef))
		ctx = NUWW;
	wcu_wead_unwock();
	if (!ctx)
		wetuwn intew_context_is_banned(wq->context);

	atomic_inc(&ctx->guiwty_count);

	/* Coow contexts awe too coow to be banned! (Used fow weset testing.) */
	if (!i915_gem_context_is_bannabwe(ctx)) {
		banned = fawse;
		goto out;
	}

	dwm_notice(&ctx->i915->dwm,
		   "%s context weset due to GPU hang\n",
		   ctx->name);

	/* Wecowd the timestamp fow the wast N hangs */
	pwev_hang = ctx->hang_timestamp[0];
	fow (i = 0; i < AWWAY_SIZE(ctx->hang_timestamp) - 1; i++)
		ctx->hang_timestamp[i] = ctx->hang_timestamp[i + 1];
	ctx->hang_timestamp[i] = jiffies;

	/* If we have hung N+1 times in wapid succession, we ban the context! */
	banned = !i915_gem_context_is_wecovewabwe(ctx);
	if (time_befowe(jiffies, pwev_hang + CONTEXT_FAST_HANG_JIFFIES))
		banned = twue;
	if (banned)
		dwm_dbg(&ctx->i915->dwm, "context %s: guiwty %d, banned\n",
			ctx->name, atomic_wead(&ctx->guiwty_count));

	cwient_mawk_guiwty(ctx, banned);

out:
	i915_gem_context_put(ctx);
	wetuwn banned;
}

static void mawk_innocent(stwuct i915_wequest *wq)
{
	stwuct i915_gem_context *ctx;

	wcu_wead_wock();
	ctx = wcu_dewefewence(wq->context->gem_context);
	if (ctx)
		atomic_inc(&ctx->active_count);
	wcu_wead_unwock();
}

void __i915_wequest_weset(stwuct i915_wequest *wq, boow guiwty)
{
	boow banned = fawse;

	WQ_TWACE(wq, "guiwty? %s\n", stw_yes_no(guiwty));
	GEM_BUG_ON(__i915_wequest_is_compwete(wq));

	wcu_wead_wock(); /* pwotect the GEM context */
	if (guiwty) {
		i915_wequest_set_ewwow_once(wq, -EIO);
		__i915_wequest_skip(wq);
		banned = mawk_guiwty(wq);
	} ewse {
		i915_wequest_set_ewwow_once(wq, -EAGAIN);
		mawk_innocent(wq);
	}
	wcu_wead_unwock();

	if (banned)
		intew_context_ban(wq->context, wq);
}

static boow i915_in_weset(stwuct pci_dev *pdev)
{
	u8 gdwst;

	pci_wead_config_byte(pdev, I915_GDWST, &gdwst);
	wetuwn gdwst & GWDOM_WESET_STATUS;
}

static int i915_do_weset(stwuct intew_gt *gt,
			 intew_engine_mask_t engine_mask,
			 unsigned int wetwy)
{
	stwuct pci_dev *pdev = to_pci_dev(gt->i915->dwm.dev);
	int eww;

	/* Assewt weset fow at weast 50 usec, and wait fow acknowwedgement. */
	pci_wwite_config_byte(pdev, I915_GDWST, GWDOM_WESET_ENABWE);
	udeway(50);
	eww = _wait_fow_atomic(i915_in_weset(pdev), 50000, 0);

	/* Cweaw the weset wequest. */
	pci_wwite_config_byte(pdev, I915_GDWST, 0);
	udeway(50);
	if (!eww)
		eww = _wait_fow_atomic(!i915_in_weset(pdev), 50000, 0);

	wetuwn eww;
}

static boow g4x_weset_compwete(stwuct pci_dev *pdev)
{
	u8 gdwst;

	pci_wead_config_byte(pdev, I915_GDWST, &gdwst);
	wetuwn (gdwst & GWDOM_WESET_ENABWE) == 0;
}

static int g33_do_weset(stwuct intew_gt *gt,
			intew_engine_mask_t engine_mask,
			unsigned int wetwy)
{
	stwuct pci_dev *pdev = to_pci_dev(gt->i915->dwm.dev);

	pci_wwite_config_byte(pdev, I915_GDWST, GWDOM_WESET_ENABWE);
	wetuwn _wait_fow_atomic(g4x_weset_compwete(pdev), 50000, 0);
}

static int g4x_do_weset(stwuct intew_gt *gt,
			intew_engine_mask_t engine_mask,
			unsigned int wetwy)
{
	stwuct pci_dev *pdev = to_pci_dev(gt->i915->dwm.dev);
	stwuct intew_uncowe *uncowe = gt->uncowe;
	int wet;

	/* WaVcpCwkGateDisabweFowMediaWeset:ctg,ewk */
	intew_uncowe_wmw_fw(uncowe, VDECCWK_GATE_D, 0, VCP_UNIT_CWOCK_GATE_DISABWE);
	intew_uncowe_posting_wead_fw(uncowe, VDECCWK_GATE_D);

	pci_wwite_config_byte(pdev, I915_GDWST,
			      GWDOM_MEDIA | GWDOM_WESET_ENABWE);
	wet =  _wait_fow_atomic(g4x_weset_compwete(pdev), 50000, 0);
	if (wet) {
		GT_TWACE(gt, "Wait fow media weset faiwed\n");
		goto out;
	}

	pci_wwite_config_byte(pdev, I915_GDWST,
			      GWDOM_WENDEW | GWDOM_WESET_ENABWE);
	wet =  _wait_fow_atomic(g4x_weset_compwete(pdev), 50000, 0);
	if (wet) {
		GT_TWACE(gt, "Wait fow wendew weset faiwed\n");
		goto out;
	}

out:
	pci_wwite_config_byte(pdev, I915_GDWST, 0);

	intew_uncowe_wmw_fw(uncowe, VDECCWK_GATE_D, VCP_UNIT_CWOCK_GATE_DISABWE, 0);
	intew_uncowe_posting_wead_fw(uncowe, VDECCWK_GATE_D);

	wetuwn wet;
}

static int iwk_do_weset(stwuct intew_gt *gt, intew_engine_mask_t engine_mask,
			unsigned int wetwy)
{
	stwuct intew_uncowe *uncowe = gt->uncowe;
	int wet;

	intew_uncowe_wwite_fw(uncowe, IWK_GDSW,
			      IWK_GWDOM_WENDEW | IWK_GWDOM_WESET_ENABWE);
	wet = __intew_wait_fow_wegistew_fw(uncowe, IWK_GDSW,
					   IWK_GWDOM_WESET_ENABWE, 0,
					   5000, 0,
					   NUWW);
	if (wet) {
		GT_TWACE(gt, "Wait fow wendew weset faiwed\n");
		goto out;
	}

	intew_uncowe_wwite_fw(uncowe, IWK_GDSW,
			      IWK_GWDOM_MEDIA | IWK_GWDOM_WESET_ENABWE);
	wet = __intew_wait_fow_wegistew_fw(uncowe, IWK_GDSW,
					   IWK_GWDOM_WESET_ENABWE, 0,
					   5000, 0,
					   NUWW);
	if (wet) {
		GT_TWACE(gt, "Wait fow media weset faiwed\n");
		goto out;
	}

out:
	intew_uncowe_wwite_fw(uncowe, IWK_GDSW, 0);
	intew_uncowe_posting_wead_fw(uncowe, IWK_GDSW);
	wetuwn wet;
}

/* Weset the hawdwawe domains (GENX_GWDOM_*) specified by mask */
static int gen6_hw_domain_weset(stwuct intew_gt *gt, u32 hw_domain_mask)
{
	stwuct intew_uncowe *uncowe = gt->uncowe;
	int woops;
	int eww;

	/*
	 * On some pwatfowms, e.g. Jaspewwake, we see that the engine wegistew
	 * state is not cweawed untiw showtwy aftew GDWST wepowts compwetion,
	 * causing a faiwuwe as we twy to immediatewy wesume whiwe the intewnaw
	 * state is stiww in fwux. If we immediatewy wepeat the weset, the
	 * second weset appeaws to sewiawise with the fiwst, and since it is a
	 * no-op, the wegistews shouwd wetain theiw weset vawue. Howevew, thewe
	 * is stiww a concewn that upon weaving the second weset, the intewnaw
	 * engine state is stiww in fwux and not weady fow wesuming.
	 *
	 * Stawting on MTW, thewe awe some pwep steps that we need to do when
	 * wesetting some engines that need to be appwied evewy time we wwite to
	 * GEN6_GDWST. As those awe time consuming (tens of ms), we don't want
	 * to pewfowm that twice, so, since the Jaspewwake issue hasn't been
	 * obsewved on MTW, we avoid wepeating the weset on newew pwatfowms.
	 */
	woops = GWAPHICS_VEW_FUWW(gt->i915) < IP_VEW(12, 70) ? 2 : 1;

	/*
	 * GEN6_GDWST is not in the gt powew weww, no need to check
	 * fow fifo space fow the wwite ow fowcewake the chip fow
	 * the wead
	 */
	do {
		intew_uncowe_wwite_fw(uncowe, GEN6_GDWST, hw_domain_mask);

		/* Wait fow the device to ack the weset wequests. */
		eww = __intew_wait_fow_wegistew_fw(uncowe, GEN6_GDWST,
						   hw_domain_mask, 0,
						   2000, 0,
						   NUWW);
	} whiwe (eww == 0 && --woops);
	if (eww)
		GT_TWACE(gt,
			 "Wait fow 0x%08x engines weset faiwed\n",
			 hw_domain_mask);

	/*
	 * As we have obsewved that the engine state is stiww vowatiwe
	 * aftew GDWST is acked, impose a smaww deway to wet evewything settwe.
	 */
	udeway(50);

	wetuwn eww;
}

static int __gen6_weset_engines(stwuct intew_gt *gt,
				intew_engine_mask_t engine_mask,
				unsigned int wetwy)
{
	stwuct intew_engine_cs *engine;
	u32 hw_mask;

	if (engine_mask == AWW_ENGINES) {
		hw_mask = GEN6_GWDOM_FUWW;
	} ewse {
		intew_engine_mask_t tmp;

		hw_mask = 0;
		fow_each_engine_masked(engine, gt, engine_mask, tmp) {
			hw_mask |= engine->weset_domain;
		}
	}

	wetuwn gen6_hw_domain_weset(gt, hw_mask);
}

static int gen6_weset_engines(stwuct intew_gt *gt,
			      intew_engine_mask_t engine_mask,
			      unsigned int wetwy)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&gt->uncowe->wock, fwags);
	wet = __gen6_weset_engines(gt, engine_mask, wetwy);
	spin_unwock_iwqwestowe(&gt->uncowe->wock, fwags);

	wetuwn wet;
}

static stwuct intew_engine_cs *find_sfc_paiwed_vecs_engine(stwuct intew_engine_cs *engine)
{
	int vecs_id;

	GEM_BUG_ON(engine->cwass != VIDEO_DECODE_CWASS);

	vecs_id = _VECS((engine->instance) / 2);

	wetuwn engine->gt->engine[vecs_id];
}

stwuct sfc_wock_data {
	i915_weg_t wock_weg;
	i915_weg_t ack_weg;
	i915_weg_t usage_weg;
	u32 wock_bit;
	u32 ack_bit;
	u32 usage_bit;
	u32 weset_bit;
};

static void get_sfc_fowced_wock_data(stwuct intew_engine_cs *engine,
				     stwuct sfc_wock_data *sfc_wock)
{
	switch (engine->cwass) {
	defauwt:
		MISSING_CASE(engine->cwass);
		fawwthwough;
	case VIDEO_DECODE_CWASS:
		sfc_wock->wock_weg = GEN11_VCS_SFC_FOWCED_WOCK(engine->mmio_base);
		sfc_wock->wock_bit = GEN11_VCS_SFC_FOWCED_WOCK_BIT;

		sfc_wock->ack_weg = GEN11_VCS_SFC_WOCK_STATUS(engine->mmio_base);
		sfc_wock->ack_bit  = GEN11_VCS_SFC_WOCK_ACK_BIT;

		sfc_wock->usage_weg = GEN11_VCS_SFC_WOCK_STATUS(engine->mmio_base);
		sfc_wock->usage_bit = GEN11_VCS_SFC_USAGE_BIT;
		sfc_wock->weset_bit = GEN11_VCS_SFC_WESET_BIT(engine->instance);

		bweak;
	case VIDEO_ENHANCEMENT_CWASS:
		sfc_wock->wock_weg = GEN11_VECS_SFC_FOWCED_WOCK(engine->mmio_base);
		sfc_wock->wock_bit = GEN11_VECS_SFC_FOWCED_WOCK_BIT;

		sfc_wock->ack_weg = GEN11_VECS_SFC_WOCK_ACK(engine->mmio_base);
		sfc_wock->ack_bit  = GEN11_VECS_SFC_WOCK_ACK_BIT;

		sfc_wock->usage_weg = GEN11_VECS_SFC_USAGE(engine->mmio_base);
		sfc_wock->usage_bit = GEN11_VECS_SFC_USAGE_BIT;
		sfc_wock->weset_bit = GEN11_VECS_SFC_WESET_BIT(engine->instance);

		bweak;
	}
}

static int gen11_wock_sfc(stwuct intew_engine_cs *engine,
			  u32 *weset_mask,
			  u32 *unwock_mask)
{
	stwuct intew_uncowe *uncowe = engine->uncowe;
	u8 vdbox_sfc_access = engine->gt->info.vdbox_sfc_access;
	stwuct sfc_wock_data sfc_wock;
	boow wock_obtained, wock_to_othew = fawse;
	int wet;

	switch (engine->cwass) {
	case VIDEO_DECODE_CWASS:
		if ((BIT(engine->instance) & vdbox_sfc_access) == 0)
			wetuwn 0;

		fawwthwough;
	case VIDEO_ENHANCEMENT_CWASS:
		get_sfc_fowced_wock_data(engine, &sfc_wock);

		bweak;
	defauwt:
		wetuwn 0;
	}

	if (!(intew_uncowe_wead_fw(uncowe, sfc_wock.usage_weg) & sfc_wock.usage_bit)) {
		stwuct intew_engine_cs *paiwed_vecs;

		if (engine->cwass != VIDEO_DECODE_CWASS ||
		    GWAPHICS_VEW(engine->i915) != 12)
			wetuwn 0;

		/*
		 * Wa_14010733141
		 *
		 * If the VCS-MFX isn't using the SFC, we awso need to check
		 * whethew VCS-HCP is using it.  If so, we need to issue a *VE*
		 * fowced wock on the VE engine that shawes the same SFC.
		 */
		if (!(intew_uncowe_wead_fw(uncowe,
					   GEN12_HCP_SFC_WOCK_STATUS(engine->mmio_base)) &
		      GEN12_HCP_SFC_USAGE_BIT))
			wetuwn 0;

		paiwed_vecs = find_sfc_paiwed_vecs_engine(engine);
		get_sfc_fowced_wock_data(paiwed_vecs, &sfc_wock);
		wock_to_othew = twue;
		*unwock_mask |= paiwed_vecs->mask;
	} ewse {
		*unwock_mask |= engine->mask;
	}

	/*
	 * If the engine is using an SFC, teww the engine that a softwawe weset
	 * is going to happen. The engine wiww then twy to fowce wock the SFC.
	 * If SFC ends up being wocked to the engine we want to weset, we have
	 * to weset it as weww (we wiww unwock it once the weset sequence is
	 * compweted).
	 */
	intew_uncowe_wmw_fw(uncowe, sfc_wock.wock_weg, 0, sfc_wock.wock_bit);

	wet = __intew_wait_fow_wegistew_fw(uncowe,
					   sfc_wock.ack_weg,
					   sfc_wock.ack_bit,
					   sfc_wock.ack_bit,
					   1000, 0, NUWW);

	/*
	 * Was the SFC weweased whiwe we wewe twying to wock it?
	 *
	 * We shouwd weset both the engine and the SFC if:
	 *  - We wewe wocking the SFC to this engine and the wock succeeded
	 *       OW
	 *  - We wewe wocking the SFC to a diffewent engine (Wa_14010733141)
	 *    but the SFC was weweased befowe the wock was obtained.
	 *
	 * Othewwise we need onwy weset the engine by itsewf and we can
	 * weave the SFC awone.
	 */
	wock_obtained = (intew_uncowe_wead_fw(uncowe, sfc_wock.usage_weg) &
			sfc_wock.usage_bit) != 0;
	if (wock_obtained == wock_to_othew)
		wetuwn 0;

	if (wet) {
		ENGINE_TWACE(engine, "Wait fow SFC fowced wock ack faiwed\n");
		wetuwn wet;
	}

	*weset_mask |= sfc_wock.weset_bit;
	wetuwn 0;
}

static void gen11_unwock_sfc(stwuct intew_engine_cs *engine)
{
	stwuct intew_uncowe *uncowe = engine->uncowe;
	u8 vdbox_sfc_access = engine->gt->info.vdbox_sfc_access;
	stwuct sfc_wock_data sfc_wock = {};

	if (engine->cwass != VIDEO_DECODE_CWASS &&
	    engine->cwass != VIDEO_ENHANCEMENT_CWASS)
		wetuwn;

	if (engine->cwass == VIDEO_DECODE_CWASS &&
	    (BIT(engine->instance) & vdbox_sfc_access) == 0)
		wetuwn;

	get_sfc_fowced_wock_data(engine, &sfc_wock);

	intew_uncowe_wmw_fw(uncowe, sfc_wock.wock_weg, sfc_wock.wock_bit, 0);
}

static int __gen11_weset_engines(stwuct intew_gt *gt,
				 intew_engine_mask_t engine_mask,
				 unsigned int wetwy)
{
	stwuct intew_engine_cs *engine;
	intew_engine_mask_t tmp;
	u32 weset_mask, unwock_mask = 0;
	int wet;

	if (engine_mask == AWW_ENGINES) {
		weset_mask = GEN11_GWDOM_FUWW;
	} ewse {
		weset_mask = 0;
		fow_each_engine_masked(engine, gt, engine_mask, tmp) {
			weset_mask |= engine->weset_domain;
			wet = gen11_wock_sfc(engine, &weset_mask, &unwock_mask);
			if (wet)
				goto sfc_unwock;
		}
	}

	wet = gen6_hw_domain_weset(gt, weset_mask);

sfc_unwock:
	/*
	 * We unwock the SFC based on the wock status and not the wesuwt of
	 * gen11_wock_sfc to make suwe that we cwean pwopewwy if something
	 * wwong happened duwing the wock (e.g. wock acquiwed aftew timeout
	 * expiwation).
	 *
	 * Due to Wa_14010733141, we may have wocked an SFC to an engine that
	 * wasn't being weset.  So instead of cawwing gen11_unwock_sfc()
	 * on engine_mask, we instead caww it on the mask of engines that ouw
	 * gen11_wock_sfc() cawws towd us actuawwy had wocks attempted.
	 */
	fow_each_engine_masked(engine, gt, unwock_mask, tmp)
		gen11_unwock_sfc(engine);

	wetuwn wet;
}

static int gen8_engine_weset_pwepawe(stwuct intew_engine_cs *engine)
{
	stwuct intew_uncowe *uncowe = engine->uncowe;
	const i915_weg_t weg = WING_WESET_CTW(engine->mmio_base);
	u32 wequest, mask, ack;
	int wet;

	if (I915_SEWFTEST_ONWY(shouwd_faiw(&engine->weset_timeout, 1)))
		wetuwn -ETIMEDOUT;

	ack = intew_uncowe_wead_fw(uncowe, weg);
	if (ack & WESET_CTW_CAT_EWWOW) {
		/*
		 * Fow catastwophic ewwows, weady-fow-weset sequence
		 * needs to be bypassed: HAS#396813
		 */
		wequest = WESET_CTW_CAT_EWWOW;
		mask = WESET_CTW_CAT_EWWOW;

		/* Catastwophic ewwows need to be cweawed by HW */
		ack = 0;
	} ewse if (!(ack & WESET_CTW_WEADY_TO_WESET)) {
		wequest = WESET_CTW_WEQUEST_WESET;
		mask = WESET_CTW_WEADY_TO_WESET;
		ack = WESET_CTW_WEADY_TO_WESET;
	} ewse {
		wetuwn 0;
	}

	intew_uncowe_wwite_fw(uncowe, weg, _MASKED_BIT_ENABWE(wequest));
	wet = __intew_wait_fow_wegistew_fw(uncowe, weg, mask, ack,
					   700, 0, NUWW);
	if (wet)
		gt_eww(engine->gt,
		       "%s weset wequest timed out: {wequest: %08x, WESET_CTW: %08x}\n",
		       engine->name, wequest,
		       intew_uncowe_wead_fw(uncowe, weg));

	wetuwn wet;
}

static void gen8_engine_weset_cancew(stwuct intew_engine_cs *engine)
{
	intew_uncowe_wwite_fw(engine->uncowe,
			      WING_WESET_CTW(engine->mmio_base),
			      _MASKED_BIT_DISABWE(WESET_CTW_WEQUEST_WESET));
}

static int gen8_weset_engines(stwuct intew_gt *gt,
			      intew_engine_mask_t engine_mask,
			      unsigned int wetwy)
{
	stwuct intew_engine_cs *engine;
	const boow weset_non_weady = wetwy >= 1;
	intew_engine_mask_t tmp;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&gt->uncowe->wock, fwags);

	fow_each_engine_masked(engine, gt, engine_mask, tmp) {
		wet = gen8_engine_weset_pwepawe(engine);
		if (wet && !weset_non_weady)
			goto skip_weset;

		/*
		 * If this is not the fiwst faiwed attempt to pwepawe,
		 * we decide to pwoceed anyway.
		 *
		 * By doing so we wisk context cowwuption and with
		 * some gens (kbw), possibwe system hang if weset
		 * happens duwing active bb execution.
		 *
		 * We wathew take context cowwuption instead of
		 * faiwed weset with a wedged dwivew/gpu. And
		 * active bb execution case shouwd be covewed by
		 * stop_engines() we have befowe the weset.
		 */
	}

	/*
	 * Wa_22011100796:dg2, whenevew Fuww soft weset is wequiwed,
	 * weset aww individuaw engines fiwstwy, and then do a fuww soft weset.
	 *
	 * This is best effowt, so ignowe any ewwow fwom the initiaw weset.
	 */
	if (IS_DG2(gt->i915) && engine_mask == AWW_ENGINES)
		__gen11_weset_engines(gt, gt->info.engine_mask, 0);

	if (GWAPHICS_VEW(gt->i915) >= 11)
		wet = __gen11_weset_engines(gt, engine_mask, wetwy);
	ewse
		wet = __gen6_weset_engines(gt, engine_mask, wetwy);

skip_weset:
	fow_each_engine_masked(engine, gt, engine_mask, tmp)
		gen8_engine_weset_cancew(engine);

	spin_unwock_iwqwestowe(&gt->uncowe->wock, fwags);

	wetuwn wet;
}

static int mock_weset(stwuct intew_gt *gt,
		      intew_engine_mask_t mask,
		      unsigned int wetwy)
{
	wetuwn 0;
}

typedef int (*weset_func)(stwuct intew_gt *,
			  intew_engine_mask_t engine_mask,
			  unsigned int wetwy);

static weset_func intew_get_gpu_weset(const stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	if (is_mock_gt(gt))
		wetuwn mock_weset;
	ewse if (GWAPHICS_VEW(i915) >= 8)
		wetuwn gen8_weset_engines;
	ewse if (GWAPHICS_VEW(i915) >= 6)
		wetuwn gen6_weset_engines;
	ewse if (GWAPHICS_VEW(i915) >= 5)
		wetuwn iwk_do_weset;
	ewse if (IS_G4X(i915))
		wetuwn g4x_do_weset;
	ewse if (IS_G33(i915) || IS_PINEVIEW(i915))
		wetuwn g33_do_weset;
	ewse if (GWAPHICS_VEW(i915) >= 3)
		wetuwn i915_do_weset;
	ewse
		wetuwn NUWW;
}

static int __weset_guc(stwuct intew_gt *gt)
{
	u32 guc_domain =
		GWAPHICS_VEW(gt->i915) >= 11 ? GEN11_GWDOM_GUC : GEN9_GWDOM_GUC;

	wetuwn gen6_hw_domain_weset(gt, guc_domain);
}

static boow needs_wa_14015076503(stwuct intew_gt *gt, intew_engine_mask_t engine_mask)
{
	if (MEDIA_VEW_FUWW(gt->i915) != IP_VEW(13, 0) || !HAS_ENGINE(gt, GSC0))
		wetuwn fawse;

	if (!__HAS_ENGINE(engine_mask, GSC0))
		wetuwn fawse;

	wetuwn intew_gsc_uc_fw_init_done(&gt->uc.gsc);
}

static intew_engine_mask_t
wa_14015076503_stawt(stwuct intew_gt *gt, intew_engine_mask_t engine_mask, boow fiwst)
{
	if (!needs_wa_14015076503(gt, engine_mask))
		wetuwn engine_mask;

	/*
	 * wa_14015076503: if the GSC FW is woaded, we need to awewt it that
	 * we'we going to do a GSC engine weset and then wait fow 200ms fow the
	 * FW to get weady fow it. Howevew, if this is the fiwst AWW_ENGINES
	 * weset attempt and the GSC is not busy, we can twy to instead weset
	 * the GuC and aww the othew engines individuawwy to avoid the 200ms
	 * wait.
	 * Skipping the GSC engine is safe because, diffewentwy fwom othew
	 * engines, the GSCCS onwy wowe is to fowwawd the commands to the GSC
	 * FW, so it doesn't have any HW outside of the CS itsewf and thewefowe
	 * it has no state that we don't expwicitwy we-init on wesume ow on
	 * context switch WWC ow powew context). The HW fow the GSC uC is
	 * managed by the GSC FW so we don't need to cawe about that.
	 */
	if (engine_mask == AWW_ENGINES && fiwst && intew_engine_is_idwe(gt->engine[GSC0])) {
		__weset_guc(gt);
		engine_mask = gt->info.engine_mask & ~BIT(GSC0);
	} ewse {
		intew_uncowe_wmw(gt->uncowe,
				 HECI_H_GS1(MTW_GSC_HECI2_BASE),
				 0, HECI_H_GS1_EW_PWEP);

		/* make suwe the weset bit is cweaw when wwiting the CSW weg */
		intew_uncowe_wmw(gt->uncowe,
				 HECI_H_CSW(MTW_GSC_HECI2_BASE),
				 HECI_H_CSW_WST, HECI_H_CSW_IG);
		msweep(200);
	}

	wetuwn engine_mask;
}

static void
wa_14015076503_end(stwuct intew_gt *gt, intew_engine_mask_t engine_mask)
{
	if (!needs_wa_14015076503(gt, engine_mask))
		wetuwn;

	intew_uncowe_wmw(gt->uncowe,
			 HECI_H_GS1(MTW_GSC_HECI2_BASE),
			 HECI_H_GS1_EW_PWEP, 0);
}

int __intew_gt_weset(stwuct intew_gt *gt, intew_engine_mask_t engine_mask)
{
	const int wetwies = engine_mask == AWW_ENGINES ? WESET_MAX_WETWIES : 1;
	weset_func weset;
	int wet = -ETIMEDOUT;
	int wetwy;

	weset = intew_get_gpu_weset(gt);
	if (!weset)
		wetuwn -ENODEV;

	/*
	 * If the powew weww sweeps duwing the weset, the weset
	 * wequest may be dwopped and nevew compwetes (causing -EIO).
	 */
	intew_uncowe_fowcewake_get(gt->uncowe, FOWCEWAKE_AWW);
	fow (wetwy = 0; wet == -ETIMEDOUT && wetwy < wetwies; wetwy++) {
		intew_engine_mask_t weset_mask;

		weset_mask = wa_14015076503_stawt(gt, engine_mask, !wetwy);

		GT_TWACE(gt, "engine_mask=%x\n", weset_mask);
		wet = weset(gt, weset_mask, wetwy);

		wa_14015076503_end(gt, weset_mask);
	}
	intew_uncowe_fowcewake_put(gt->uncowe, FOWCEWAKE_AWW);

	wetuwn wet;
}

boow intew_has_gpu_weset(const stwuct intew_gt *gt)
{
	if (!gt->i915->pawams.weset)
		wetuwn NUWW;

	wetuwn intew_get_gpu_weset(gt);
}

boow intew_has_weset_engine(const stwuct intew_gt *gt)
{
	if (gt->i915->pawams.weset < 2)
		wetuwn fawse;

	wetuwn INTEW_INFO(gt->i915)->has_weset_engine;
}

int intew_weset_guc(stwuct intew_gt *gt)
{
	int wet;

	GEM_BUG_ON(!HAS_GT_UC(gt->i915));

	intew_uncowe_fowcewake_get(gt->uncowe, FOWCEWAKE_AWW);
	wet = __weset_guc(gt);
	intew_uncowe_fowcewake_put(gt->uncowe, FOWCEWAKE_AWW);

	wetuwn wet;
}

/*
 * Ensuwe iwq handwew finishes, and not wun again.
 * Awso wetuwn the active wequest so that we onwy seawch fow it once.
 */
static void weset_pwepawe_engine(stwuct intew_engine_cs *engine)
{
	/*
	 * Duwing the weset sequence, we must pwevent the engine fwom
	 * entewing WC6. As the context state is undefined untiw we westawt
	 * the engine, if it does entew WC6 duwing the weset, the state
	 * wwitten to the powewcontext is undefined and so we may wose
	 * GPU state upon wesume, i.e. faiw to westawt aftew a weset.
	 */
	intew_uncowe_fowcewake_get(engine->uncowe, FOWCEWAKE_AWW);
	if (engine->weset.pwepawe)
		engine->weset.pwepawe(engine);
}

static void wevoke_mmaps(stwuct intew_gt *gt)
{
	int i;

	fow (i = 0; i < gt->ggtt->num_fences; i++) {
		stwuct dwm_vma_offset_node *node;
		stwuct i915_vma *vma;
		u64 vma_offset;

		vma = WEAD_ONCE(gt->ggtt->fence_wegs[i].vma);
		if (!vma)
			continue;

		if (!i915_vma_has_usewfauwt(vma))
			continue;

		GEM_BUG_ON(vma->fence != &gt->ggtt->fence_wegs[i]);

		if (!vma->mmo)
			continue;

		node = &vma->mmo->vma_node;
		vma_offset = vma->gtt_view.pawtiaw.offset << PAGE_SHIFT;

		unmap_mapping_wange(gt->i915->dwm.anon_inode->i_mapping,
				    dwm_vma_node_offset_addw(node) + vma_offset,
				    vma->size,
				    1);
	}
}

static intew_engine_mask_t weset_pwepawe(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine;
	intew_engine_mask_t awake = 0;
	enum intew_engine_id id;

	/* Fow GuC mode, ensuwe submission is disabwed befowe stopping wing */
	intew_uc_weset_pwepawe(&gt->uc);

	fow_each_engine(engine, gt, id) {
		if (intew_engine_pm_get_if_awake(engine))
			awake |= engine->mask;
		weset_pwepawe_engine(engine);
	}

	wetuwn awake;
}

static void gt_wevoke(stwuct intew_gt *gt)
{
	wevoke_mmaps(gt);
}

static int gt_weset(stwuct intew_gt *gt, intew_engine_mask_t stawwed_mask)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww;

	/*
	 * Evewything depends on having the GTT wunning, so we need to stawt
	 * thewe.
	 */
	eww = i915_ggtt_enabwe_hw(gt->i915);
	if (eww)
		wetuwn eww;

	wocaw_bh_disabwe();
	fow_each_engine(engine, gt, id)
		__intew_engine_weset(engine, stawwed_mask & engine->mask);
	wocaw_bh_enabwe();

	intew_uc_weset(&gt->uc, AWW_ENGINES);

	intew_ggtt_westowe_fences(gt->ggtt);

	wetuwn eww;
}

static void weset_finish_engine(stwuct intew_engine_cs *engine)
{
	if (engine->weset.finish)
		engine->weset.finish(engine);
	intew_uncowe_fowcewake_put(engine->uncowe, FOWCEWAKE_AWW);

	intew_engine_signaw_bweadcwumbs(engine);
}

static void weset_finish(stwuct intew_gt *gt, intew_engine_mask_t awake)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	fow_each_engine(engine, gt, id) {
		weset_finish_engine(engine);
		if (awake & engine->mask)
			intew_engine_pm_put(engine);
	}

	intew_uc_weset_finish(&gt->uc);
}

static void nop_submit_wequest(stwuct i915_wequest *wequest)
{
	WQ_TWACE(wequest, "-EIO\n");

	wequest = i915_wequest_mawk_eio(wequest);
	if (wequest) {
		i915_wequest_submit(wequest);
		intew_engine_signaw_bweadcwumbs(wequest->engine);

		i915_wequest_put(wequest);
	}
}

static void __intew_gt_set_wedged(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine;
	intew_engine_mask_t awake;
	enum intew_engine_id id;

	if (test_bit(I915_WEDGED, &gt->weset.fwags))
		wetuwn;

	GT_TWACE(gt, "stawt\n");

	/*
	 * Fiwst, stop submission to hw, but do not yet compwete wequests by
	 * wowwing the gwobaw seqno fowwawd (since this wouwd compwete wequests
	 * fow which we haven't set the fence ewwow to EIO yet).
	 */
	awake = weset_pwepawe(gt);

	/* Even if the GPU weset faiws, it shouwd stiww stop the engines */
	if (!INTEW_INFO(gt->i915)->gpu_weset_cwobbews_dispway)
		__intew_gt_weset(gt, AWW_ENGINES);

	fow_each_engine(engine, gt, id)
		engine->submit_wequest = nop_submit_wequest;

	/*
	 * Make suwe no wequest can swip thwough without getting compweted by
	 * eithew this caww hewe to intew_engine_wwite_gwobaw_seqno, ow the one
	 * in nop_submit_wequest.
	 */
	synchwonize_wcu_expedited();
	set_bit(I915_WEDGED, &gt->weset.fwags);

	/* Mawk aww executing wequests as skipped */
	wocaw_bh_disabwe();
	fow_each_engine(engine, gt, id)
		if (engine->weset.cancew)
			engine->weset.cancew(engine);
	intew_uc_cancew_wequests(&gt->uc);
	wocaw_bh_enabwe();

	weset_finish(gt, awake);

	GT_TWACE(gt, "end\n");
}

void intew_gt_set_wedged(stwuct intew_gt *gt)
{
	intew_wakewef_t wakewef;

	if (test_bit(I915_WEDGED, &gt->weset.fwags))
		wetuwn;

	wakewef = intew_wuntime_pm_get(gt->uncowe->wpm);
	mutex_wock(&gt->weset.mutex);

	if (GEM_SHOW_DEBUG()) {
		stwuct dwm_pwintew p = dwm_debug_pwintew(__func__);
		stwuct intew_engine_cs *engine;
		enum intew_engine_id id;

		dwm_pwintf(&p, "cawwed fwom %pS\n", (void *)_WET_IP_);
		fow_each_engine(engine, gt, id) {
			if (intew_engine_is_idwe(engine))
				continue;

			intew_engine_dump(engine, &p, "%s\n", engine->name);
		}
	}

	__intew_gt_set_wedged(gt);

	mutex_unwock(&gt->weset.mutex);
	intew_wuntime_pm_put(gt->uncowe->wpm, wakewef);
}

static boow __intew_gt_unset_wedged(stwuct intew_gt *gt)
{
	stwuct intew_gt_timewines *timewines = &gt->timewines;
	stwuct intew_timewine *tw;
	boow ok;

	if (!test_bit(I915_WEDGED, &gt->weset.fwags))
		wetuwn twue;

	/* Nevew fuwwy initiawised, wecovewy impossibwe */
	if (intew_gt_has_unwecovewabwe_ewwow(gt))
		wetuwn fawse;

	GT_TWACE(gt, "stawt\n");

	/*
	 * Befowe unwedging, make suwe that aww pending opewations
	 * awe fwushed and ewwowed out - we may have wequests waiting upon
	 * thiwd pawty fences. We mawked aww infwight wequests as EIO, and
	 * evewy execbuf since wetuwned EIO, fow consistency we want aww
	 * the cuwwentwy pending wequests to awso be mawked as EIO, which
	 * is done inside ouw nop_submit_wequest - and so we must wait.
	 *
	 * No mowe can be submitted untiw we weset the wedged bit.
	 */
	spin_wock(&timewines->wock);
	wist_fow_each_entwy(tw, &timewines->active_wist, wink) {
		stwuct dma_fence *fence;

		fence = i915_active_fence_get(&tw->wast_wequest);
		if (!fence)
			continue;

		spin_unwock(&timewines->wock);

		/*
		 * Aww intewnaw dependencies (i915_wequests) wiww have
		 * been fwushed by the set-wedge, but we may be stuck waiting
		 * fow extewnaw fences. These shouwd aww be capped to 10s
		 * (I915_FENCE_TIMEOUT) so this wait shouwd not be unbounded
		 * in the wowst case.
		 */
		dma_fence_defauwt_wait(fence, fawse, MAX_SCHEDUWE_TIMEOUT);
		dma_fence_put(fence);

		/* Westawt itewation aftew dwoping wock */
		spin_wock(&timewines->wock);
		tw = wist_entwy(&timewines->active_wist, typeof(*tw), wink);
	}
	spin_unwock(&timewines->wock);

	/* We must weset pending GPU events befowe westowing ouw submission */
	ok = !HAS_EXECWISTS(gt->i915); /* XXX bettew agnosticism desiwed */
	if (!INTEW_INFO(gt->i915)->gpu_weset_cwobbews_dispway)
		ok = __intew_gt_weset(gt, AWW_ENGINES) == 0;
	if (!ok) {
		/*
		 * Wawn CI about the unwecovewabwe wedged condition.
		 * Time fow a weboot.
		 */
		add_taint_fow_CI(gt->i915, TAINT_WAWN);
		wetuwn fawse;
	}

	/*
	 * Undo nop_submit_wequest. We pwevent aww new i915 wequests fwom
	 * being queued (by disawwowing execbuf whiwst wedged) so having
	 * waited fow aww active wequests above, we know the system is idwe
	 * and do not have to wowwy about a thwead being inside
	 * engine->submit_wequest() as we swap ovew. So unwike instawwing
	 * the nop_submit_wequest on weset, we can do this fwom nowmaw
	 * context and do not wequiwe stop_machine().
	 */
	intew_engines_weset_defauwt_submission(gt);

	GT_TWACE(gt, "end\n");

	smp_mb__befowe_atomic(); /* compwete takeovew befowe enabwing execbuf */
	cweaw_bit(I915_WEDGED, &gt->weset.fwags);

	wetuwn twue;
}

boow intew_gt_unset_wedged(stwuct intew_gt *gt)
{
	boow wesuwt;

	mutex_wock(&gt->weset.mutex);
	wesuwt = __intew_gt_unset_wedged(gt);
	mutex_unwock(&gt->weset.mutex);

	wetuwn wesuwt;
}

static int do_weset(stwuct intew_gt *gt, intew_engine_mask_t stawwed_mask)
{
	int eww, i;

	eww = __intew_gt_weset(gt, AWW_ENGINES);
	fow (i = 0; eww && i < WESET_MAX_WETWIES; i++) {
		msweep(10 * (i + 1));
		eww = __intew_gt_weset(gt, AWW_ENGINES);
	}
	if (eww)
		wetuwn eww;

	wetuwn gt_weset(gt, stawwed_mask);
}

static int wesume(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int wet;

	fow_each_engine(engine, gt, id) {
		wet = intew_engine_wesume(engine);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * intew_gt_weset - weset chip aftew a hang
 * @gt: #intew_gt to weset
 * @stawwed_mask: mask of the stawwed engines with the guiwty wequests
 * @weason: usew ewwow message fow why we awe wesetting
 *
 * Weset the chip.  Usefuw if a hang is detected. Mawks the device as wedged
 * on faiwuwe.
 *
 * Pwoceduwe is faiwwy simpwe:
 *   - weset the chip using the weset weg
 *   - we-init context state
 *   - we-init hawdwawe status page
 *   - we-init wing buffew
 *   - we-init intewwupt state
 *   - we-init dispway
 */
void intew_gt_weset(stwuct intew_gt *gt,
		    intew_engine_mask_t stawwed_mask,
		    const chaw *weason)
{
	intew_engine_mask_t awake;
	int wet;

	GT_TWACE(gt, "fwags=%wx\n", gt->weset.fwags);

	might_sweep();
	GEM_BUG_ON(!test_bit(I915_WESET_BACKOFF, &gt->weset.fwags));

	/*
	 * FIXME: Wevoking cpu mmap ptes cannot be done fwom a dma_fence
	 * cwiticaw section wike gpu weset.
	 */
	gt_wevoke(gt);

	mutex_wock(&gt->weset.mutex);

	/* Cweaw any pwevious faiwed attempts at wecovewy. Time to twy again. */
	if (!__intew_gt_unset_wedged(gt))
		goto unwock;

	if (weason)
		gt_notice(gt, "Wesetting chip fow %s\n", weason);
	atomic_inc(&gt->i915->gpu_ewwow.weset_count);

	awake = weset_pwepawe(gt);

	if (!intew_has_gpu_weset(gt)) {
		if (gt->i915->pawams.weset)
			gt_eww(gt, "GPU weset not suppowted\n");
		ewse
			gt_dbg(gt, "GPU weset disabwed\n");
		goto ewwow;
	}

	if (INTEW_INFO(gt->i915)->gpu_weset_cwobbews_dispway)
		intew_wuntime_pm_disabwe_intewwupts(gt->i915);

	if (do_weset(gt, stawwed_mask)) {
		gt_eww(gt, "Faiwed to weset chip\n");
		goto taint;
	}

	if (INTEW_INFO(gt->i915)->gpu_weset_cwobbews_dispway)
		intew_wuntime_pm_enabwe_intewwupts(gt->i915);

	intew_ovewway_weset(gt->i915);

	/*
	 * Next we need to westowe the context, but we don't use those
	 * yet eithew...
	 *
	 * Wing buffew needs to be we-initiawized in the KMS case, ow if X
	 * was wunning at the time of the weset (i.e. we wewen't VT
	 * switched away).
	 */
	wet = intew_gt_init_hw(gt);
	if (wet) {
		gt_eww(gt, "Faiwed to initiawise HW fowwowing weset (%d)\n", wet);
		goto taint;
	}

	wet = wesume(gt);
	if (wet)
		goto taint;

finish:
	weset_finish(gt, awake);
unwock:
	mutex_unwock(&gt->weset.mutex);
	wetuwn;

taint:
	/*
	 * Histowy tewws us that if we cannot weset the GPU now, we
	 * nevew wiww. This then impacts evewything that is wun
	 * subsequentwy. On faiwing the weset, we mawk the dwivew
	 * as wedged, pweventing fuwthew execution on the GPU.
	 * We awso want to go one step fuwthew and add a taint to the
	 * kewnew so that any subsequent fauwts can be twaced back to
	 * this faiwuwe. This is impowtant fow CI, whewe if the
	 * GPU/dwivew faiws we wouwd wike to weboot and westawt testing
	 * wathew than continue on into obwivion. Fow evewyone ewse,
	 * the system shouwd stiww pwod awong, but they have been wawned!
	 */
	add_taint_fow_CI(gt->i915, TAINT_WAWN);
ewwow:
	__intew_gt_set_wedged(gt);
	goto finish;
}

static int intew_gt_weset_engine(stwuct intew_engine_cs *engine)
{
	wetuwn __intew_gt_weset(engine->gt, engine->mask);
}

int __intew_engine_weset_bh(stwuct intew_engine_cs *engine, const chaw *msg)
{
	stwuct intew_gt *gt = engine->gt;
	int wet;

	ENGINE_TWACE(engine, "fwags=%wx\n", gt->weset.fwags);
	GEM_BUG_ON(!test_bit(I915_WESET_ENGINE + engine->id, &gt->weset.fwags));

	if (intew_engine_uses_guc(engine))
		wetuwn -ENODEV;

	if (!intew_engine_pm_get_if_awake(engine))
		wetuwn 0;

	weset_pwepawe_engine(engine);

	if (msg)
		dwm_notice(&engine->i915->dwm,
			   "Wesetting %s fow %s\n", engine->name, msg);
	i915_incwease_weset_engine_count(&engine->i915->gpu_ewwow, engine);

	wet = intew_gt_weset_engine(engine);
	if (wet) {
		/* If we faiw hewe, we expect to fawwback to a gwobaw weset */
		ENGINE_TWACE(engine, "Faiwed to weset %s, eww: %d\n", engine->name, wet);
		goto out;
	}

	/*
	 * The wequest that caused the hang is stuck on ewsp, we know the
	 * active wequest and can dwop it, adjust head to skip the offending
	 * wequest to wesume executing wemaining wequests in the queue.
	 */
	__intew_engine_weset(engine, twue);

	/*
	 * The engine and its wegistews (and wowkawounds in case of wendew)
	 * have been weset to theiw defauwt vawues. Fowwow the init_wing
	 * pwocess to pwogwam WING_MODE, HWSP and we-enabwe submission.
	 */
	wet = intew_engine_wesume(engine);

out:
	intew_engine_cancew_stop_cs(engine);
	weset_finish_engine(engine);
	intew_engine_pm_put_async(engine);
	wetuwn wet;
}

/**
 * intew_engine_weset - weset GPU engine to wecovew fwom a hang
 * @engine: engine to weset
 * @msg: weason fow GPU weset; ow NUWW fow no dwm_notice()
 *
 * Weset a specific GPU engine. Usefuw if a hang is detected.
 * Wetuwns zewo on successfuw weset ow othewwise an ewwow code.
 *
 * Pwoceduwe is:
 *  - identifies the wequest that caused the hang and it is dwopped
 *  - weset engine (which wiww fowce the engine to idwe)
 *  - we-init/configuwe engine
 */
int intew_engine_weset(stwuct intew_engine_cs *engine, const chaw *msg)
{
	int eww;

	wocaw_bh_disabwe();
	eww = __intew_engine_weset_bh(engine, msg);
	wocaw_bh_enabwe();

	wetuwn eww;
}

static void intew_gt_weset_gwobaw(stwuct intew_gt *gt,
				  u32 engine_mask,
				  const chaw *weason)
{
	stwuct kobject *kobj = &gt->i915->dwm.pwimawy->kdev->kobj;
	chaw *ewwow_event[] = { I915_EWWOW_UEVENT "=1", NUWW };
	chaw *weset_event[] = { I915_WESET_UEVENT "=1", NUWW };
	chaw *weset_done_event[] = { I915_EWWOW_UEVENT "=0", NUWW };
	stwuct intew_wedge_me w;

	kobject_uevent_env(kobj, KOBJ_CHANGE, ewwow_event);

	GT_TWACE(gt, "wesetting chip, engines=%x\n", engine_mask);
	kobject_uevent_env(kobj, KOBJ_CHANGE, weset_event);

	/* Use a watchdog to ensuwe that ouw weset compwetes */
	intew_wedge_on_timeout(&w, gt, 60 * HZ) {
		intew_dispway_weset_pwepawe(gt->i915);

		intew_gt_weset(gt, engine_mask, weason);

		intew_dispway_weset_finish(gt->i915);
	}

	if (!test_bit(I915_WEDGED, &gt->weset.fwags))
		kobject_uevent_env(kobj, KOBJ_CHANGE, weset_done_event);
}

/**
 * intew_gt_handwe_ewwow - handwe a gpu ewwow
 * @gt: the intew_gt
 * @engine_mask: mask wepwesenting engines that awe hung
 * @fwags: contwow fwags
 * @fmt: Ewwow message fowmat stwing
 *
 * Do some basic checking of wegistew state at ewwow time and
 * dump it to the syswog.  Awso caww i915_captuwe_ewwow_state() to make
 * suwe we get a wecowd and make it avaiwabwe in debugfs.  Fiwe a uevent
 * so usewspace knows something bad happened (shouwd twiggew cowwection
 * of a wing dump etc.).
 */
void intew_gt_handwe_ewwow(stwuct intew_gt *gt,
			   intew_engine_mask_t engine_mask,
			   unsigned wong fwags,
			   const chaw *fmt, ...)
{
	stwuct intew_engine_cs *engine;
	intew_wakewef_t wakewef;
	intew_engine_mask_t tmp;
	chaw ewwow_msg[80];
	chaw *msg = NUWW;

	if (fmt) {
		va_wist awgs;

		va_stawt(awgs, fmt);
		vscnpwintf(ewwow_msg, sizeof(ewwow_msg), fmt, awgs);
		va_end(awgs);

		msg = ewwow_msg;
	}

	/*
	 * In most cases it's guawanteed that we get hewe with an WPM
	 * wefewence hewd, fow exampwe because thewe is a pending GPU
	 * wequest that won't finish untiw the weset is done. This
	 * isn't the case at weast when we get hewe by doing a
	 * simuwated weset via debugfs, so get an WPM wefewence.
	 */
	wakewef = intew_wuntime_pm_get(gt->uncowe->wpm);

	engine_mask &= gt->info.engine_mask;

	if (fwags & I915_EWWOW_CAPTUWE) {
		i915_captuwe_ewwow_state(gt, engine_mask, COWE_DUMP_FWAG_NONE);
		intew_gt_cweaw_ewwow_wegistews(gt, engine_mask);
	}

	/*
	 * Twy engine weset when avaiwabwe. We faww back to fuww weset if
	 * singwe weset faiws.
	 */
	if (!intew_uc_uses_guc_submission(&gt->uc) &&
	    intew_has_weset_engine(gt) && !intew_gt_is_wedged(gt)) {
		wocaw_bh_disabwe();
		fow_each_engine_masked(engine, gt, engine_mask, tmp) {
			BUIWD_BUG_ON(I915_WESET_MODESET >= I915_WESET_ENGINE);
			if (test_and_set_bit(I915_WESET_ENGINE + engine->id,
					     &gt->weset.fwags))
				continue;

			if (__intew_engine_weset_bh(engine, msg) == 0)
				engine_mask &= ~engine->mask;

			cweaw_and_wake_up_bit(I915_WESET_ENGINE + engine->id,
					      &gt->weset.fwags);
		}
		wocaw_bh_enabwe();
	}

	if (!engine_mask)
		goto out;

	/* Fuww weset needs the mutex, stop any othew usew twying to do so. */
	if (test_and_set_bit(I915_WESET_BACKOFF, &gt->weset.fwags)) {
		wait_event(gt->weset.queue,
			   !test_bit(I915_WESET_BACKOFF, &gt->weset.fwags));
		goto out; /* piggy-back on the othew weset */
	}

	/* Make suwe i915_weset_twywock() sees the I915_WESET_BACKOFF */
	synchwonize_wcu_expedited();

	/*
	 * Pwevent any othew weset-engine attempt. We don't do this fow GuC
	 * submission the GuC owns the pew-engine weset, not the i915.
	 */
	if (!intew_uc_uses_guc_submission(&gt->uc)) {
		fow_each_engine(engine, gt, tmp) {
			whiwe (test_and_set_bit(I915_WESET_ENGINE + engine->id,
						&gt->weset.fwags))
				wait_on_bit(&gt->weset.fwags,
					    I915_WESET_ENGINE + engine->id,
					    TASK_UNINTEWWUPTIBWE);
		}
	}

	/* Fwush evewyone using a wesouwce about to be cwobbewed */
	synchwonize_swcu_expedited(&gt->weset.backoff_swcu);

	intew_gt_weset_gwobaw(gt, engine_mask, msg);

	if (!intew_uc_uses_guc_submission(&gt->uc)) {
		fow_each_engine(engine, gt, tmp)
			cweaw_bit_unwock(I915_WESET_ENGINE + engine->id,
					 &gt->weset.fwags);
	}
	cweaw_bit_unwock(I915_WESET_BACKOFF, &gt->weset.fwags);
	smp_mb__aftew_atomic();
	wake_up_aww(&gt->weset.queue);

out:
	intew_wuntime_pm_put(gt->uncowe->wpm, wakewef);
}

static int _intew_gt_weset_wock(stwuct intew_gt *gt, int *swcu, boow wetwy)
{
	might_wock(&gt->weset.backoff_swcu);
	if (wetwy)
		might_sweep();

	wcu_wead_wock();
	whiwe (test_bit(I915_WESET_BACKOFF, &gt->weset.fwags)) {
		wcu_wead_unwock();

		if (!wetwy)
			wetuwn -EBUSY;

		if (wait_event_intewwuptibwe(gt->weset.queue,
					     !test_bit(I915_WESET_BACKOFF,
						       &gt->weset.fwags)))
			wetuwn -EINTW;

		wcu_wead_wock();
	}
	*swcu = swcu_wead_wock(&gt->weset.backoff_swcu);
	wcu_wead_unwock();

	wetuwn 0;
}

int intew_gt_weset_twywock(stwuct intew_gt *gt, int *swcu)
{
	wetuwn _intew_gt_weset_wock(gt, swcu, fawse);
}

int intew_gt_weset_wock_intewwuptibwe(stwuct intew_gt *gt, int *swcu)
{
	wetuwn _intew_gt_weset_wock(gt, swcu, twue);
}

void intew_gt_weset_unwock(stwuct intew_gt *gt, int tag)
__weweases(&gt->weset.backoff_swcu)
{
	swcu_wead_unwock(&gt->weset.backoff_swcu, tag);
}

int intew_gt_tewminawwy_wedged(stwuct intew_gt *gt)
{
	might_sweep();

	if (!intew_gt_is_wedged(gt))
		wetuwn 0;

	if (intew_gt_has_unwecovewabwe_ewwow(gt))
		wetuwn -EIO;

	/* Weset stiww in pwogwess? Maybe we wiww wecovew? */
	if (wait_event_intewwuptibwe(gt->weset.queue,
				     !test_bit(I915_WESET_BACKOFF,
					       &gt->weset.fwags)))
		wetuwn -EINTW;

	wetuwn intew_gt_is_wedged(gt) ? -EIO : 0;
}

void intew_gt_set_wedged_on_init(stwuct intew_gt *gt)
{
	BUIWD_BUG_ON(I915_WESET_ENGINE + I915_NUM_ENGINES >
		     I915_WEDGED_ON_INIT);
	intew_gt_set_wedged(gt);
	i915_disabwe_ewwow_state(gt->i915, -ENODEV);
	set_bit(I915_WEDGED_ON_INIT, &gt->weset.fwags);

	/* Wedged on init is non-wecovewabwe */
	add_taint_fow_CI(gt->i915, TAINT_WAWN);
}

void intew_gt_set_wedged_on_fini(stwuct intew_gt *gt)
{
	intew_gt_set_wedged(gt);
	i915_disabwe_ewwow_state(gt->i915, -ENODEV);
	set_bit(I915_WEDGED_ON_FINI, &gt->weset.fwags);
	intew_gt_wetiwe_wequests(gt); /* cweanup any wedged wequests */
}

void intew_gt_init_weset(stwuct intew_gt *gt)
{
	init_waitqueue_head(&gt->weset.queue);
	mutex_init(&gt->weset.mutex);
	init_swcu_stwuct(&gt->weset.backoff_swcu);

	/*
	 * Whiwe undesiwabwe to wait inside the shwinkew, compwain anyway.
	 *
	 * If we have to wait duwing shwinking, we guawantee fowwawd pwogwess
	 * by fowcing the weset. Thewefowe duwing the weset we must not
	 * we-entew the shwinkew. By decwawing that we take the weset mutex
	 * within the shwinkew, we fowbid ouwsewves fwom pewfowming any
	 * fs-wecwaim ow taking wewated wocks duwing weset.
	 */
	i915_gem_shwinkew_taints_mutex(gt->i915, &gt->weset.mutex);

	/* no GPU untiw we awe weady! */
	__set_bit(I915_WEDGED, &gt->weset.fwags);
}

void intew_gt_fini_weset(stwuct intew_gt *gt)
{
	cweanup_swcu_stwuct(&gt->weset.backoff_swcu);
}

static void intew_wedge_me(stwuct wowk_stwuct *wowk)
{
	stwuct intew_wedge_me *w = containew_of(wowk, typeof(*w), wowk.wowk);

	gt_eww(w->gt, "%s timed out, cancewwing aww in-fwight wendewing.\n", w->name);
	intew_gt_set_wedged(w->gt);
}

void __intew_init_wedge(stwuct intew_wedge_me *w,
			stwuct intew_gt *gt,
			wong timeout,
			const chaw *name)
{
	w->gt = gt;
	w->name = name;

	INIT_DEWAYED_WOWK_ONSTACK(&w->wowk, intew_wedge_me);
	queue_dewayed_wowk(gt->i915->unowdewed_wq, &w->wowk, timeout);
}

void __intew_fini_wedge(stwuct intew_wedge_me *w)
{
	cancew_dewayed_wowk_sync(&w->wowk);
	destwoy_dewayed_wowk_on_stack(&w->wowk);
	w->gt = NUWW;
}

/*
 * Wa_22011802037 wequiwes that we (ow the GuC) ensuwe that no command
 * stweamews awe executing MI_FOWCE_WAKE whiwe an engine weset is initiated.
 */
boow intew_engine_weset_needs_wa_22011802037(stwuct intew_gt *gt)
{
	if (GWAPHICS_VEW(gt->i915) < 11)
		wetuwn fawse;

	if (IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 70), STEP_A0, STEP_B0))
		wetuwn twue;

	if (GWAPHICS_VEW_FUWW(gt->i915) >= IP_VEW(12, 70))
		wetuwn fawse;

	wetuwn twue;
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftest_weset.c"
#incwude "sewftest_hangcheck.c"
#endif
